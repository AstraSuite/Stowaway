#pragma once

#include <QObject>
#include <QString>
#include <QLocalServer>
#include <QLocalSocket>
#include <QTimer>
#include <QJSEngine>
#include <QQmlEngine>
#include <qqmlintegration.h>

namespace stowaway::core {

class AppController : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibilityChanged)
    Q_PROPERTY(int activeTab READ activeTab WRITE setActiveTab NOTIFY activeTabChanged)
    Q_PROPERTY(QString targetWindowAddress READ targetWindowAddress NOTIFY targetWindowAddressChanged)
    Q_PROPERTY(QString toastMessage READ toastMessage NOTIFY toastMessageChanged)
    Q_PROPERTY(bool toastVisible READ toastVisible NOTIFY toastVisibleChanged)

public:
    explicit AppController(QObject* parent = nullptr);

    static AppController* instance();
    static AppController* create(QQmlEngine* = nullptr, QJSEngine* = nullptr) {
        auto* inst = instance();
        QJSEngine::setObjectOwnership(inst, QJSEngine::CppOwnership);
        return inst;
    }

    bool isVisible() const { return m_visible; }
    void setVisible(bool v);

    int activeTab() const { return m_activeTab; }
    void setActiveTab(int tab);

    QString targetWindowAddress() const { return m_targetWindowAddress; }
    void setTargetWindowAddress(const QString& addr);

    QString toastMessage() const { return m_toastMessage; }
    bool toastVisible() const { return m_toastVisible; }

    Q_INVOKABLE void showOverlay(int tab = -1);
    Q_INVOKABLE void hideOverlay();
    Q_INVOKABLE void toggleOverlay(int tab = -1);
    Q_INVOKABLE void showToast(const QString& message);
    Q_INVOKABLE void quit();

    // Copy content to the clipboard, then animate the overlay out and only send the
    // paste keystroke AFTER the overlay has fully closed (releasing keyboard focus).
    Q_INVOKABLE void dismissAndPasteText(const QString& text, const QString& targetAddress = QString());
    Q_INVOKABLE void dismissAndPasteImage(const QString& filePath, const QString& targetAddress = QString());
    // Shared tail: plays the exit animation, refocuses the target after it closes, pastes, then quits.
    void beginPasteDismiss(const QString& targetAddress);

    bool startServer();
    void initHyprlandEventSocket();
    static bool sendCommandToRunningInstance(const QString& cmd);

signals:
    void visibilityChanged();
    void activeTabChanged();
    void targetWindowAddressChanged();
    void toastMessageChanged();
    void toastVisibleChanged();
    void requestDismiss();

private slots:
    void handleNewConnection();
    void handleHyprlandEvent();

private:
    bool m_visible = false;
    int m_activeTab = 0;
    QString m_targetWindowAddress;
    QString m_toastMessage;
    bool m_toastVisible = false;

    QLocalServer* m_server = nullptr;
    QLocalSocket* m_hyprEventSocket = nullptr;
    QTimer m_toastTimer;
};

} // namespace stowaway::core
