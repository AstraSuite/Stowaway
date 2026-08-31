#pragma once

#include <QObject>
#include <QList>
#include <QTimer>
#include <QProcess>
#include <QJSEngine>
#include <QQmlEngine>
#include "clipboarditem.hpp"
#include <qqmlintegration.h>

namespace stowaway::core {

class ClipboardManager : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QList<stowaway::core::ClipboardItem*> items READ items NOTIFY itemsChanged)
    Q_PROPERTY(QList<stowaway::core::ClipboardItem*> filteredItems READ filteredItems NOTIFY filteredItemsChanged)
    Q_PROPERTY(QString filterQuery READ filterQuery WRITE setFilterQuery NOTIFY filterQueryChanged)
    Q_PROPERTY(bool onlyPinned READ onlyPinned WRITE setOnlyPinned NOTIFY onlyPinnedChanged)
    Q_PROPERTY(int filterType READ filterType WRITE setFilterType NOTIFY filterTypeChanged)
    Q_PROPERTY(bool filterPinnedOnly READ filterPinnedOnly WRITE setFilterPinnedOnly NOTIFY filterPinnedOnlyChanged)
    Q_PROPERTY(int itemCount READ itemCount NOTIFY itemsChanged)
    Q_PROPERTY(int pinnedCount READ pinnedCount NOTIFY itemsChanged)
    Q_PROPERTY(int imageCount READ imageCount NOTIFY itemsChanged)

public:
    explicit ClipboardManager(QObject* parent = nullptr);
    ~ClipboardManager() override;

    static ClipboardManager* instance();
    static ClipboardManager* create(QQmlEngine* = nullptr, QJSEngine* = nullptr) {
        auto* inst = instance();
        QJSEngine::setObjectOwnership(inst, QJSEngine::CppOwnership);
        return inst;
    }

    QList<ClipboardItem*> items() const { return m_items; }
    QList<ClipboardItem*> filteredItems() const { return m_filteredItems; }

    QString filterQuery() const { return m_filterQuery; }
    void setFilterQuery(const QString& query);

    bool onlyPinned() const { return m_onlyPinned; }
    void setOnlyPinned(bool pinned);

    int filterType() const { return m_filterType; }
    void setFilterType(int type);

    bool filterPinnedOnly() const { return m_filterPinnedOnly; }
    void setFilterPinnedOnly(bool pinnedOnly);

    int itemCount() const { return m_items.size(); }
    int pinnedCount() const;
    int imageCount() const;

    Q_INVOKABLE void selectItem(const QString& id, const QString& targetWindowAddress = QString());
    Q_INVOKABLE void copyItem(const QString& id);
    Q_INVOKABLE void togglePin(const QString& id);
    Q_INVOKABLE void deleteItem(const QString& id);
    Q_INVOKABLE void clearHistory();
    Q_INVOKABLE void checkClipboard();

signals:
    void itemsChanged();
    void filteredItemsChanged();
    void filterQueryChanged();
    void onlyPinnedChanged();
    void filterTypeChanged();
    void filterPinnedOnlyChanged();
    void itemSelected(const QString& content);

private slots:
    void onTextWatcherReady();
    void onImageWatcherReady();
    void saveHistory();

private:
    QList<ClipboardItem*> m_items;
    QList<ClipboardItem*> m_filteredItems;
    QString m_filterQuery;
    bool m_onlyPinned = false;
    int m_filterType = -1;
    bool m_filterPinnedOnly = false;

    void loadHistory();
    void updateFilteredItems();
    void addItem(ClipboardItem* item);
    void startWaylandWatchers();
};

} // namespace stowaway::core
