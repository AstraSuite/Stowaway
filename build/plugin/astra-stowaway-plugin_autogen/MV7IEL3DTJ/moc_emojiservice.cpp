/****************************************************************************
** Meta object code from reading C++ file 'emojiservice.hpp'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/core/emojiservice.hpp"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'emojiservice.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN8stowaway4core12EmojiServiceE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::core::EmojiService::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway4core12EmojiServiceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::core::EmojiService",
        "QML.Element",
        "auto",
        "QML.Singleton",
        "true",
        "datasetsLoaded",
        "",
        "recentChanged",
        "favoritesChanged",
        "searchEmojis",
        "QVariantList",
        "query",
        "category",
        "searchKaomoji",
        "searchSymbols",
        "isFavorite",
        "character",
        "toggleFavorite",
        "name",
        "type",
        "recordUsage",
        "loadDatasets",
        "emojiCategories",
        "kaomojiCategories",
        "symbolCategories",
        "recentList",
        "favoritesList"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'datasetsLoaded'
        QtMocHelpers::SignalData<void()>(5, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'recentChanged'
        QtMocHelpers::SignalData<void()>(7, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'favoritesChanged'
        QtMocHelpers::SignalData<void()>(8, 6, QMC::AccessPublic, QMetaType::Void),
        // Method 'searchEmojis'
        QtMocHelpers::MethodData<QVariantList(const QString &, const QString &)>(9, 6, QMC::AccessPublic, 0x80000000 | 10, {{
            { QMetaType::QString, 11 }, { QMetaType::QString, 12 },
        }}),
        // Method 'searchEmojis'
        QtMocHelpers::MethodData<QVariantList(const QString &)>(9, 6, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 10, {{
            { QMetaType::QString, 11 },
        }}),
        // Method 'searchEmojis'
        QtMocHelpers::MethodData<QVariantList()>(9, 6, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 10),
        // Method 'searchKaomoji'
        QtMocHelpers::MethodData<QVariantList(const QString &, const QString &)>(13, 6, QMC::AccessPublic, 0x80000000 | 10, {{
            { QMetaType::QString, 11 }, { QMetaType::QString, 12 },
        }}),
        // Method 'searchKaomoji'
        QtMocHelpers::MethodData<QVariantList(const QString &)>(13, 6, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 10, {{
            { QMetaType::QString, 11 },
        }}),
        // Method 'searchKaomoji'
        QtMocHelpers::MethodData<QVariantList()>(13, 6, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 10),
        // Method 'searchSymbols'
        QtMocHelpers::MethodData<QVariantList(const QString &, const QString &)>(14, 6, QMC::AccessPublic, 0x80000000 | 10, {{
            { QMetaType::QString, 11 }, { QMetaType::QString, 12 },
        }}),
        // Method 'searchSymbols'
        QtMocHelpers::MethodData<QVariantList(const QString &)>(14, 6, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 10, {{
            { QMetaType::QString, 11 },
        }}),
        // Method 'searchSymbols'
        QtMocHelpers::MethodData<QVariantList()>(14, 6, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 10),
        // Method 'isFavorite'
        QtMocHelpers::MethodData<bool(const QString &) const>(15, 6, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 16 },
        }}),
        // Method 'toggleFavorite'
        QtMocHelpers::MethodData<void(const QString &, const QString &, const QString &)>(17, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 16 }, { QMetaType::QString, 18 }, { QMetaType::QString, 19 },
        }}),
        // Method 'toggleFavorite'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(17, 6, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 16 }, { QMetaType::QString, 18 },
        }}),
        // Method 'toggleFavorite'
        QtMocHelpers::MethodData<void(const QString &)>(17, 6, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 16 },
        }}),
        // Method 'recordUsage'
        QtMocHelpers::MethodData<void(const QString &, const QString &, const QString &)>(20, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 16 }, { QMetaType::QString, 18 }, { QMetaType::QString, 19 },
        }}),
        // Method 'recordUsage'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(20, 6, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 16 }, { QMetaType::QString, 18 },
        }}),
        // Method 'recordUsage'
        QtMocHelpers::MethodData<void(const QString &)>(20, 6, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 16 },
        }}),
        // Method 'loadDatasets'
        QtMocHelpers::MethodData<void()>(21, 6, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'emojiCategories'
        QtMocHelpers::PropertyData<QStringList>(22, QMetaType::QStringList, QMC::DefaultPropertyFlags, 0),
        // property 'kaomojiCategories'
        QtMocHelpers::PropertyData<QStringList>(23, QMetaType::QStringList, QMC::DefaultPropertyFlags, 0),
        // property 'symbolCategories'
        QtMocHelpers::PropertyData<QStringList>(24, QMetaType::QStringList, QMC::DefaultPropertyFlags, 0),
        // property 'recentList'
        QtMocHelpers::PropertyData<QVariantList>(25, 0x80000000 | 10, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 1),
        // property 'favoritesList'
        QtMocHelpers::PropertyData<QStringList>(26, QMetaType::QStringList, QMC::DefaultPropertyFlags, 2),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
    });
    return QtMocHelpers::metaObjectData<EmojiService, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::core::EmojiService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway4core12EmojiServiceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway4core12EmojiServiceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway4core12EmojiServiceE_t>.metaTypes,
    nullptr
} };

void stowaway::core::EmojiService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<EmojiService *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->datasetsLoaded(); break;
        case 1: _t->recentChanged(); break;
        case 2: _t->favoritesChanged(); break;
        case 3: { QVariantList _r = _t->searchEmojis((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 4: { QVariantList _r = _t->searchEmojis((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 5: { QVariantList _r = _t->searchEmojis();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 6: { QVariantList _r = _t->searchKaomoji((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 7: { QVariantList _r = _t->searchKaomoji((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 8: { QVariantList _r = _t->searchKaomoji();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 9: { QVariantList _r = _t->searchSymbols((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 10: { QVariantList _r = _t->searchSymbols((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 11: { QVariantList _r = _t->searchSymbols();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->isFavorite((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->toggleFavorite((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3]))); break;
        case 14: _t->toggleFavorite((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 15: _t->toggleFavorite((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->recordUsage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3]))); break;
        case 17: _t->recordUsage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 18: _t->recordUsage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 19: _t->loadDatasets(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (EmojiService::*)()>(_a, &EmojiService::datasetsLoaded, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (EmojiService::*)()>(_a, &EmojiService::recentChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (EmojiService::*)()>(_a, &EmojiService::favoritesChanged, 2))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QStringList*>(_v) = _t->emojiCategories(); break;
        case 1: *reinterpret_cast<QStringList*>(_v) = _t->kaomojiCategories(); break;
        case 2: *reinterpret_cast<QStringList*>(_v) = _t->symbolCategories(); break;
        case 3: *reinterpret_cast<QVariantList*>(_v) = _t->recentList(); break;
        case 4: *reinterpret_cast<QStringList*>(_v) = _t->favoritesList(); break;
        default: break;
        }
    }
}

const QMetaObject *stowaway::core::EmojiService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::core::EmojiService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway4core12EmojiServiceE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int stowaway::core::EmojiService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 20;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void stowaway::core::EmojiService::datasetsLoaded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void stowaway::core::EmojiService::recentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void stowaway::core::EmojiService::favoritesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
