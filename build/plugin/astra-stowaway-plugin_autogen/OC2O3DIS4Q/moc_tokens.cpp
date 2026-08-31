/****************************************************************************
** Meta object code from reading C++ file 'tokens.hpp'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/config/tokens.hpp"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tokens.hpp' doesn't include <QObject>."
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
struct qt_meta_tag_ZN8stowaway6config14RoundingTokensE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::config::RoundingTokens::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway6config14RoundingTokensE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::config::RoundingTokens",
        "QML.Element",
        "anonymous",
        "valuesChanged",
        "",
        "scale",
        "extraSmall",
        "small",
        "medium",
        "large",
        "largeIncreased",
        "extraLarge",
        "extraLargeIncreased",
        "extraExtraLarge",
        "full"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'valuesChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'scale'
        QtMocHelpers::PropertyData<qreal>(5, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'extraSmall'
        QtMocHelpers::PropertyData<int>(6, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'small'
        QtMocHelpers::PropertyData<int>(7, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'medium'
        QtMocHelpers::PropertyData<int>(8, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'large'
        QtMocHelpers::PropertyData<int>(9, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'largeIncreased'
        QtMocHelpers::PropertyData<int>(10, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'extraLarge'
        QtMocHelpers::PropertyData<int>(11, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'extraLargeIncreased'
        QtMocHelpers::PropertyData<int>(12, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'extraExtraLarge'
        QtMocHelpers::PropertyData<int>(13, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'full'
        QtMocHelpers::PropertyData<int>(14, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<RoundingTokens, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::config::RoundingTokens::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config14RoundingTokensE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config14RoundingTokensE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway6config14RoundingTokensE_t>.metaTypes,
    nullptr
} };

void stowaway::config::RoundingTokens::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<RoundingTokens *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->valuesChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (RoundingTokens::*)()>(_a, &RoundingTokens::valuesChanged, 0))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<qreal*>(_v) = _t->scale(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->extraSmall(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->small(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->medium(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->large(); break;
        case 5: *reinterpret_cast<int*>(_v) = _t->largeIncreased(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->extraLarge(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->extraLargeIncreased(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->extraExtraLarge(); break;
        case 9: *reinterpret_cast<int*>(_v) = _t->full(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setScale(*reinterpret_cast<qreal*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *stowaway::config::RoundingTokens::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::config::RoundingTokens::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config14RoundingTokensE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int stowaway::config::RoundingTokens::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void stowaway::config::RoundingTokens::valuesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
namespace {
struct qt_meta_tag_ZN8stowaway6config13SpacingTokensE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::config::SpacingTokens::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway6config13SpacingTokensE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::config::SpacingTokens",
        "QML.Element",
        "anonymous",
        "valuesChanged",
        "",
        "scale",
        "extraSmall",
        "small",
        "medium",
        "large",
        "largeIncreased",
        "extraLarge",
        "extraLargeIncreased",
        "extraExtraLarge"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'valuesChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'scale'
        QtMocHelpers::PropertyData<qreal>(5, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'extraSmall'
        QtMocHelpers::PropertyData<int>(6, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'small'
        QtMocHelpers::PropertyData<int>(7, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'medium'
        QtMocHelpers::PropertyData<int>(8, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'large'
        QtMocHelpers::PropertyData<int>(9, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'largeIncreased'
        QtMocHelpers::PropertyData<int>(10, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'extraLarge'
        QtMocHelpers::PropertyData<int>(11, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'extraLargeIncreased'
        QtMocHelpers::PropertyData<int>(12, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'extraExtraLarge'
        QtMocHelpers::PropertyData<int>(13, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<SpacingTokens, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::config::SpacingTokens::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config13SpacingTokensE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config13SpacingTokensE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway6config13SpacingTokensE_t>.metaTypes,
    nullptr
} };

void stowaway::config::SpacingTokens::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SpacingTokens *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->valuesChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SpacingTokens::*)()>(_a, &SpacingTokens::valuesChanged, 0))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<qreal*>(_v) = _t->scale(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->extraSmall(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->small(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->medium(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->large(); break;
        case 5: *reinterpret_cast<int*>(_v) = _t->largeIncreased(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->extraLarge(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->extraLargeIncreased(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->extraExtraLarge(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setScale(*reinterpret_cast<qreal*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *stowaway::config::SpacingTokens::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::config::SpacingTokens::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config13SpacingTokensE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int stowaway::config::SpacingTokens::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
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
void stowaway::config::SpacingTokens::valuesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
namespace {
struct qt_meta_tag_ZN8stowaway6config13PaddingTokensE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::config::PaddingTokens::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway6config13PaddingTokensE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::config::PaddingTokens",
        "QML.Element",
        "anonymous",
        "valuesChanged",
        "",
        "scale",
        "extraSmall",
        "small",
        "medium",
        "large",
        "largeIncreased",
        "extraLarge",
        "extraLargeIncreased",
        "extraExtraLarge"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'valuesChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'scale'
        QtMocHelpers::PropertyData<qreal>(5, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'extraSmall'
        QtMocHelpers::PropertyData<int>(6, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'small'
        QtMocHelpers::PropertyData<int>(7, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'medium'
        QtMocHelpers::PropertyData<int>(8, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'large'
        QtMocHelpers::PropertyData<int>(9, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'largeIncreased'
        QtMocHelpers::PropertyData<int>(10, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'extraLarge'
        QtMocHelpers::PropertyData<int>(11, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'extraLargeIncreased'
        QtMocHelpers::PropertyData<int>(12, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'extraExtraLarge'
        QtMocHelpers::PropertyData<int>(13, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<PaddingTokens, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::config::PaddingTokens::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config13PaddingTokensE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config13PaddingTokensE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway6config13PaddingTokensE_t>.metaTypes,
    nullptr
} };

void stowaway::config::PaddingTokens::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PaddingTokens *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->valuesChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PaddingTokens::*)()>(_a, &PaddingTokens::valuesChanged, 0))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<qreal*>(_v) = _t->scale(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->extraSmall(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->small(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->medium(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->large(); break;
        case 5: *reinterpret_cast<int*>(_v) = _t->largeIncreased(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->extraLarge(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->extraLargeIncreased(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->extraExtraLarge(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setScale(*reinterpret_cast<qreal*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *stowaway::config::PaddingTokens::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::config::PaddingTokens::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config13PaddingTokensE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int stowaway::config::PaddingTokens::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
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
void stowaway::config::PaddingTokens::valuesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
namespace {
struct qt_meta_tag_ZN8stowaway6config18AnimDurationTokensE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::config::AnimDurationTokens::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway6config18AnimDurationTokensE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::config::AnimDurationTokens",
        "QML.Element",
        "anonymous",
        "valuesChanged",
        "",
        "scale",
        "small",
        "normal",
        "large",
        "extraLarge",
        "expressiveFastSpatial",
        "expressiveDefaultSpatial",
        "expressiveSlowSpatial",
        "expressiveFastEffects",
        "expressiveDefaultEffects",
        "expressiveSlowEffects"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'valuesChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'scale'
        QtMocHelpers::PropertyData<qreal>(5, QMetaType::QReal, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'small'
        QtMocHelpers::PropertyData<int>(6, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'normal'
        QtMocHelpers::PropertyData<int>(7, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'large'
        QtMocHelpers::PropertyData<int>(8, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'extraLarge'
        QtMocHelpers::PropertyData<int>(9, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'expressiveFastSpatial'
        QtMocHelpers::PropertyData<int>(10, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'expressiveDefaultSpatial'
        QtMocHelpers::PropertyData<int>(11, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'expressiveSlowSpatial'
        QtMocHelpers::PropertyData<int>(12, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'expressiveFastEffects'
        QtMocHelpers::PropertyData<int>(13, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'expressiveDefaultEffects'
        QtMocHelpers::PropertyData<int>(14, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'expressiveSlowEffects'
        QtMocHelpers::PropertyData<int>(15, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<AnimDurationTokens, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::config::AnimDurationTokens::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config18AnimDurationTokensE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config18AnimDurationTokensE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway6config18AnimDurationTokensE_t>.metaTypes,
    nullptr
} };

void stowaway::config::AnimDurationTokens::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AnimDurationTokens *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->valuesChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AnimDurationTokens::*)()>(_a, &AnimDurationTokens::valuesChanged, 0))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<qreal*>(_v) = _t->scale(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->small(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->normal(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->large(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->extraLarge(); break;
        case 5: *reinterpret_cast<int*>(_v) = _t->expressiveFastSpatial(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->expressiveDefaultSpatial(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->expressiveSlowSpatial(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->expressiveFastEffects(); break;
        case 9: *reinterpret_cast<int*>(_v) = _t->expressiveDefaultEffects(); break;
        case 10: *reinterpret_cast<int*>(_v) = _t->expressiveSlowEffects(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setScale(*reinterpret_cast<qreal*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *stowaway::config::AnimDurationTokens::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::config::AnimDurationTokens::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config18AnimDurationTokensE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int stowaway::config::AnimDurationTokens::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void stowaway::config::AnimDurationTokens::valuesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
namespace {
struct qt_meta_tag_ZN8stowaway6config10AnimCurvesE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::config::AnimCurves::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway6config10AnimCurvesE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::config::AnimCurves",
        "QML.Element",
        "anonymous",
        "curvesChanged",
        "",
        "emphasized",
        "QEasingCurve",
        "emphasizedAccel",
        "emphasizedDecel",
        "standard",
        "standardAccel",
        "standardDecel",
        "expressiveFastSpatial",
        "expressiveDefaultSpatial",
        "expressiveSlowSpatial",
        "expressiveFastEffects",
        "expressiveDefaultEffects",
        "expressiveSlowEffects",
        "durations",
        "stowaway::config::AnimDurationTokens*"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'curvesChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'emphasized'
        QtMocHelpers::PropertyData<QEasingCurve>(5, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'emphasizedAccel'
        QtMocHelpers::PropertyData<QEasingCurve>(7, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'emphasizedDecel'
        QtMocHelpers::PropertyData<QEasingCurve>(8, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'standard'
        QtMocHelpers::PropertyData<QEasingCurve>(9, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'standardAccel'
        QtMocHelpers::PropertyData<QEasingCurve>(10, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'standardDecel'
        QtMocHelpers::PropertyData<QEasingCurve>(11, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'expressiveFastSpatial'
        QtMocHelpers::PropertyData<QEasingCurve>(12, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'expressiveDefaultSpatial'
        QtMocHelpers::PropertyData<QEasingCurve>(13, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'expressiveSlowSpatial'
        QtMocHelpers::PropertyData<QEasingCurve>(14, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'expressiveFastEffects'
        QtMocHelpers::PropertyData<QEasingCurve>(15, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'expressiveDefaultEffects'
        QtMocHelpers::PropertyData<QEasingCurve>(16, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'expressiveSlowEffects'
        QtMocHelpers::PropertyData<QEasingCurve>(17, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'durations'
        QtMocHelpers::PropertyData<stowaway::config::AnimDurationTokens*>(18, 0x80000000 | 19, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<AnimCurves, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::config::AnimCurves::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config10AnimCurvesE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config10AnimCurvesE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway6config10AnimCurvesE_t>.metaTypes,
    nullptr
} };

void stowaway::config::AnimCurves::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AnimCurves *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->curvesChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AnimCurves::*)()>(_a, &AnimCurves::curvesChanged, 0))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stowaway::config::AnimDurationTokens* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QEasingCurve*>(_v) = _t->emphasized(); break;
        case 1: *reinterpret_cast<QEasingCurve*>(_v) = _t->emphasizedAccel(); break;
        case 2: *reinterpret_cast<QEasingCurve*>(_v) = _t->emphasizedDecel(); break;
        case 3: *reinterpret_cast<QEasingCurve*>(_v) = _t->standard(); break;
        case 4: *reinterpret_cast<QEasingCurve*>(_v) = _t->standardAccel(); break;
        case 5: *reinterpret_cast<QEasingCurve*>(_v) = _t->standardDecel(); break;
        case 6: *reinterpret_cast<QEasingCurve*>(_v) = _t->expressiveFastSpatial(); break;
        case 7: *reinterpret_cast<QEasingCurve*>(_v) = _t->expressiveDefaultSpatial(); break;
        case 8: *reinterpret_cast<QEasingCurve*>(_v) = _t->expressiveSlowSpatial(); break;
        case 9: *reinterpret_cast<QEasingCurve*>(_v) = _t->expressiveFastEffects(); break;
        case 10: *reinterpret_cast<QEasingCurve*>(_v) = _t->expressiveDefaultEffects(); break;
        case 11: *reinterpret_cast<QEasingCurve*>(_v) = _t->expressiveSlowEffects(); break;
        case 12: *reinterpret_cast<stowaway::config::AnimDurationTokens**>(_v) = _t->durations(); break;
        default: break;
        }
    }
}

const QMetaObject *stowaway::config::AnimCurves::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::config::AnimCurves::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config10AnimCurvesE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int stowaway::config::AnimCurves::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void stowaway::config::AnimCurves::curvesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
namespace {
struct qt_meta_tag_ZN8stowaway6config15TokensSingletonE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::config::TokensSingleton::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway6config15TokensSingletonE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::config::TokensSingleton",
        "QML.Element",
        "Tokens",
        "QML.Singleton",
        "true",
        "rounding",
        "stowaway::config::RoundingTokens*",
        "spacing",
        "stowaway::config::SpacingTokens*",
        "padding",
        "stowaway::config::PaddingTokens*",
        "anim",
        "stowaway::config::AnimCurves*",
        "font",
        "stowaway::config::FontTokens*"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'rounding'
        QtMocHelpers::PropertyData<stowaway::config::RoundingTokens*>(5, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'spacing'
        QtMocHelpers::PropertyData<stowaway::config::SpacingTokens*>(7, 0x80000000 | 8, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'padding'
        QtMocHelpers::PropertyData<stowaway::config::PaddingTokens*>(9, 0x80000000 | 10, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'anim'
        QtMocHelpers::PropertyData<stowaway::config::AnimCurves*>(11, 0x80000000 | 12, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'font'
        QtMocHelpers::PropertyData<stowaway::config::FontTokens*>(13, 0x80000000 | 14, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
    });
    return QtMocHelpers::metaObjectData<TokensSingleton, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::config::TokensSingleton::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config15TokensSingletonE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config15TokensSingletonE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway6config15TokensSingletonE_t>.metaTypes,
    nullptr
} };

void stowaway::config::TokensSingleton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TokensSingleton *>(_o);
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stowaway::config::AnimCurves* >(); break;
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stowaway::config::FontTokens* >(); break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stowaway::config::PaddingTokens* >(); break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stowaway::config::RoundingTokens* >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stowaway::config::SpacingTokens* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<stowaway::config::RoundingTokens**>(_v) = _t->rounding(); break;
        case 1: *reinterpret_cast<stowaway::config::SpacingTokens**>(_v) = _t->spacing(); break;
        case 2: *reinterpret_cast<stowaway::config::PaddingTokens**>(_v) = _t->padding(); break;
        case 3: *reinterpret_cast<stowaway::config::AnimCurves**>(_v) = _t->anim(); break;
        case 4: *reinterpret_cast<stowaway::config::FontTokens**>(_v) = _t->font(); break;
        default: break;
        }
    }
}

const QMetaObject *stowaway::config::TokensSingleton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::config::TokensSingleton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config15TokensSingletonE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int stowaway::config::TokensSingleton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
