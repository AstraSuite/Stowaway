#include "pastemanager.hpp"
#include "hyprlandipc.hpp"
#include <QGuiApplication>
#include <QClipboard>
#include <QProcess>
#include <QTimer>
#include <QFile>
#include <QImage>
#include <linux/uinput.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

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
    QTimer::singleShot(80, this, [this, targetWindowAddress]() {
        bool isTerm = HyprlandIPC::isTargetTerminal(targetWindowAddress);
        simulatePaste(isTerm);
        emit pasteCompleted();
    });
}

void PasteManager::pasteImage(const QString& imagePath, const QString& targetWindowAddress) {
    copyImage(imagePath);

    if (!targetWindowAddress.isEmpty()) {
        HyprlandIPC::focusWindow(targetWindowAddress);
    }

    QTimer::singleShot(80, this, [this, targetWindowAddress]() {
        bool isTerm = HyprlandIPC::isTargetTerminal(targetWindowAddress);
        simulatePaste(isTerm);
        emit pasteCompleted();
    });
}

static bool simulatePasteUinput(bool isTerminal) {
    int fd = ::open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd < 0) return false;

    if (::ioctl(fd, UI_SET_EVBIT, EV_KEY) < 0 ||
        ::ioctl(fd, UI_SET_EVBIT, EV_SYN) < 0 ||
        ::ioctl(fd, UI_SET_KEYBIT, KEY_LEFTCTRL) < 0 ||
        ::ioctl(fd, UI_SET_KEYBIT, KEY_LEFTSHIFT) < 0 ||
        ::ioctl(fd, UI_SET_KEYBIT, KEY_V) < 0) {
        ::close(fd);
        return false;
    }

    struct uinput_setup usetup;
    std::memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234;
    usetup.id.product = 0x5678;
    std::strncpy(usetup.name, "stowaway-paste", sizeof(usetup.name) - 1);

    if (::ioctl(fd, UI_DEV_SETUP, &usetup) < 0 ||
        ::ioctl(fd, UI_DEV_CREATE) < 0) {
        ::close(fd);
        return false;
    }

    // Small delay so compositor and target window register the virtual keyboard
    ::usleep(40000);

    auto emit_ev = [fd](int type, int code, int val) {
        struct input_event ie;
        std::memset(&ie, 0, sizeof(ie));
        ie.type = type;
        ie.code = code;
        ie.value = val;
        (void)::write(fd, &ie, sizeof(ie));
    };

    emit_ev(EV_KEY, KEY_LEFTCTRL, 1);
    if (isTerminal) {
        emit_ev(EV_KEY, KEY_LEFTSHIFT, 1);
    }
    emit_ev(EV_KEY, KEY_V, 1);
    emit_ev(EV_SYN, SYN_REPORT, 0);

    ::usleep(25000);

    emit_ev(EV_KEY, KEY_V, 0);
    if (isTerminal) {
        emit_ev(EV_KEY, KEY_LEFTSHIFT, 0);
    }
    emit_ev(EV_KEY, KEY_LEFTCTRL, 0);
    emit_ev(EV_SYN, SYN_REPORT, 0);

    ::usleep(20000);

    ::ioctl(fd, UI_DEV_DESTROY);
    ::close(fd);
    return true;
}

void PasteManager::simulatePaste(bool isTerminal) {
    // 1. Try direct uinput first (guarantees real evdev keycodes: KEY_LEFTCTRL 29, KEY_LEFTSHIFT 42, KEY_V 47)
    // This avoids wtype's synthetic keymap which maps keycode 1 (KEY_ESC), causing Hyprland to trigger Ctrl+Shift+Escape.
    if (simulatePasteUinput(isTerminal)) {
        return;
    }

    // 2. Fallback: ydotool with real evdev keycodes
    QProcess ydoProc;
    if (isTerminal) {
        ydoProc.start(QStringLiteral("ydotool"), {
            QStringLiteral("key"),
            QStringLiteral("29:1"), QStringLiteral("42:1"), QStringLiteral("47:1"),
            QStringLiteral("47:0"), QStringLiteral("42:0"), QStringLiteral("29:0")
        });
    } else {
        ydoProc.start(QStringLiteral("ydotool"), {
            QStringLiteral("key"),
            QStringLiteral("29:1"), QStringLiteral("47:1"),
            QStringLiteral("47:0"), QStringLiteral("29:0")
        });
    }
    if (ydoProc.waitForFinished(300) && ydoProc.exitCode() == 0) {
        return;
    }

    // 3. Fallback: wtype for standard GUI applications (Ctrl+V)
    if (!isTerminal) {
        QProcess wtypeProc;
        wtypeProc.start(QStringLiteral("wtype"), {
            QStringLiteral("-M"), QStringLiteral("ctrl"),
            QStringLiteral("-k"), QStringLiteral("v"),
            QStringLiteral("-m"), QStringLiteral("ctrl")
        });
        wtypeProc.waitForFinished(300);
    }
}

} // namespace stowaway::core
