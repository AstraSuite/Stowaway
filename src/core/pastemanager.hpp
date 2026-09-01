#pragma once

#include <QObject>
#include <QString>
#include <QJSEngine>
#include <QQmlEngine>
#include <qqmlintegration.h>

namespace stowaway::core {

class PasteManager : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    static PasteManager* instance();
    static PasteManager* create(QQmlEngine* = nullptr, QJSEngine* = nullptr) {
        auto* inst = instance();
        QJSEngine::setObjectOwnership(inst, QJSEngine::CppOwnership);
        return inst;
    }

    Q_INVOKABLE void pasteText(const QString& text, const QString& targetWindowAddress = QString());
    Q_INVOKABLE void copyText(const QString& text);
    Q_INVOKABLE void pasteImage(const QString& filePath, const QString& targetWindowAddress = QString());
    Q_INVOKABLE void copyImage(const QString& filePath);
    void simulatePaste();

signals:
    void contentCopied(const QString& message);
    void pasteCompleted();

private:
    explicit PasteManager(QObject* parent = nullptr);
};

} // namespace stowaway::core
