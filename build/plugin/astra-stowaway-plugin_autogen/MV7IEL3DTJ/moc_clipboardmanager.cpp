/****************************************************************************
** Meta object code from reading C++ file 'clipboardmanager.hpp'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/core/clipboardmanager.hpp"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clipboardmanager.hpp' doesn't include <QObject>."
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
struct qt_meta_tag_ZN8stowaway4core16ClipboardManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::core::ClipboardManager::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway4core16ClipboardManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::core::ClipboardManager",
        "QML.Element",
        "auto",
        "QML.Singleton",
        "true",
        "itemsChanged",
        "",
        "filteredItemsChanged",
        "filterQueryChanged",
        "onlyPinnedChanged",
        "filterTypeChanged",
        "filterPinnedOnlyChanged",
        "itemSelected",
        "content",
        "onTextWatcherReady",
        "onImageWatcherReady",
        "saveHistory",
        "selectItem",
        "id",
        "targetWindowAddress",
        "copyItem",
        "togglePin",
        "deleteItem",
        "clearHistory",
        "checkClipboard",
        "items",
        "QList<stowaway::core::ClipboardItem*>",
        "filteredItems",
        "filterQuery",
        "onlyPinned",
        "filterType",
        "filterPinnedOnly",
        "itemCount",
        "pinnedCount",
        "imageCount"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'itemsChanged'
        QtMocHelpers::SignalData<void()>(5, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'filteredItemsChanged'
        QtMocHelpers::SignalData<void()>(7, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'filterQueryChanged'
        QtMocHelpers::SignalData<void()>(8, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'onlyPinnedChanged'
        QtMocHelpers::SignalData<void()>(9, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'filterTypeChanged'
        QtMocHelpers::SignalData<void()>(10, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'filterPinnedOnlyChanged'
        QtMocHelpers::SignalData<void()>(11, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'itemSelected'
        QtMocHelpers::SignalData<void(const QString &)>(12, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 },
        }}),
        // Slot 'onTextWatcherReady'
        QtMocHelpers::SlotData<void()>(14, 6, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onImageWatcherReady'
        QtMocHelpers::SlotData<void()>(15, 6, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'saveHistory'
        QtMocHelpers::SlotData<void()>(16, 6, QMC::AccessPrivate, QMetaType::Void),
        // Method 'selectItem'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(17, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 18 }, { QMetaType::QString, 19 },
        }}),
        // Method 'selectItem'
        QtMocHelpers::MethodData<void(const QString &)>(17, 6, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 18 },
        }}),
        // Method 'copyItem'
        QtMocHelpers::MethodData<void(const QString &)>(20, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 18 },
        }}),
        // Method 'togglePin'
        QtMocHelpers::MethodData<void(const QString &)>(21, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 18 },
        }}),
        // Method 'deleteItem'
        QtMocHelpers::MethodData<void(const QString &)>(22, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 18 },
        }}),
        // Method 'clearHistory'
        QtMocHelpers::MethodData<void()>(23, 6, QMC::AccessPublic, QMetaType::Void),
        // Method 'checkClipboard'
        QtMocHelpers::MethodData<void()>(24, 6, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'items'
        QtMocHelpers::PropertyData<QList<stowaway::core::ClipboardItem*>>(25, 0x80000000 | 26, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'filteredItems'
        QtMocHelpers::PropertyData<QList<stowaway::core::ClipboardItem*>>(27, 0x80000000 | 26, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 1),
        // property 'filterQuery'
        QtMocHelpers::PropertyData<QString>(28, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'onlyPinned'
        QtMocHelpers::PropertyData<bool>(29, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'filterType'
        QtMocHelpers::PropertyData<int>(30, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'filterPinnedOnly'
        QtMocHelpers::PropertyData<bool>(31, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'itemCount'
        QtMocHelpers::PropertyData<int>(32, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'pinnedCount'
        QtMocHelpers::PropertyData<int>(33, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'imageCount'
        QtMocHelpers::PropertyData<int>(34, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
    });
    return QtMocHelpers::metaObjectData<ClipboardManager, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::core::ClipboardManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway4core16ClipboardManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway4core16ClipboardManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway4core16ClipboardManagerE_t>.metaTypes,
    nullptr
} };

void stowaway::core::ClipboardManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ClipboardManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->itemsChanged(); break;
        case 1: _t->filteredItemsChanged(); break;
        case 2: _t->filterQueryChanged(); break;
        case 3: _t->onlyPinnedChanged(); break;
        case 4: _t->filterTypeChanged(); break;
        case 5: _t->filterPinnedOnlyChanged(); break;
        case 6: _t->itemSelected((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->onTextWatcherReady(); break;
        case 8: _t->onImageWatcherReady(); break;
        case 9: _t->saveHistory(); break;
        case 10: _t->selectItem((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 11: _t->selectItem((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->copyItem((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 13: _t->togglePin((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->deleteItem((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->clearHistory(); break;
        case 16: _t->checkClipboard(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ClipboardManager::*)()>(_a, &ClipboardManager::itemsChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClipboardManager::*)()>(_a, &ClipboardManager::filteredItemsChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClipboardManager::*)()>(_a, &ClipboardManager::filterQueryChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClipboardManager::*)()>(_a, &ClipboardManager::onlyPinnedChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClipboardManager::*)()>(_a, &ClipboardManager::filterTypeChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClipboardManager::*)()>(_a, &ClipboardManager::filterPinnedOnlyChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClipboardManager::*)(const QString & )>(_a, &ClipboardManager::itemSelected, 6))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<stowaway::core::ClipboardItem*> >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<stowaway::core::ClipboardItem*>*>(_v) = _t->items(); break;
        case 1: *reinterpret_cast<QList<stowaway::core::ClipboardItem*>*>(_v) = _t->filteredItems(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->filterQuery(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->onlyPinned(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->filterType(); break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->filterPinnedOnly(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->itemCount(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->pinnedCount(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->imageCount(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setFilterQuery(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setOnlyPinned(*reinterpret_cast<bool*>(_v)); break;
        case 4: _t->setFilterType(*reinterpret_cast<int*>(_v)); break;
        case 5: _t->setFilterPinnedOnly(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *stowaway::core::ClipboardManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::core::ClipboardManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway4core16ClipboardManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int stowaway::core::ClipboardManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void stowaway::core::ClipboardManager::itemsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void stowaway::core::ClipboardManager::filteredItemsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void stowaway::core::ClipboardManager::filterQueryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void stowaway::core::ClipboardManager::onlyPinnedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void stowaway::core::ClipboardManager::filterTypeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void stowaway::core::ClipboardManager::filterPinnedOnlyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void stowaway::core::ClipboardManager::itemSelected(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}
QT_WARNING_POP
