#include "emojiservice.hpp"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include <algorithm>

namespace stowaway::core {

EmojiService::EmojiService(QObject* parent)
    : QObject(parent) {
    loadFavorites();
    loadUsageCounts();
    loadDatasets();
    loadRecent();
}

EmojiService* EmojiService::instance() {
    static EmojiService inst;
    return &inst;
}

bool EmojiService::isFavorite(const QString& character) const {
    return m_favorites.contains(character);
}

void EmojiService::toggleFavorite(const QString& character, const QString& name, const QString& type) {
    Q_UNUSED(name)
    Q_UNUSED(type)
    if (m_favorites.contains(character)) {
        m_favorites.removeAll(character);
    } else {
        m_favorites.append(character);
    }
    saveFavorites();
    emit favoritesChanged();
}

void EmojiService::loadFavorites() {
    m_favorites.clear();
    QString dataDir = QDir::homePath() + QStringLiteral("/.local/share/stowaway");
    QString filePath = dataDir + QStringLiteral("/favorites.json");

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isArray()) return;

    for (const auto& val : doc.array()) {
        QString s = val.toString();
        if (!m_favorites.contains(s)) {
            m_favorites.append(s);
        }
    }
}

void EmojiService::saveFavorites() {
    QString dataDir = QDir::homePath() + QStringLiteral("/.local/share/stowaway");
    QDir().mkpath(dataDir);
    QString filePath = dataDir + QStringLiteral("/favorites.json");

    QJsonArray arr;
    for (const auto& fav : m_favorites) {
        arr.append(fav);
    }

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(arr).toJson(QJsonDocument::Compact));
    }
}

void EmojiService::loadUsageCounts() {
    m_usageCounts.clear();
    QString dataDir = QDir::homePath() + QStringLiteral("/.local/share/stowaway");
    QString filePath = dataDir + QStringLiteral("/usage_counts.json");

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) return;

    QJsonObject obj = doc.object();
    for (auto it = obj.begin(); it != obj.end(); ++it) {
        m_usageCounts.insert(it.key(), it.value().toInt());
    }
}

void EmojiService::saveUsageCounts() {
    QString dataDir = QDir::homePath() + QStringLiteral("/.local/share/stowaway");
    QDir().mkpath(dataDir);
    QString filePath = dataDir + QStringLiteral("/usage_counts.json");

    QJsonObject obj;
    for (auto it = m_usageCounts.begin(); it != m_usageCounts.end(); ++it) {
        obj.insert(it.key(), it.value());
    }

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
    }
}

