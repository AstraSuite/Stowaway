#pragma once

#include <QObject>
#include <QPoint>
#include <QRect>
#include <QJSEngine>
#include <QQmlEngine>
#include <qqmlintegration.h>

namespace stowaway::core {

class PositionController : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(int targetX READ targetX NOTIFY positionChanged)
    Q_PROPERTY(int targetY READ targetY NOTIFY positionChanged)
    Q_PROPERTY(int monitorX READ monitorX NOTIFY positionChanged)
    Q_PROPERTY(int monitorY READ monitorY NOTIFY positionChanged)
    Q_PROPERTY(int monitorWidth READ monitorWidth NOTIFY positionChanged)
    Q_PROPERTY(int monitorHeight READ monitorHeight NOTIFY positionChanged)
    Q_PROPERTY(QString monitorName READ monitorName NOTIFY positionChanged)

public:
    static PositionController* instance();
    static PositionController* create(QQmlEngine* = nullptr, QJSEngine* = nullptr) {
        auto* inst = instance();
        QJSEngine::setObjectOwnership(inst, QJSEngine::CppOwnership);
        return inst;
    }

    int targetX() const { return m_targetX; }
    int targetY() const { return m_targetY; }
    int monitorX() const { return m_monitorX; }
    int monitorY() const { return m_monitorY; }
    int monitorWidth() const { return m_monitorWidth; }
    int monitorHeight() const { return m_monitorHeight; }
    QString monitorName() const { return m_monitorName; }

    Q_INVOKABLE void calculatePosition(int overlayWidth = -1, int overlayHeight = -1);
    Q_INVOKABLE void updateSize(int overlayWidth = -1, int overlayHeight = -1);

signals:
    void positionChanged();

private:
    explicit PositionController(QObject* parent = nullptr);

    int m_targetX = 100;
    int m_targetY = 100;
    int m_monitorX = 0;
    int m_monitorY = 0;
    int m_monitorWidth = 1920;
    int m_monitorHeight = 1080;
    QString m_monitorName;
};

} // namespace stowaway::core
