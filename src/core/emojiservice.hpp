#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>
#include <QHash>
#include <QVariantList>
#include <QJSEngine>
#include <QQmlEngine>
#include <qqmlintegration.h>

namespace stowaway::core {

struct CharacterItem {
    QString character;
    QString name;
    QString category;
    QString keywords;
    int index = 0;
};

class EmojiService : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QStringList emojiCategories READ emojiCategories NOTIFY datasetsLoaded)
    Q_PROPERTY(QStringList kaomojiCategories READ kaomojiCategories NOTIFY datasetsLoaded)
    Q_PROPERTY(QStringList symbolCategories READ symbolCategories NOTIFY datasetsLoaded)
    Q_PROPERTY(QVariantList recentList READ recentList NOTIFY recentChanged)
    Q_PROPERTY(QStringList favoritesList READ favoritesList NOTIFY favoritesChanged)

public:
    static EmojiService* instance();
    static EmojiService* create(QQmlEngine* = nullptr, QJSEngine* = nullptr) {
        auto* inst = instance();
        QJSEngine::setObjectOwnership(inst, QJSEngine::CppOwnership);
        return inst;
    }

    QStringList emojiCategories() const { return m_emojiCategories; }
    QStringList kaomojiCategories() const { return m_kaomojiCategories; }
    QStringList symbolCategories() const { return m_symbolCategories; }
    QVariantList recentList() const { return m_recentList; }
    QStringList favoritesList() const { return m_favorites; }

    Q_INVOKABLE QVariantList searchEmojis(const QString& query = QString(), const QString& category = QString());
    Q_INVOKABLE QVariantList searchKaomoji(const QString& query = QString(), const QString& category = QString());
    Q_INVOKABLE QVariantList searchSymbols(const QString& query = QString(), const QString& category = QString());
    Q_INVOKABLE bool isFavorite(const QString& character) const;
    Q_INVOKABLE void toggleFavorite(const QString& character, const QString& name = QString(), const QString& type = QStringLiteral("emoji"));
    Q_INVOKABLE void recordUsage(const QString& character, const QString& name = QString(), const QString& type = QStringLiteral("emoji"));
    Q_INVOKABLE void loadDatasets();

signals:
    void datasetsLoaded();
    void recentChanged();
    void favoritesChanged();

private:
    explicit EmojiService(QObject* parent = nullptr);

    QList<CharacterItem> m_emojis;
    QList<CharacterItem> m_kaomoji;
    QList<CharacterItem> m_symbols;

    QStringList m_emojiCategories;
    QStringList m_kaomojiCategories;
    QStringList m_symbolCategories;

    QVariantList m_recentList;
    QStringList m_favorites;
    QHash<QString, int> m_usageCounts;

    void loadRecent();
    void loadFavorites();
    void saveFavorites();
    void loadUsageCounts();
    void saveUsageCounts();

    QVariantList sortAndFilter(const QList<CharacterItem>& list, const QString& query, const QString& category);
};

} // namespace stowaway::core
