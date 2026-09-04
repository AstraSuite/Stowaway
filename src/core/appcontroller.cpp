#include "appcontroller.hpp"
#include "hyprlandipc.hpp"
#include "positioncontroller.hpp"
#include "clipboardmanager.hpp"
#include "pastemanager.hpp"
#include "../config/tokens.hpp"
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QTimer>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <algorithm>

namespace stowaway::core {

static QString socketServerName() {
    const QString runtimeDir = qEnvironmentVariable("XDG_RUNTIME_DIR", QStringLiteral("/tmp"));
    return runtimeDir + QStringLiteral("/stowaway.sock");
}

AppController::AppController(QObject* parent)
    : QObject(parent) {
    loadConfiguration();
    setUiScale(m_uiScale);

    m_toastTimer.setSingleShot(true);
    m_toastTimer.setInterval(2000);
    connect(&m_toastTimer, &QTimer::timeout, this, [this]() {
        m_toastVisible = false;
        emit toastVisibleChanged();
    });

    m_saveConfigTimer.setSingleShot(true);
    connect(&m_saveConfigTimer, &QTimer::timeout, this, &AppController::writeConfigurationToDisk);

    bool ok = false;
    int tab = qEnvironmentVariableIntValue("STOWAWAY_INITIAL_TAB", &ok);
    if (ok && tab == -1) {
        m_visible = false;
    } else {
        m_visible = true;
        if (ok && tab >= 0 && tab <= 3) {
            m_activeTab = tab;
        }
    }

    startServer();
    initHyprlandEventSocket();

    if (m_visible) {
        m_targetWindowAddress = HyprlandIPC::getActiveWindowAddress();
        QTimer::singleShot(0, this, [this]() {
            if (m_targetWindowAddress.isEmpty()) {
                m_targetWindowAddress = HyprlandIPC::getActiveWindowAddress();
            }
            emit targetWindowAddressChanged();
        });
    }
}

AppController* AppController::instance() {
    static AppController inst;
    return &inst;
}

void AppController::setIsDaemon(bool daemon) {
    if (m_isDaemon != daemon) {
        m_isDaemon = daemon;
        emit isDaemonChanged();
    }
}

void AppController::quitDaemon() {
    m_isDaemon = false;
    if (m_saveConfigTimer.isActive()) {
        m_saveConfigTimer.stop();
        writeConfigurationToDisk();
    }
    if (m_server) {
        m_server->close();
        QLocalServer::removeServer(socketServerName());
    }
    QCoreApplication::quit();
}

void AppController::setVisible(bool v) {
    if (m_visible != v) {
        m_visible = v;
        if (!m_visible) {
            hideOverlay();
        } else {
            // Emit visibility immediately so the open animation starts without delay.
            // Blocking IPC (positioning, clipboard load) is deferred to the next
            // event-loop iteration so the first frame renders instantly.
            emit visibilityChanged();
            QTimer::singleShot(0, this, [this]() {
                m_targetWindowAddress = HyprlandIPC::getActiveWindowAddress();
                emit targetWindowAddressChanged();
                PositionController::instance()->calculatePosition(m_popupWidth, m_popupHeight);
                ClipboardManager::instance()->checkClipboard();
            });
            return;
        }
        emit visibilityChanged();
    }
}

void AppController::setActiveTab(int tab) {
    if (m_activeTab != tab) {
        m_activeTab = tab;
        emit activeTabChanged();
    }
}

void AppController::setTargetWindowAddress(const QString& addr) {
    if (m_targetWindowAddress != addr) {
        m_targetWindowAddress = addr;
        emit targetWindowAddressChanged();
    }
}

void AppController::showOverlay(int tab) {
    if (tab >= 0) {
        setActiveTab(tab);
    }
    if (m_hyprEventSocket && m_hyprEventSocket->isOpen()) {
        m_hyprEventSocket->readAll();
    }
    m_targetWindowAddress = HyprlandIPC::getActiveWindowAddress();
    emit targetWindowAddressChanged();
    PositionController::instance()->calculatePosition(m_popupWidth, m_popupHeight);
    ClipboardManager::instance()->checkClipboard();
    m_visible = true;
    emit visibilityChanged();
}

void AppController::hideOverlay() {
    if (!m_visible) return;
    if (m_saveConfigTimer.isActive()) {
        m_saveConfigTimer.stop();
        writeConfigurationToDisk();
    }
    m_visible = false;
    emit visibilityChanged();
    emit requestDismiss();

    if (!m_isDaemon) {
        if (m_server) {
            m_server->close();
            QLocalServer::removeServer(socketServerName());
        }

        // Allow QML spring exit animation (~250ms) to play fully before quitting
        QTimer::singleShot(320, []() {
            QCoreApplication::quit();
        });
    }
}

void AppController::dismissAndPasteText(const QString& text, const QString& targetAddress) {
    if (!m_visible) return;
    PasteManager::instance()->copyText(text);
    beginPasteDismiss(targetAddress);
}

void AppController::dismissAndPasteImage(const QString& filePath, const QString& targetAddress) {
    if (!m_visible) return;
    PasteManager::instance()->copyImage(filePath);
    beginPasteDismiss(targetAddress);
}

void AppController::beginPasteDismiss(const QString& targetAddress) {
    if (!m_visible) return;
    if (m_saveConfigTimer.isActive()) {
        m_saveConfigTimer.stop();
        writeConfigurationToDisk();
    }

    // Keep focus on the overlay so its exit animation renders fully
    m_visible = false;
    emit visibilityChanged();
    emit requestDismiss();

    if (!m_isDaemon) {
        if (m_server) {
            m_server->close();
            QLocalServer::removeServer(socketServerName());
        }
    }

    // Refocus the target only AFTER the exit animation has played (~250ms)
    QTimer::singleShot(280, this, [targetAddress]() {
        if (!targetAddress.isEmpty()) {
            HyprlandIPC::focusWindow(targetAddress);
        }
    });

    // The QML layer is fully unmapped by then (~260ms); keyboard focus has returned to the
    // target, so the paste keystroke lands in the target rather than in the overlay.
    QTimer::singleShot(360, this, [targetAddress]() {
        bool isTerm = HyprlandIPC::isTargetTerminal(targetAddress);
        PasteManager::instance()->simulatePaste(isTerm);
    });

    if (!m_isDaemon) {
        // Quit after the paste has been dispatched
        QTimer::singleShot(480, this, []() {
            QCoreApplication::quit();
        });
    }
}

void AppController::toggleOverlay(int tab) {
    if (!m_visible) {
        showOverlay(tab >= 0 ? tab : 0);
    } else if (tab >= 0 && tab != m_activeTab) {
        setActiveTab(tab);
        PositionController::instance()->calculatePosition(m_popupWidth, m_popupHeight);
    } else {
        hideOverlay();
    }
}

void AppController::showToast(const QString& message) {
    m_toastMessage = message;
    m_toastVisible = true;
    emit toastMessageChanged();
    emit toastVisibleChanged();
    m_toastTimer.start();
}

void AppController::quit() {
    hideOverlay();
}

bool AppController::startServer() {
    QString sockPath = socketServerName();
    QLocalServer::removeServer(sockPath);

    m_server = new QLocalServer(this);
    if (!m_server->listen(sockPath)) {
        return false;
    }

    connect(m_server, &QLocalServer::newConnection, this, &AppController::handleNewConnection);
    return true;
}

void AppController::handleNewConnection() {
    while (m_server && m_server->hasPendingConnections()) {
        QLocalSocket* socket = m_server->nextPendingConnection();
        connect(socket, &QLocalSocket::readyRead, this, [this, socket]() {
            QByteArray data = socket->readAll().trimmed();
            QString cmd = QString::fromUtf8(data);

            if (cmd == QStringLiteral("quit") || cmd == QStringLiteral("kill")) {
                socket->write("OK\n");
                socket->flush();
                socket->disconnectFromServer();
                quitDaemon();
                return;
            } else if (cmd == QStringLiteral("status") || cmd == QStringLiteral("ping")) {
                socket->write("RUNNING\n");
                socket->flush();
                socket->disconnectFromServer();
                return;
            } else if (cmd.startsWith(QStringLiteral("tab:"))) {
                QStringList parts = cmd.split(':');
                int tabIdx = parts.value(1).toInt();
                if (m_visible && tabIdx == m_activeTab && parts.size() <= 2) {
                    hideOverlay();
                } else {
                    setActiveTab(tabIdx);
                    if (parts.size() >= 4) {
                        int w = parts.value(2).toInt();
                        int h = parts.value(3).toInt();
                        if (w > 0 && h > 0) {
                            savePopupSize(w, h);
                        }
                    }
                    if (parts.size() >= 5) {
                        bool ok = false;
                        double s = parts.value(4).toDouble(&ok);
                        if (ok && s > 0.1) {
                            saveUiScale(s);
                        }
                    }
                    showOverlay(tabIdx);
                }
            } else if (cmd.startsWith(QStringLiteral("size:"))) {
                QStringList parts = cmd.split(':');
                if (parts.size() >= 3) {
                    int w = parts.value(1).toInt();
                    int h = parts.value(2).toInt();
                    if (w > 0 && h > 0) {
                        savePopupSize(w, h);
                    }
                }
                showOverlay();
            } else if (cmd.startsWith(QStringLiteral("scale:"))) {
                QStringList parts = cmd.split(':');
                if (parts.size() >= 2) {
                    bool ok = false;
                    double s = parts.value(1).toDouble(&ok);
                    if (ok && s > 0.1) {
                        saveUiScale(s);
                    }
                }
                showOverlay();
            } else if (cmd == QStringLiteral("reset-size")) {
                resetPopupSize();
                showOverlay();
            } else if (cmd == QStringLiteral("emoji")) {
                if (m_visible && m_activeTab == 1) {
                    hideOverlay();
                } else {
                    setActiveTab(1);
                    showOverlay(1);
                }
            } else if (cmd == QStringLiteral("kaomoji")) {
                if (m_visible && m_activeTab == 2) {
                    hideOverlay();
                } else {
                    setActiveTab(2);
                    showOverlay(2);
                }
            } else if (cmd == QStringLiteral("symbols")) {
                if (m_visible && m_activeTab == 3) {
                    hideOverlay();
                } else {
                    setActiveTab(3);
                    showOverlay(3);
                }
            } else if (cmd == QStringLiteral("toggle")) {
                toggleOverlay(0);
            } else if (cmd == QStringLiteral("clips")) {
                if (m_visible && m_activeTab == 0) {
                    hideOverlay();
                } else {
                    setActiveTab(0);
                    showOverlay(0);
                }
            } else if (cmd == QStringLiteral("hide")) {
                hideOverlay();
            }

            socket->write("OK\n");
            socket->flush();
            socket->disconnectFromServer();
        });
    }
}

QString AppController::configFilePath() const {
    QString home = QDir::homePath();
    QString caelestiaDir = home + QStringLiteral("/.config/caelestia");
    if (QDir(caelestiaDir).exists()) {
        return caelestiaDir + QStringLiteral("/stowaway.json");
    }
    return home + QStringLiteral("/.config/stowaway/config.json");
}

void AppController::loadConfiguration() {
    // 1. Check existing config files
    QString home = QDir::homePath();
    QStringList configCandidates = {
        home + QStringLiteral("/.config/caelestia/stowaway.json"),
        home + QStringLiteral("/.config/stowaway/config.json"),
        home + QStringLiteral("/.config/caelestia/shell-tokens.json"),
        home + QStringLiteral("/.config/caelestia/shell.json")
    };

    for (const auto& path : configCandidates) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) continue;
        auto doc = QJsonDocument::fromJson(file.readAll());
        if (!doc.isObject()) continue;
        auto obj = doc.object();

