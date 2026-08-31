#include "hyprlandipc.hpp"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLocalSocket>
#include <QProcess>
#include <QCursor>
#include <QGuiApplication>
#include <QScreen>

namespace stowaway::core {

HyprlandIPC::HyprlandIPC(QObject* parent)
    : QObject(parent) {}

bool HyprlandIPC::isHyprlandRunning() {
    return qEnvironmentVariableIsSet("HYPRLAND_INSTANCE_SIGNATURE");
}

QByteArray HyprlandIPC::requestSocket(const QString& command) {
    const QString his = qEnvironmentVariable("HYPRLAND_INSTANCE_SIGNATURE");
    if (his.isEmpty()) {
        QProcess proc;
        proc.start(QStringLiteral("hyprctl"), { QStringLiteral("-j"), command.startsWith(QLatin1String("j/")) ? command.mid(2) : command });
        if (proc.waitForFinished(800)) {
            return proc.readAllStandardOutput();
        }
        return {};
    }

    const QString runtimeDir = qEnvironmentVariable("XDG_RUNTIME_DIR", QStringLiteral("/tmp"));
    QString socketPath = QStringLiteral("%1/hypr/%2/.socket.sock").arg(runtimeDir, his);
    if (!QFile::exists(socketPath)) {
        socketPath = QStringLiteral("/tmp/hypr/%1/.socket.sock").arg(his);
    }

    QLocalSocket socket;
    socket.connectToServer(socketPath);
    if (!socket.waitForConnected(300)) {
        QProcess proc;
        proc.start(QStringLiteral("hyprctl"), { QStringLiteral("-j"), command.startsWith(QLatin1String("j/")) ? command.mid(2) : command });
        if (proc.waitForFinished(800)) {
            return proc.readAllStandardOutput();
        }
        return {};
    }

    socket.write(command.toUtf8());
    socket.flush();

    QByteArray response;
    while (socket.waitForReadyRead(300)) {
        response.append(socket.readAll());
    }
    return response;
}

QPoint HyprlandIPC::getCursorPos() {
    if (isHyprlandRunning()) {
        QByteArray data = requestSocket(QStringLiteral("j/cursorpos"));
        if (!data.isEmpty()) {
            QJsonDocument doc = QJsonDocument::fromJson(data);
            if (doc.isObject()) {
                QJsonObject obj = doc.object();
                return QPoint(obj.value(QStringLiteral("x")).toInt(), obj.value(QStringLiteral("y")).toInt());
            }
        }
    }
    return QCursor::pos();
}

QList<HyprlandMonitor> HyprlandIPC::getMonitors() {
    QList<HyprlandMonitor> list;
    if (isHyprlandRunning()) {
        QByteArray data = requestSocket(QStringLiteral("j/monitors"));
        if (!data.isEmpty()) {
            QJsonDocument doc = QJsonDocument::fromJson(data);
            if (doc.isArray()) {
                const QJsonArray arr = doc.array();
                for (const QJsonValue& val : arr) {
                    if (!val.isObject()) continue;
                    QJsonObject obj = val.toObject();
                    HyprlandMonitor m;
                    m.id = obj.value(QStringLiteral("id")).toInt();
                    m.name = obj.value(QStringLiteral("name")).toString();
                    m.x = obj.value(QStringLiteral("x")).toInt();
                    m.y = obj.value(QStringLiteral("y")).toInt();
                    m.width = obj.value(QStringLiteral("width")).toInt();
                    m.height = obj.value(QStringLiteral("height")).toInt();
                    m.scale = obj.value(QStringLiteral("scale")).toDouble(1.0);
                    m.transform = obj.value(QStringLiteral("transform")).toInt(0);
                    m.focused = obj.value(QStringLiteral("focused")).toBool();
                    list.append(m);
                }
                return list;
            }
        }
    }

    // Fallback using Qt Screen geometry
    const auto screens = QGuiApplication::screens();
    int id = 0;
    for (auto* screen : screens) {
        HyprlandMonitor m;
        m.id = id++;
        m.name = screen->name();
        QRect g = screen->geometry();
        m.x = g.x();
        m.y = g.y();
        m.width = g.width();
        m.height = g.height();
        m.scale = screen->devicePixelRatio();
        m.focused = (screen == QGuiApplication::primaryScreen());
        list.append(m);
    }
    return list;
}

QString HyprlandIPC::getActiveWindowAddress() {
    if (!isHyprlandRunning()) return {};
    QByteArray data = requestSocket(QStringLiteral("j/activewindow"));
    if (data.isEmpty()) return {};
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isObject()) {
        return doc.object().value(QStringLiteral("address")).toString();
    }
    return {};
}

void HyprlandIPC::focusWindow(const QString& address) {
    if (address.isEmpty() || !isHyprlandRunning()) return;
    requestSocket(QStringLiteral("/dispatch focuswindow address:") + address);
}

void HyprlandIPC::setupWindowRules() {
    if (!isHyprlandRunning()) return;
    requestSocket(QStringLiteral("keyword windowrulev2 float,class:^(stowaway|stowaway_app)$"));
    requestSocket(QStringLiteral("keyword windowrulev2 noborder,class:^(stowaway|stowaway_app)$"));
    requestSocket(QStringLiteral("keyword windowrulev2 noshadow,class:^(stowaway|stowaway_app)$"));
    requestSocket(QStringLiteral("keyword windowrulev2 pin,class:^(stowaway|stowaway_app)$"));
    requestSocket(QStringLiteral("keyword windowrulev2 stayfocused,class:^(stowaway|stowaway_app)$"));
    requestSocket(QStringLiteral("keyword layerrule blur,stowaway"));
    requestSocket(QStringLiteral("keyword layerrule ignorezero,stowaway"));
}

void HyprlandIPC::positionWindow(int x, int y, int w, int h) {
    if (!isHyprlandRunning()) return;
    requestSocket(QStringLiteral("/dispatch movewindowpixel exact %1 %2,class:^(stowaway|stowaway_app)$").arg(x).arg(y));
    requestSocket(QStringLiteral("/dispatch resizewindowpixel exact %1 %2,class:^(stowaway|stowaway_app)$").arg(w).arg(h));
    focusSelf();
}

void HyprlandIPC::focusSelf() {
    if (!isHyprlandRunning()) return;
    requestSocket(QStringLiteral("/dispatch focuswindow class:^(stowaway|stowaway_app)$"));
}

} // namespace stowaway::core
