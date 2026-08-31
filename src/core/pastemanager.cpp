#include "pastemanager.hpp"
#include "hyprlandipc.hpp"
#include <QGuiApplication>
#include <QClipboard>
#include <QProcess>
#include <QTimer>
#include <QFile>
#include <QImage>

namespace stowaway::core {

PasteManager::PasteManager(QObject* parent)
    : QObject(parent) {}

PasteManager* PasteManager::instance() {
    static PasteManager inst;
    return &inst;
}

void PasteManager::copyText(const QString& text) {
    if (auto* cb = QGuiApplication::clipboard()) {
        cb->setText(text, QClipboard::Clipboard);
        cb->setText(text, QClipboard::Selection);
    }

    // Run wl-copy in background to ensure Wayland persistence
    auto* proc = new QProcess(this);
    connect(proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), proc, &QObject::deleteLater);
    proc->start(QStringLiteral("wl-copy"), { QStringLiteral("--type"), QStringLiteral("text/plain;charset=utf-8"), text });

    emit contentCopied(QStringLiteral("Copied to clipboard"));
}

void PasteManager::copyImage(const QString& imagePath) {
    QImage img(imagePath);
    if (!img.isNull()) {
        if (auto* cb = QGuiApplication::clipboard()) {
            cb->setImage(img, QClipboard::Clipboard);
        }
    }

    if (QFile::exists(imagePath)) {
        auto* proc = new QProcess(this);
        connect(proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), proc, &QObject::deleteLater);
        proc->start(QStringLiteral("sh"), { QStringLiteral("-c"), QStringLiteral("wl-copy -t image/png < \"%1\"").arg(imagePath) });
    }

    emit contentCopied(QStringLiteral("Image copied to clipboard"));
}

void PasteManager::pasteText(const QString& text, const QString& targetWindowAddress) {
    copyText(text);

    if (!targetWindowAddress.isEmpty()) {
        HyprlandIPC::focusWindow(targetWindowAddress);
    }

    // Delay slightly to let the compositor refocus the target client
    QTimer::singleShot(80, this, [this]() {
        simulatePaste();
        emit pasteCompleted();
    });
}

void PasteManager::pasteImage(const QString& imagePath, const QString& targetWindowAddress) {
    copyImage(imagePath);

    if (!targetWindowAddress.isEmpty()) {
        HyprlandIPC::focusWindow(targetWindowAddress);
    }

    QTimer::singleShot(80, this, [this]() {
        simulatePaste();
        emit pasteCompleted();
    });
}

void PasteManager::simulatePaste() {
    // Try wtype first (as requested: wtype -M ctrl -k v -m ctrl)
    QProcess wtypeProc;
    wtypeProc.start(QStringLiteral("wtype"), { QStringLiteral("-M"), QStringLiteral("ctrl"), QStringLiteral("-k"), QStringLiteral("v"), QStringLiteral("-m"), QStringLiteral("ctrl") });
    if (wtypeProc.waitForFinished(300) && wtypeProc.exitCode() == 0) {
        return;
    }

    // Fallback: ydotool if wtype is not found
    QProcess ydoProc;
    ydoProc.start(QStringLiteral("ydotool"), { QStringLiteral("key"), QStringLiteral("29:1"), QStringLiteral("47:1"), QStringLiteral("47:0"), QStringLiteral("29:0") });
    ydoProc.waitForFinished(300);
}

} // namespace stowaway::core