        if (path.endsWith(QLatin1String("stowaway.json")) || path.endsWith(QLatin1String("config.json"))) {
            if (obj.contains("daemon")) {
                m_isDaemon = obj.value("daemon").toBool(m_isDaemon);
            }
            if (obj.contains("scale")) {
                m_uiScale = obj.value("scale").toDouble(m_uiScale);
            }
            if (obj.contains("width") && obj.contains("height")) {
                m_popupWidth = obj.value("width").toInt(m_popupWidth);
                m_popupHeight = obj.value("height").toInt(m_popupHeight);
                break;
            } else if (obj.contains("sizes")) {
                auto sz = obj.value("sizes").toObject();
                if (sz.contains("width") && sz.contains("height")) {
                    m_popupWidth = sz.value("width").toInt(m_popupWidth);
                    m_popupHeight = sz.value("height").toInt(m_popupHeight);
                    break;
                }
            } else if (obj.contains("popup")) {
                auto sz = obj.value("popup").toObject();
                if (sz.contains("width") && sz.contains("height")) {
                    m_popupWidth = sz.value("width").toInt(m_popupWidth);
                    m_popupHeight = sz.value("height").toInt(m_popupHeight);
                    break;
                }
            }
        } else if (path.endsWith(QLatin1String("shell-tokens.json"))) {
            if (obj.contains("scale")) {
                m_uiScale = obj.value("scale").toDouble(m_uiScale);
            }
            if (obj.contains("sizes")) {
                auto sz = obj.value("sizes").toObject();
                if (sz.contains("stowaway")) {
                    auto st = sz.value("stowaway").toObject();
                    if (st.contains("width")) m_popupWidth = st.value("width").toInt(m_popupWidth);
                    if (st.contains("height")) m_popupHeight = st.value("height").toInt(m_popupHeight);
                } else if (sz.contains("clipboard")) {
                    auto cb = sz.value("clipboard").toObject();
                    if (cb.contains("width")) m_popupWidth = cb.value("width").toInt(m_popupWidth);
                    if (cb.contains("height")) m_popupHeight = cb.value("height").toInt(m_popupHeight);
                }
            }
        } else if (path.endsWith(QLatin1String("shell.json"))) {
            if (obj.contains("scale")) {
                m_uiScale = obj.value("scale").toDouble(m_uiScale);
            }
            if (obj.contains("stowaway")) {
                auto st = obj.value("stowaway").toObject();
                if (st.contains("width")) m_popupWidth = st.value("width").toInt(m_popupWidth);
                if (st.contains("height")) m_popupHeight = st.value("height").toInt(m_popupHeight);
            }
        }
    }

    // 2. Override with environment variables if present
    bool okW = false;
    int envW = qEnvironmentVariableIntValue("STOWAWAY_WIDTH", &okW);
    if (okW && envW > 0) m_popupWidth = envW;

    bool okH = false;
    int envH = qEnvironmentVariableIntValue("STOWAWAY_HEIGHT", &okH);
    if (okH && envH > 0) m_popupHeight = envH;

    bool okS = false;
    double envS = qEnvironmentVariable("STOWAWAY_SCALE").toDouble(&okS);
    if (okS && envS > 0.1) m_uiScale = envS;

    if (qEnvironmentVariableIsSet("STOWAWAY_DAEMON")) {
        QString dEnv = qEnvironmentVariable("STOWAWAY_DAEMON").trimmed();
        if (dEnv == QStringLiteral("0") || dEnv.compare(QStringLiteral("false"), Qt::CaseInsensitive) == 0) {
            m_isDaemon = false;
        } else if (dEnv == QStringLiteral("1") || dEnv.compare(QStringLiteral("true"), Qt::CaseInsensitive) == 0) {
            m_isDaemon = true;
        }
    }
    if (qEnvironmentVariableIsSet("STOWAWAY_NO_DAEMON")) {
        m_isDaemon = false;
    }

    // Clamp within bounds
    m_popupWidth = std::clamp(m_popupWidth, MinWidth, MaxWidth);
    m_popupHeight = std::clamp(m_popupHeight, MinHeight, MaxHeight);
    m_uiScale = std::clamp(m_uiScale, 0.5, 3.0);
}

