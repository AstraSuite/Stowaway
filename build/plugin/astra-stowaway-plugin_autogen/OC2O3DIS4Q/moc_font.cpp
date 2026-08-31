/****************************************************************************
** Meta object code from reading C++ file 'font.hpp'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/config/font.hpp"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'font.hpp' doesn't include <QObject>."
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
struct qt_meta_tag_ZN8stowaway6config12FontBuildersE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::config::FontBuilders::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway6config12FontBuildersE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::config::FontBuilders",
        "QML.Element",
        "anonymous",
        "buildersChanged",
        "",
        "extraLarge",
        "stowaway::config::FontBuilder",
        "large",
        "medium",
        "small"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'buildersChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'extraLarge'
        QtMocHelpers::PropertyData<stowaway::config::FontBuilder>(5, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Final, 0),
        // property 'large'
        QtMocHelpers::PropertyData<stowaway::config::FontBuilder>(7, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Final, 0),
        // property 'medium'
        QtMocHelpers::PropertyData<stowaway::config::FontBuilder>(8, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Final, 0),
        // property 'small'
        QtMocHelpers::PropertyData<stowaway::config::FontBuilder>(9, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Final, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<FontBuilders, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::config::FontBuilders::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config12FontBuildersE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config12FontBuildersE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway6config12FontBuildersE_t>.metaTypes,
    nullptr
} };

void stowaway::config::FontBuilders::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FontBuilders *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->buildersChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (FontBuilders::*)()>(_a, &FontBuilders::buildersChanged, 0))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<stowaway::config::FontBuilder*>(_v) = _t->extraLarge(); break;
        case 1: *reinterpret_cast<stowaway::config::FontBuilder*>(_v) = _t->large(); break;
        case 2: *reinterpret_cast<stowaway::config::FontBuilder*>(_v) = _t->medium(); break;
        case 3: *reinterpret_cast<stowaway::config::FontBuilder*>(_v) = _t->small(); break;
        default: break;
        }
    }
}

const QMetaObject *stowaway::config::FontBuilders::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::config::FontBuilders::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config12FontBuildersE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int stowaway::config::FontBuilders::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void stowaway::config::FontBuilders::buildersChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
namespace {
struct qt_meta_tag_ZN8stowaway6config13FontStyleBaseE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::config::FontStyleBase::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway6config13FontStyleBaseE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::config::FontStyleBase",
        "fontsChanged",
        "",
        "extraLarge",
        "QFont",
        "large",
        "medium",
        "small",
        "builders",
        "stowaway::config::FontBuilders*"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'fontsChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'extraLarge'
        QtMocHelpers::PropertyData<QFont>(3, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Final, 0),
        // property 'large'
        QtMocHelpers::PropertyData<QFont>(5, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Final, 0),
        // property 'medium'
        QtMocHelpers::PropertyData<QFont>(6, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Final, 0),
        // property 'small'
        QtMocHelpers::PropertyData<QFont>(7, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Final, 0),
        // property 'builders'
        QtMocHelpers::PropertyData<stowaway::config::FontBuilders*>(8, 0x80000000 | 9, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<FontStyleBase, qt_meta_tag_ZN8stowaway6config13FontStyleBaseE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject stowaway::config::FontStyleBase::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config13FontStyleBaseE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config13FontStyleBaseE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway6config13FontStyleBaseE_t>.metaTypes,
    nullptr
} };

void stowaway::config::FontStyleBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FontStyleBase *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->fontsChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (FontStyleBase::*)()>(_a, &FontStyleBase::fontsChanged, 0))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stowaway::config::FontBuilders* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QFont*>(_v) = _t->extraLarge(); break;
        case 1: *reinterpret_cast<QFont*>(_v) = _t->large(); break;
        case 2: *reinterpret_cast<QFont*>(_v) = _t->medium(); break;
        case 3: *reinterpret_cast<QFont*>(_v) = _t->small(); break;
        case 4: *reinterpret_cast<stowaway::config::FontBuilders**>(_v) = _t->builders(); break;
        default: break;
        }
    }
}

const QMetaObject *stowaway::config::FontStyleBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::config::FontStyleBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config13FontStyleBaseE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int stowaway::config::FontStyleBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void stowaway::config::FontStyleBase::fontsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
namespace {
struct qt_meta_tag_ZN8stowaway6config9FontStyleE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::config::FontStyle::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway6config9FontStyleE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::config::FontStyle",
        "QML.Element",
        "anonymous"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<FontStyle, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::config::FontStyle::staticMetaObject = { {
    QMetaObject::SuperData::link<FontStyleBase::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config9FontStyleE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config9FontStyleE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway6config9FontStyleE_t>.metaTypes,
    nullptr
} };

void stowaway::config::FontStyle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FontStyle *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *stowaway::config::FontStyle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::config::FontStyle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config9FontStyleE_t>.strings))
        return static_cast<void*>(this);
    return FontStyleBase::qt_metacast(_clname);
}

int stowaway::config::FontStyle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FontStyleBase::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN8stowaway6config13IconFontStyleE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::config::IconFontStyle::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway6config13IconFontStyleE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::config::IconFontStyle",
        "QML.Element",
        "anonymous",
        "size",
        "stowaway::config::FontBuilder",
        "",
        "pointSize"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'size'
        QtMocHelpers::MethodData<stowaway::config::FontBuilder(int)>(3, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::Int, 6 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<IconFontStyle, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::config::IconFontStyle::staticMetaObject = { {
    QMetaObject::SuperData::link<FontStyleBase::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config13IconFontStyleE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config13IconFontStyleE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway6config13IconFontStyleE_t>.metaTypes,
    nullptr
} };

void stowaway::config::IconFontStyle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<IconFontStyle *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { stowaway::config::FontBuilder _r = _t->size((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<stowaway::config::FontBuilder*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *stowaway::config::IconFontStyle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::config::IconFontStyle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config13IconFontStyleE_t>.strings))
        return static_cast<void*>(this);
    return FontStyleBase::qt_metacast(_clname);
}

int stowaway::config::IconFontStyle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FontStyleBase::qt_metacall(_c, _id, _a);
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
    return _id;
}
namespace {
struct qt_meta_tag_ZN8stowaway6config10FontTokensE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::config::FontTokens::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway6config10FontTokensE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::config::FontTokens",
        "QML.Element",
        "anonymous",
        "headline",
        "stowaway::config::FontStyle*",
        "title",
        "body",
        "label",
        "mono",
        "icon",
        "stowaway::config::IconFontStyle*"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'headline'
        QtMocHelpers::PropertyData<stowaway::config::FontStyle*>(3, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'title'
        QtMocHelpers::PropertyData<stowaway::config::FontStyle*>(5, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'body'
        QtMocHelpers::PropertyData<stowaway::config::FontStyle*>(6, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'label'
        QtMocHelpers::PropertyData<stowaway::config::FontStyle*>(7, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'mono'
        QtMocHelpers::PropertyData<stowaway::config::FontStyle*>(8, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'icon'
        QtMocHelpers::PropertyData<stowaway::config::IconFontStyle*>(9, 0x80000000 | 10, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<FontTokens, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::config::FontTokens::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config10FontTokensE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config10FontTokensE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway6config10FontTokensE_t>.metaTypes,
    nullptr
} };

void stowaway::config::FontTokens::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FontTokens *>(_o);
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
        case 3:
        case 2:
        case 1:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stowaway::config::FontStyle* >(); break;
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< stowaway::config::IconFontStyle* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<stowaway::config::FontStyle**>(_v) = _t->headline(); break;
        case 1: *reinterpret_cast<stowaway::config::FontStyle**>(_v) = _t->title(); break;
        case 2: *reinterpret_cast<stowaway::config::FontStyle**>(_v) = _t->body(); break;
        case 3: *reinterpret_cast<stowaway::config::FontStyle**>(_v) = _t->label(); break;
        case 4: *reinterpret_cast<stowaway::config::FontStyle**>(_v) = _t->mono(); break;
        case 5: *reinterpret_cast<stowaway::config::IconFontStyle**>(_v) = _t->icon(); break;
        default: break;
        }
    }
}

const QMetaObject *stowaway::config::FontTokens::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stowaway::config::FontTokens::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config10FontTokensE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int stowaway::config::FontTokens::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
