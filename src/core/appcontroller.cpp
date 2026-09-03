#include "appcontroller.hpp"
#include "hyprlandipc.hpp"
#include "positioncontroller.hpp"
#include "clipboardmanager.hpp"
#include "pastemanager.hpp"
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QTimer>

namespace stowaway::core {

static QString socketServerName() {
    const QString runtimeDir = qEnvironmentVariable("XDG_RUNTIME_DIR", QStringLiteral("/tmp"));
    return runtimeDir + QStringLiteral("/stowaway.sock");
}

AppController::AppController(QObject* parent)
    : QObject(parent) {
    m_visible = true;
    m_toastTimer.setSingleShot(true);
    m_toastTimer.setInterval(2000);
    connect(&m_toastTimer, &QTimer::timeout, this, [this]() {
        m_toastVisible = false;
        emit toastVisibleChanged();
    });

    bool ok = false;
    int tab = qEnvironmentVariableIntValue("STOWAWAY_INITIAL_TAB", &ok);
    if (ok && tab >= 0 && tab <= 3) {
        m_activeTab = tab;
    }

    m_targetWindowAddress = HyprlandIPC::getActiveWindowAddress();

    startServer();
    initHyprlandEventSocket();

    QTimer::singleShot(0, this, [this]() {
        if (m_targetWindowAddress.isEmpty()) {
            m_targetWindowAddress = HyprlandIPC::getActiveWindowAddress();
        }
        emit targetWindowAddressChanged();
    });
}

AppController* AppController::instance() {
    static AppController inst;
    return &inst;
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
                PositionController::instance()->calculatePosition(390, 500);
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
    m_visible = true;
    emit visibilityChanged();
}

void AppController::hideOverlay() {
    if (!m_visible) return;
    m_visible = false;
    emit visibilityChanged();
    emit requestDismiss();

    if (m_server) {
        m_server->close();
        QLocalServer::removeServer(socketServerName());
    }

    // Allow QML spring exit animation (~250ms) to play fully before quitting
    QTimer::singleShot(320, []() {
        QCoreApplication::quit();
    });
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

    // Keep focus on the overlay so its exit animation renders fully
    m_visible = false;
    emit visibilityChanged();
    emit requestDismiss();

    if (m_server) {
        m_server->close();
        QLocalServer::removeServer(socketServerName());
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

    // Quit after the paste has been dispatched
    QTimer::singleShot(480, this, []() {
        QCoreApplication::quit();
    });
}

void AppController::toggleOverlay(int tab) {
    if (tab >= 0 && tab != m_activeTab) {
        setActiveTab(tab);
        PositionController::instance()->calculatePosition(390, 500);
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

            if (cmd.startsWith(QStringLiteral("tab:"))) {
                int tabIdx = cmd.mid(4).toInt();
                setActiveTab(tabIdx);
            } else if (cmd == QStringLiteral("emoji")) {
                setActiveTab(1);
            } else if (cmd == QStringLiteral("kaomoji")) {
                setActiveTab(2);
            } else if (cmd == QStringLiteral("symbols")) {
                setActiveTab(3);
            } else if (cmd == QStringLiteral("toggle") || cmd == QStringLiteral("clips")) {
                setActiveTab(0);
            } else if (cmd == QStringLiteral("hide")) {
                hideOverlay();
            }

            socket->write("OK\n");
            socket->flush();
            socket->disconnectFromServer();
        });
    }
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
    if (!m_hyprEventSocket || !m_visible) return;
    QByteArray data = m_hyprEventSocket->readAll();
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