void AppController::setPopupWidth(int w) {
    w = std::clamp(w, MinWidth, MaxWidth);
    if (m_popupWidth != w) {
        m_popupWidth = w;
        emit popupSizeChanged();
        PositionController::instance()->updateSize(m_popupWidth, m_popupHeight);
    }
}

void AppController::setPopupHeight(int h) {
    h = std::clamp(h, MinHeight, MaxHeight);
    if (m_popupHeight != h) {
        m_popupHeight = h;
        emit popupSizeChanged();
        PositionController::instance()->updateSize(m_popupWidth, m_popupHeight);
    }
}

void AppController::setPopupSize(int w, int h) {
    w = std::clamp(w, MinWidth, MaxWidth);
    h = std::clamp(h, MinHeight, MaxHeight);
    if (m_popupWidth != w || m_popupHeight != h) {
        m_popupWidth = w;
        m_popupHeight = h;
        emit popupSizeChanged();
        PositionController::instance()->updateSize(m_popupWidth, m_popupHeight);
    }
}

void AppController::setUiScale(qreal s) {
    s = std::clamp(s, 0.5, 3.0);
    if (!qFuzzyCompare(m_uiScale, s)) {
        m_uiScale = s;
        if (auto* tokens = stowaway::config::TokensSingleton::instance()) {
            if (tokens->font()) tokens->font()->setScale(m_uiScale);
            if (tokens->spacing()) tokens->spacing()->setScale(m_uiScale);
            if (tokens->padding()) tokens->padding()->setScale(m_uiScale);
            if (tokens->rounding()) tokens->rounding()->setScale(m_uiScale);
        }
        emit uiScaleChanged();
    }
}

