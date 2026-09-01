#include "clipboardmanager.hpp"
#include "pastemanager.hpp"
#include "hyprlandipc.hpp"
#include "thumbnailprovider.hpp"
#include "appcontroller.hpp"
#include <QGuiApplication>
#include <QClipboard>
#include <QMimeData>
#include <QImage>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QRegularExpression>
#include <QDebug>

namespace stowaway::core {

ClipboardManager::ClipboardManager(QObject* parent)
    : QObject(parent) {
    loadHistory();
}

ClipboardManager::~ClipboardManager() {
}

ClipboardManager* ClipboardManager::instance() {
    static ClipboardManager inst;
    return &inst;
}

int ClipboardManager::pinnedCount() const {
    int count = 0;
    for (auto* item : m_items) {
        if (item->pinned()) count++;
    }
    return count;
}

int ClipboardManager::imageCount() const {
    int count = 0;
    for (auto* item : m_items) {
        if (item->type() == ClipboardType::Image) count++;
    }
    return count;
}

void ClipboardManager::setFilterQuery(const QString& query) {
    if (m_filterQuery != query) {
        m_filterQuery = query;
        emit filterQueryChanged();
        updateFilteredItems();
    }
}

void ClipboardManager::setOnlyPinned(bool pinned) {
    if (m_onlyPinned != pinned) {
        m_onlyPinned = pinned;
        emit onlyPinnedChanged();
        updateFilteredItems();
    }
}

void ClipboardManager::setFilterType(int type) {
    if (m_filterType != type) {
        m_filterType = type;
        emit filterTypeChanged();
        updateFilteredItems();
    }
}

void ClipboardManager::setFilterPinnedOnly(bool pinnedOnly) {
    if (m_filterPinnedOnly != pinnedOnly) {
        m_filterPinnedOnly = pinnedOnly;
        emit filterPinnedOnlyChanged();
        updateFilteredItems();
    }
}

void ClipboardManager::startWaylandWatchers() {
}

void ClipboardManager::onTextWatcherReady() {
}

void ClipboardManager::onImageWatcherReady() {
}

void ClipboardManager::checkClipboard() {
    loadHistory();
}

void ClipboardManager::loadHistory() {
    // Read from cliphist (shared with Caelestia / Hyprland ecosystem)
    QProcess proc;
    proc.start(QStringLiteral("cliphist"), {QStringLiteral("list")});
    if (!proc.waitForFinished(600)) {
        return;
    }

    QString output = QString::fromUtf8(proc.readAllStandardOutput());
    QStringList lines = output.split(QLatin1Char('\n'), Qt::SkipEmptyParts);

    qDeleteAll(m_items);
    m_items.clear();

    QString cacheDir = QStringLiteral("/tmp/caelestia-clipboard");
    QDir().mkpath(cacheDir);

    static const QRegularExpression imgRegex(QStringLiteral(R"(^\[\[\s*binary data\s+(\d+)\s+KiB\s+png\s+(\d+)x(\d+)\s*\]\])"));

    for (const QString& line : lines) {
        int tabIdx = line.indexOf(QLatin1Char('\t'));
        if (tabIdx <= 0) continue;

        QString idStr = line.left(tabIdx).trimmed();
        QString preview = line.mid(tabIdx + 1);

        auto match = imgRegex.match(preview);
        if (match.hasMatch() || preview.startsWith(QStringLiteral("[[ binary data"))) {
            // Image entry
            QString imgPath = cacheDir + QStringLiteral("/") + idStr + QStringLiteral(".png");
            if (!QFile::exists(imgPath)) {
                // Decode image from cliphist
                QProcess decodeProc;
                decodeProc.setStandardOutputFile(imgPath);
                decodeProc.start(QStringLiteral("cliphist"), {QStringLiteral("decode"), idStr});
                decodeProc.waitForFinished(200);
            }

            int w = match.hasMatch() ? match.captured(2).toInt() : 0;
            int h = match.hasMatch() ? match.captured(3).toInt() : 0;
            int kbs = match.hasMatch() ? match.captured(1).toInt() : 0;

            auto* item = new ClipboardItem(idStr, ClipboardType::Image, imgPath, QDateTime::currentDateTime(), false, this);
            item->setImagePath(imgPath);
            item->setImageWidth(w);
            item->setImageHeight(h);
            item->setByteSize(kbs * 1024);
            item->setPreviewText(w > 0 ? QStringLiteral("%1 × %2 Image").arg(w).arg(h) : QStringLiteral("Image"));
            m_items.append(item);
        } else {
            // Text entry (classify Code, URL, Color, Text)
            ClipboardType type = ClipboardType::Text;
            QString trimmed = preview.trimmed();

            if (trimmed.startsWith(QStringLiteral("http://")) || trimmed.startsWith(QStringLiteral("https://"))) {
                type = ClipboardType::Url;
            } else if (trimmed.startsWith(QLatin1Char('#')) && (trimmed.size() == 4 || trimmed.size() == 7 || trimmed.size() == 9)) {
                type = ClipboardType::Color;
            } else if (trimmed.startsWith(QStringLiteral("rgb(")) || trimmed.startsWith(QStringLiteral("rgba("))) {
                type = ClipboardType::Color;
            } else if (trimmed.contains(QStringLiteral("const ")) || trimmed.contains(QStringLiteral("function")) ||
                       trimmed.contains(QStringLiteral("let ")) || trimmed.contains(QStringLiteral("import ")) ||
                       trimmed.contains(QStringLiteral("def ")) || trimmed.contains(QStringLiteral("class "))) {
                type = ClipboardType::Code;
            }

            auto* item = new ClipboardItem(idStr, type, preview, QDateTime::currentDateTime(), false, this);
            m_items.append(item);
        }

        if (m_items.size() >= 100) break;
    }

    emit itemsChanged();
    updateFilteredItems();
}

void ClipboardManager::updateFilteredItems() {
    m_filteredItems.clear();
    QString query = m_filterQuery.trimmed().toLower();

    for (auto* item : m_items) {
        if (!query.isEmpty()) {
            if (!item->previewText().toLower().contains(query) &&
                !item->content().toLower().contains(query)) {
                continue;
            }
        }
        m_filteredItems.append(item);
    }

    emit filteredItemsChanged();
}

void ClipboardManager::selectItem(const QString& id, const QString& targetWindowAddress) {
    if (id.isEmpty()) return;

    auto* ac = AppController::instance();
    if (!ac->isVisible()) return;

    // Determine the item type so we can dispatch to the correct paste path. Images are
    // already decoded into /tmp/caelestia-clipboard/<id>.png during loadHistory().
    ClipboardType type = ClipboardType::Text;
    for (auto* it : std::as_const(m_items)) {
        if (it->id() == id) { type = it->type(); break; }
    }

    if (type == ClipboardType::Image) {
        const QString imgPath = QStringLiteral("/tmp/caelestia-clipboard/") + id + QStringLiteral(".png");
        ac->dismissAndPasteImage(imgPath, targetWindowAddress);
        return;
    }

    // Text/Code/Url/Color: start the dismiss animation immediately so the close
    // animation plays right away, then restore the clipboard item via the canonical
    // "cliphist decode | wl-copy" pipeline. startDetached is critical: wl-copy must
    // stay alive after QCoreApplication::quit() (480ms) to serve the Wayland clipboard
    // read that the simulatePaste() Ctrl+V keystroke (360ms) triggers in the target
    // window. A child process would be killed at quit() before that read completes.
    ac->beginPasteDismiss(targetWindowAddress);
    QProcess::startDetached(QStringLiteral("sh"),
        { QStringLiteral("-c"),
          QStringLiteral("cliphist decode %1 | wl-copy").arg(id) });
}

void ClipboardManager::copyItem(const QString& id) {
    if (id.isEmpty()) return;
    QProcess decodeProc;
    decodeProc.start(QStringLiteral("sh"), {
        QStringLiteral("-c"),
        QStringLiteral("cliphist decode %1 | wl-copy").arg(id)
    });
    decodeProc.waitForFinished(300);
}

void ClipboardManager::togglePin(const QString& id) {
    for (auto* item : m_items) {
        if (item->id() == id) {
            item->setPinned(!item->pinned());
            emit itemsChanged();
            updateFilteredItems();
            break;
        }
    }
}

void ClipboardManager::deleteItem(const QString& id) {
    if (id.isEmpty()) return;

    // Delete from cliphist
    QProcess delProc;
    delProc.start(QStringLiteral("sh"), {
        QStringLiteral("-c"),
        QStringLiteral("cliphist list | grep -E '^%1[[:space:]]' | cliphist delete").arg(id)
    });
    delProc.waitForFinished(300);

    for (int i = 0; i < m_items.size(); ++i) {
        if (m_items.at(i)->id() == id) {
            auto* item = m_items.takeAt(i);
            item->deleteLater();
            emit itemsChanged();
            updateFilteredItems();
            break;
        }
    }
}

void ClipboardManager::clearHistory() {
    QProcess wipeProc;
    wipeProc.start(QStringLiteral("cliphist"), {QStringLiteral("wipe")});
    wipeProc.waitForFinished(300);

    qDeleteAll(m_items);
    m_items.clear();
    emit itemsChanged();
    updateFilteredItems();
}

void ClipboardManager::addItem(ClipboardItem* newItem) {
    if (!newItem) return;
    m_items.prepend(newItem);
    emit itemsChanged();
    updateFilteredItems();
}

void ClipboardManager::saveHistory() {
}

} // namespace stowaway::core
