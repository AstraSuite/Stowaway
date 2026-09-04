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
    Q_PROPERTY(int popupWidth READ popupWidth WRITE setPopupWidth NOTIFY popupSizeChanged)
    Q_PROPERTY(int popupHeight READ popupHeight WRITE setPopupHeight NOTIFY popupSizeChanged)
    Q_PROPERTY(qreal uiScale READ uiScale WRITE setUiScale NOTIFY uiScaleChanged)
    Q_PROPERTY(QString targetWindowAddress READ targetWindowAddress NOTIFY targetWindowAddressChanged)
    Q_PROPERTY(QString toastMessage READ toastMessage NOTIFY toastMessageChanged)
    Q_PROPERTY(bool toastVisible READ toastVisible NOTIFY toastVisibleChanged)
    Q_PROPERTY(bool isDaemon READ isDaemon WRITE setIsDaemon NOTIFY isDaemonChanged)

public:
    static constexpr int DefaultWidth = 390;
    static constexpr int DefaultHeight = 500;
    static constexpr int MinWidth = 320;
    static constexpr int MinHeight = 350;
    static constexpr int MaxWidth = 1600;
    static constexpr int MaxHeight = 1200;

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

    int popupWidth() const { return m_popupWidth; }
    void setPopupWidth(int w);

    int popupHeight() const { return m_popupHeight; }
    void setPopupHeight(int h);

    qreal uiScale() const { return m_uiScale; }
    void setUiScale(qreal s);

    Q_INVOKABLE void setPopupSize(int w, int h);
    Q_INVOKABLE void savePopupSize(int w, int h);
    Q_INVOKABLE void saveUiScale(qreal s);
    Q_INVOKABLE void resetPopupSize();

    QString targetWindowAddress() const { return m_targetWindowAddress; }
    void setTargetWindowAddress(const QString& addr);

    QString toastMessage() const { return m_toastMessage; }
    bool toastVisible() const { return m_toastVisible; }

    bool isDaemon() const { return m_isDaemon; }
    void setIsDaemon(bool daemon);

    Q_INVOKABLE void showOverlay(int tab = -1);
    Q_INVOKABLE void hideOverlay();
    Q_INVOKABLE void toggleOverlay(int tab = -1);
    Q_INVOKABLE void showToast(const QString& message);
    Q_INVOKABLE void quit();
    Q_INVOKABLE void quitDaemon();

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
    void popupSizeChanged();
    void uiScaleChanged();
    void targetWindowAddressChanged();
    void toastMessageChanged();
    void toastVisibleChanged();
    void isDaemonChanged();
    void requestDismiss();

private slots:
    void handleNewConnection();
    void handleHyprlandEvent();

private:
    explicit AppController(QObject* parent = nullptr);

    bool m_visible = false;
    bool m_isDaemon = false;
    int m_activeTab = 0;
    int m_popupWidth = DefaultWidth;
    int m_popupHeight = DefaultHeight;
    qreal m_uiScale = 1.0;
    QString m_targetWindowAddress;
    QString m_toastMessage;
    bool m_toastVisible = false;

    void loadConfiguration();
    void writeConfigurationToDisk();
    QString configFilePath() const;

    QLocalServer* m_server = nullptr;
    QLocalSocket* m_hyprEventSocket = nullptr;
    QTimer m_toastTimer;
    QTimer m_saveConfigTimer;
};

} // namespace stowaway::core