void EmojiService::loadDatasets() {
    auto parseJson = [](const QString& filename, QList<CharacterItem>& targetList, QStringList& categories) {
        targetList.clear();
        categories.clear();
        categories.append(QStringLiteral("All"));

        QString home = QDir::homePath();
        QList<QString> candidates = {
            QStringLiteral(":/qt/qml/Astra/Stowaway/assets/data/") + filename,
            QStringLiteral(":/qt/qml/stowaway/assets/data/") + filename,
            QStringLiteral("/etc/xdg/quickshell/astra-stowaway/assets/data/") + filename,
            QStringLiteral("/usr/share/stowaway/assets/data/") + filename,
            home + QStringLiteral("/Projects/AstraSuite/Stowaway/assets/data/") + filename,
            QDir::currentPath() + QStringLiteral("/assets/data/") + filename
        };

        QFile file;
        bool opened = false;
        for (const auto& path : candidates) {
            file.setFileName(path);
            if (file.open(QIODevice::ReadOnly)) {
                opened = true;
                break;
            }
        }

        if (!opened) {
            qWarning() << "EmojiService: Could not open dataset" << filename;
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        if (!doc.isArray()) return;

        const QJsonArray arr = doc.array();
        int idx = 0;
        for (const auto& val : arr) {
            if (!val.isObject()) continue;
            QJsonObject obj = val.toObject();
            CharacterItem item;
            item.character = obj.value(QStringLiteral("c")).toString();
            item.name = obj.value(QStringLiteral("name")).toString();
            item.category = obj.value(QStringLiteral("cat")).toString();
            item.keywords = obj.value(QStringLiteral("keys")).toString();
            item.index = idx++;

            if (!categories.contains(item.category) && !item.category.isEmpty()) {
                categories.append(item.category);
            }

            targetList.append(item);
        }
    };

    parseJson(QStringLiteral("emojis.json"), m_emojis, m_emojiCategories);
    parseJson(QStringLiteral("kaomoji.json"), m_kaomoji, m_kaomojiCategories);
    parseJson(QStringLiteral("symbols.json"), m_symbols, m_symbolCategories);
    emit datasetsLoaded();
}

QVariantList EmojiService::sortAndFilter(const QList<CharacterItem>& list, const QString& query, const QString& category) {
    QString q = query.trimmed().toLower();
    bool matchCat = !category.isEmpty() && category != QStringLiteral("All");

    struct ScoredItem {
        CharacterItem item;
        bool isFav;
        int favOrder;
        int freq;
    };

    QList<ScoredItem> favMatches;
    QList<ScoredItem> nonFavMatches;

    for (const auto& item : list) {
        if (matchCat && item.category != category) continue;

        if (q.isEmpty() ||
            item.character.contains(q) ||
            item.name.toLower().contains(q) ||
            item.keywords.toLower().contains(q)) {
            
            bool isFav = m_favorites.contains(item.character);
            int favOrder = isFav ? m_favorites.indexOf(item.character) : -1;
            int freq = m_usageCounts.value(item.character, 0);

            ScoredItem scored{ item, isFav, favOrder, freq };
            if (isFav) {
                favMatches.append(scored);
            } else {
                nonFavMatches.append(scored);
            }
        }
    }

    // 1. Sort favorited items by usage frequency (descending), then order favorited
    std::stable_sort(favMatches.begin(), favMatches.end(), [](const ScoredItem& a, const ScoredItem& b) {
        if (a.freq != b.freq) {
            return a.freq > b.freq;
        }
        return a.favOrder < b.favOrder;
    });

    // 2. Sort non-favorited items by usage frequency (descending), then original index
    std::stable_sort(nonFavMatches.begin(), nonFavMatches.end(), [](const ScoredItem& a, const ScoredItem& b) {
        if (a.freq != b.freq) {
            return a.freq > b.freq;
        }
        return a.item.index < b.item.index;
    });

    QVariantList results;
    results.reserve(favMatches.size() + nonFavMatches.size());

    for (const auto& s : favMatches) {
        QVariantMap map;
        map[QStringLiteral("character")] = s.item.character;
        map[QStringLiteral("name")] = s.item.name;
        map[QStringLiteral("category")] = s.item.category;
        map[QStringLiteral("isFavorite")] = true;
        results.append(map);
    }

    for (const auto& s : nonFavMatches) {
        QVariantMap map;
        map[QStringLiteral("character")] = s.item.character;
        map[QStringLiteral("name")] = s.item.name;
        map[QStringLiteral("category")] = s.item.category;
        map[QStringLiteral("isFavorite")] = false;
        results.append(map);
    }

    return results;
}

QVariantList EmojiService::searchEmojis(const QString& query, const QString& category) {
    return sortAndFilter(m_emojis, query, category);
}

QVariantList EmojiService::searchKaomoji(const QString& query, const QString& category) {
    return sortAndFilter(m_kaomoji, query, category);
}

QVariantList EmojiService::searchSymbols(const QString& query, const QString& category) {
    return sortAndFilter(m_symbols, query, category);
}

void EmojiService::recordUsage(const QString& character, const QString& name, const QString& type) {
    Q_UNUSED(name)
    Q_UNUSED(type)
    
    // Increase frequency count
    m_usageCounts[character] = m_usageCounts.value(character, 0) + 1;
    saveUsageCounts();

    m_recentList.removeAll(character);
    m_recentList.prepend(character);
    if (m_recentList.size() > 64) m_recentList.removeLast();

    QString dataDir = QDir::homePath() + QStringLiteral("/.local/share/stowaway");
    QDir().mkpath(dataDir);
    QString filePath = dataDir + QStringLiteral("/recent_characters.json");

    QJsonArray arr;
    for (const auto& c : m_recentList) arr.append(QJsonValue::fromVariant(c));

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(arr).toJson(QJsonDocument::Compact));
    }
}

void EmojiService::loadRecent() {
    m_recentList.clear();
    QString dataDir = QDir::homePath() + QStringLiteral("/.local/share/stowaway");
    QString filePath = dataDir + QStringLiteral("/recent_characters.json");

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isArray()) return;

    for (const auto& val : doc.array()) {
        m_recentList.append(val.toString());
    }
}

} // namespace stowaway::core