void AppController::saveUiScale(qreal s) {
    setUiScale(s);
    m_saveConfigTimer.start(300);
}

void AppController::savePopupSize(int w, int h) {
    setPopupSize(w, h);
    m_saveConfigTimer.start(300);
}

void AppController::writeConfigurationToDisk() {
    QString path = configFilePath();
    QFileInfo fi(path);
    QDir().mkpath(fi.dir().path());

    QJsonObject obj;
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        auto doc = QJsonDocument::fromJson(file.readAll());
        if (doc.isObject()) obj = doc.object();
        file.close();
    }

    obj["width"] = m_popupWidth;
    obj["height"] = m_popupHeight;
    obj["scale"] = m_uiScale;

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file.write(QJsonDocument(obj).toJson(QJsonDocument::Indented));
        file.close();
    }
}

void AppController::resetPopupSize() {
    if (m_saveConfigTimer.isActive()) m_saveConfigTimer.stop();
    setUiScale(1.0);
    setPopupSize(DefaultWidth, DefaultHeight);
    writeConfigurationToDisk();
}

bool AppController::sendCommandToRunningInstance(const QString& cmd) {
    QString sockPath = socketServerName();
    QLocalSocket socket;
    socket.connectToServer(sockPath);
    if (socket.waitForConnected(150)) {
        socket.write(cmd.toUtf8());
        socket.flush();
        socket.waitForBytesWritten(150);
        socket.waitForReadyRead(150);
        return true;
    }
    return false;
}

