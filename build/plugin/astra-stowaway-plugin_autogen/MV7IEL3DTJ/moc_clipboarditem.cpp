/****************************************************************************
** Meta object code from reading C++ file 'clipboarditem.hpp'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/core/clipboarditem.hpp"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clipboarditem.hpp' doesn't include <QObject>."
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
struct qt_meta_tag_ZN8stowaway4core13ClipboardItemE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::core::ClipboardItem::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway4core13ClipboardItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::core::ClipboardItem",
        "QML.Element",
        "anonymous",
        "typeChanged",
        "",
        "contentChanged",
        "previewTextChanged",
        "imagePathChanged",
        "byteSizeChanged",
        "timestampChanged",
        "pinnedChanged",
        "colorHexChanged",
        "id",
        "type",
        "typeName",
        "content",
        "previewText",
        "previewLine1",
        "previewLine2",
        "imagePath",
        "imageWidth",
        "imageHeight",
        "byteSize",
        "lineCount",
        "charCount",
        "timestamp",
        "timeAgo",
        "pinned",
        "colorHex"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'typeChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'contentChanged'
        QtMocHelpers::SignalData<void()>(5, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'previewTextChanged'
        QtMocHelpers::SignalData<void()>(6, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'imagePathChanged'
        QtMocHelpers::SignalData<void()>(7, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'byteSizeChanged'
        QtMocHelpers::SignalData<void()>(8, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'timestampChanged'
        QtMocHelpers::SignalData<void()>(9, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'pinnedChanged'
        QtMocHelpers::SignalData<void()>(10, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'colorHexChanged'
        QtMocHelpers::SignalData<void()>(11, 4, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'id'
        QtMocHelpers::PropertyData<QString>(12, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'type'
        QtMocHelpers::PropertyData<int>(13, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'typeName'
        QtMocHelpers::PropertyData<QString>(14, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'content'
        QtMocHelpers::PropertyData<QString>(15, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'previewText'
        QtMocHelpers::PropertyData<QString>(16, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'previewLine1'
        QtMocHelpers::PropertyData<QString>(17, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'previewLine2'
        QtMocHelpers::PropertyData<QString>(18, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'imagePath'
        QtMocHelpers::PropertyData<QString>(19, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'imageWidth'
        QtMocHelpers::PropertyData<int>(20, QMetaType::Int, QMC::DefaultPropertyFlags, 3),
        // property 'imageHeight'
        QtMocHelpers::PropertyData<int>(21, QMetaType::Int, QMC::DefaultPropertyFlags, 3),
        // property 'byteSize'
        QtMocHelpers::PropertyData<qint64>(22, QMetaType::LongLong, QMC::DefaultPropertyFlags, 4),
        // property 'lineCount'
        QtMocHelpers::PropertyData<int>(23, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'charCount'
        QtMocHelpers::PropertyData<int>(24, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'timestamp'
        QtMocHelpers::PropertyData<QDateTime>(25, QMetaType::QDateTime, QMC::DefaultPropertyFlags, 5),
        // property 'timeAgo'
        QtMocHelpers::PropertyData<QString>(26, QMetaType::QString, QMC::DefaultPropertyFlags, 5),
        // property 'pinned'
        QtMocHelpers::PropertyData<bool>(27, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'colorHex'
        QtMocHelpers::PropertyData<QString>(28, QMetaType::QString, QMC::DefaultPropertyFlags, 7),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<ClipboardItem, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::core::ClipboardItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway4core13ClipboardItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway4core13ClipboardItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway4core13ClipboardItemE_t>.metaTypes,
    nullptr
} };

void stowaway::core::ClipboardItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ClipboardItem *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->typeChanged(); break;
        case 1: _t->contentChanged(); break;
        case 2: _t->previewTextChanged(); break;
        case 3: _t->imagePathChanged(); break;
        case 4: _t->byteSizeChanged(); break;
        case 5: _t->timestampChanged(); break;
        case 6: _t->pinnedChanged(); break;
        case 7: _t->colorHexChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ClipboardItem::*)()>(_a, &ClipboardItem::typeChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClipboardItem::*)()>(_a, &ClipboardItem::contentChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClipboardItem::*)()>(_a, &ClipboardItem::previewTextChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClipboardItem::*)()>(_a, &ClipboardItem::imagePathChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClipboardItem::*)()>(_a, &ClipboardItem::byteSizeChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClipboardItem::*)()>(_a, &ClipboardItem::timestampChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClipboardItem::*)()>(_a, &ClipboardItem::pinnedChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClipboardItem::*)()>(_a, &ClipboardItem::colorHexChanged, 7))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->id(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->typeInt(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->typeName(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->content(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->previewText(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->previewLine1(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->previewLine2(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->imagePath(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->imageWidth(); break;
        case 9: *reinterpret_cast<int*>(_v) = _t->imageHeight(); break;
        case 10: *reinterpret_cast<qint64*>(_v) = _t->byteSize(); break;
        case 11: *reinterpret_cast<int*>(_v) = _t->lineCount(); break;
        case 12: *reinterpret_cast<int*>(_v) = _t->charCount(); break;
        case 13: *reinterpret_cast<QDateTime*>(_v) = _t->timestamp(); break;
        case 14: *reinterpret_cast<QString*>(_v) = _t->timeAgo(); break;
        case 15: *reinterpret_cast<bool*>(_v) = _t->pinned(); break;
        case 16: *reinterpret_cast<QString*>(_v) = _t->colorHex(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 3: _t->setContent(*reinterpret_cast<QString*>(_v)); break;
        case 15: _t->setPinned(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *stowaway::core::ClipboardItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::core::ClipboardItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway4core13ClipboardItemE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int stowaway::core::ClipboardItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void stowaway::core::ClipboardItem::typeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void stowaway::core::ClipboardItem::contentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void stowaway::core::ClipboardItem::previewTextChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void stowaway::core::ClipboardItem::imagePathChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void stowaway::core::ClipboardItem::byteSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void stowaway::core::ClipboardItem::timestampChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void stowaway::core::ClipboardItem::pinnedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void stowaway::core::ClipboardItem::colorHexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
