/****************************************************************************
** Meta object code from reading C++ file 'appcontroller.hpp'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/core/appcontroller.hpp"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appcontroller.hpp' doesn't include <QObject>."
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
struct qt_meta_tag_ZN8stowaway4core13AppControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::core::AppController::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway4core13AppControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::core::AppController",
        "QML.Element",
        "auto",
        "QML.Singleton",
        "true",
        "visibilityChanged",
        "",
        "activeTabChanged",
        "targetWindowAddressChanged",
        "toastMessageChanged",
        "toastVisibleChanged",
        "requestDismiss",
        "handleNewConnection",
        "handleHyprlandEvent",
        "showOverlay",
        "tab",
        "hideOverlay",
        "toggleOverlay",
        "showToast",
        "message",
        "quit",
        "dismissAndPasteText",
        "text",
        "targetAddress",
        "dismissAndPasteImage",
        "filePath",
        "visible",
        "activeTab",
        "targetWindowAddress",
        "toastMessage",
        "toastVisible"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'visibilityChanged'
        QtMocHelpers::SignalData<void()>(5, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'activeTabChanged'
        QtMocHelpers::SignalData<void()>(7, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'targetWindowAddressChanged'
        QtMocHelpers::SignalData<void()>(8, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'toastMessageChanged'
        QtMocHelpers::SignalData<void()>(9, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'toastVisibleChanged'
        QtMocHelpers::SignalData<void()>(10, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'requestDismiss'
        QtMocHelpers::SignalData<void()>(11, 6, QMC::AccessPublic, QMetaType::Void),
        // Slot 'handleNewConnection'
        QtMocHelpers::SlotData<void()>(12, 6, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleHyprlandEvent'
        QtMocHelpers::SlotData<void()>(13, 6, QMC::AccessPrivate, QMetaType::Void),
        // Method 'showOverlay'
        QtMocHelpers::MethodData<void(int)>(14, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Method 'showOverlay'
        QtMocHelpers::MethodData<void()>(14, 6, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void),
        // Method 'hideOverlay'
        QtMocHelpers::MethodData<void()>(16, 6, QMC::AccessPublic, QMetaType::Void),
        // Method 'toggleOverlay'
        QtMocHelpers::MethodData<void(int)>(17, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Method 'toggleOverlay'
        QtMocHelpers::MethodData<void()>(17, 6, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void),
        // Method 'showToast'
        QtMocHelpers::MethodData<void(const QString &)>(18, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 19 },
        }}),
        // Method 'quit'
        QtMocHelpers::MethodData<void()>(20, 6, QMC::AccessPublic, QMetaType::Void),
        // Method 'dismissAndPasteText'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(21, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 22 }, { QMetaType::QString, 23 },
        }}),
        // Method 'dismissAndPasteText'
        QtMocHelpers::MethodData<void(const QString &)>(21, 6, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 22 },
        }}),
        // Method 'dismissAndPasteImage'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(24, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 25 }, { QMetaType::QString, 23 },
        }}),
        // Method 'dismissAndPasteImage'
        QtMocHelpers::MethodData<void(const QString &)>(24, 6, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 25 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'visible'
        QtMocHelpers::PropertyData<bool>(26, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'activeTab'
        QtMocHelpers::PropertyData<int>(27, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'targetWindowAddress'
        QtMocHelpers::PropertyData<QString>(28, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'toastMessage'
        QtMocHelpers::PropertyData<QString>(29, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'toastVisible'
        QtMocHelpers::PropertyData<bool>(30, QMetaType::Bool, QMC::DefaultPropertyFlags, 4),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
    });
    return QtMocHelpers::metaObjectData<AppController, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::core::AppController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway4core13AppControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway4core13AppControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway4core13AppControllerE_t>.metaTypes,
    nullptr
} };

void stowaway::core::AppController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AppController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->visibilityChanged(); break;
        case 1: _t->activeTabChanged(); break;
        case 2: _t->targetWindowAddressChanged(); break;
        case 3: _t->toastMessageChanged(); break;
        case 4: _t->toastVisibleChanged(); break;
        case 5: _t->requestDismiss(); break;
        case 6: _t->handleNewConnection(); break;
        case 7: _t->handleHyprlandEvent(); break;
        case 8: _t->showOverlay((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->showOverlay(); break;
        case 10: _t->hideOverlay(); break;
        case 11: _t->toggleOverlay((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->toggleOverlay(); break;
        case 13: _t->showToast((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->quit(); break;
        case 15: _t->dismissAndPasteText((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 16: _t->dismissAndPasteText((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->dismissAndPasteImage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 18: _t->dismissAndPasteImage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::visibilityChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::activeTabChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::targetWindowAddressChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::toastMessageChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::toastVisibleChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::requestDismiss, 5))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->isVisible(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->activeTab(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->targetWindowAddress(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->toastMessage(); break;
        case 4: *reinterpret_cast<bool*>(_v) = _t->toastVisible(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setVisible(*reinterpret_cast<bool*>(_v)); break;
        case 1: _t->setActiveTab(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *stowaway::core::AppController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::core::AppController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway4core13AppControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int stowaway::core::AppController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
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
void stowaway::core::AppController::visibilityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void stowaway::core::AppController::activeTabChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void stowaway::core::AppController::targetWindowAddressChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void stowaway::core::AppController::toastMessageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void stowaway::core::AppController::toastVisibleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void stowaway::core::AppController::requestDismiss()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