void AppController::initHyprlandEventSocket() {
    const QString his = qEnvironmentVariable("HYPRLAND_INSTANCE_SIGNATURE");
    if (his.isEmpty()) return;

    const QString runtimeDir = qEnvironmentVariable("XDG_RUNTIME_DIR", QStringLiteral("/tmp"));
    QString socketPath = QStringLiteral("%1/hypr/%2/.socket2.sock").arg(runtimeDir, his);
    if (!QFile::exists(socketPath)) {
        socketPath = QStringLiteral("/tmp/hypr/%1/.socket2.sock").arg(his);
    }

    m_hyprEventSocket = new QLocalSocket(this);
    connect(m_hyprEventSocket, &QLocalSocket::readyRead, this, &AppController::handleHyprlandEvent);
    m_hyprEventSocket->connectToServer(socketPath);
}

void AppController::handleHyprlandEvent() {
    if (!m_hyprEventSocket) return;
    QByteArray data = m_hyprEventSocket->readAll();
    if (!m_visible) return;
    const QString text = QString::fromUtf8(data);
    const QStringList lines = text.split(QLatin1Char('\n'), Qt::SkipEmptyParts);

    for (const QString& line : lines) {
        if (line.startsWith(QStringLiteral("focusedmon>>")) ||
            line.startsWith(QStringLiteral("workspace>>")) ||
            line.startsWith(QStringLiteral("activewindow>>")) ||
            line.startsWith(QStringLiteral("activewindowv2>>"))) {
            hideOverlay();
            break;
        }
    }
}

} // namespace stowaway::core
