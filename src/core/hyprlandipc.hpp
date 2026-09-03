#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include <QPoint>
#include <QRect>

namespace stowaway::core {

struct HyprlandMonitor {
    int id = 0;
    QString name;
    int x = 0;
    int y = 0;
    int width = 1920;
    int height = 1080;
    double scale = 1.0;
    int transform = 0;
    bool focused = false;
    QRect reservedMargins;

    int effectiveWidth() const {
        double s = (scale > 0.0) ? scale : 1.0;
        return (transform % 2 == 1) ? static_cast<int>(height / s) : static_cast<int>(width / s);
    }

    int effectiveHeight() const {
        double s = (scale > 0.0) ? scale : 1.0;
        return (transform % 2 == 1) ? static_cast<int>(width / s) : static_cast<int>(height / s);
    }

    QRect bounds() const {
        return QRect(x, y, effectiveWidth(), effectiveHeight());
    }
};

class HyprlandIPC : public QObject {
    Q_OBJECT

public:
    explicit HyprlandIPC(QObject* parent = nullptr);

    static bool isHyprlandRunning();
    static QByteArray requestSocket(const QString& command);

    static QPoint getCursorPos();
    static QList<HyprlandMonitor> getMonitors();
    static QString getActiveWindowAddress();
    static void focusWindow(const QString& address);
    static void setupWindowRules();
    static void positionWindow(int x, int y, int w, int h);
    static void focusSelf();
    static bool isTerminalClass(const QString& windowClass);
    static bool isTargetTerminal(const QString& address = QString());
};

} // namespace stowaway::core
