/****************************************************************************
** Meta object code from reading C++ file 'fontbuilder.hpp'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/config/fontbuilder.hpp"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fontbuilder.hpp' doesn't include <QObject>."
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
struct qt_meta_tag_ZN8stowaway6config11FontBuilderE_t {};
} // unnamed namespace

template <> constexpr inline auto stowaway::config::FontBuilder::qt_create_metaobjectdata<qt_meta_tag_ZN8stowaway6config11FontBuilderE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "stowaway::config::FontBuilder",
        "QML.Element",
        "anonymous",
        "family",
        "FontBuilder",
        "",
        "size",
        "pointSize",
        "weight",
        "QFont::Weight",
        "italic",
        "on",
        "stretch",
        "letterSpacing",
        "spacing",
        "absolute",
        "capitalisation",
        "QFont::Capitalization",
        "cap",
        "vaxis",
        "tag",
        "value",
        "vaxes",
        "QVariantMap",
        "axes",
        "build",
        "QFont",
        "fill",
        "grade",
        "width",
        "scale",
        "factor"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'family'
        QtMocHelpers::MethodData<FontBuilder(const QString &)>(3, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::QString, 3 },
        }}),
        // Method 'size'
        QtMocHelpers::MethodData<FontBuilder(int)>(6, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::Int, 7 },
        }}),
        // Method 'weight'
        QtMocHelpers::MethodData<FontBuilder(QFont::Weight)>(8, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { 0x80000000 | 9, 8 },
        }}),
        // Method 'italic'
        QtMocHelpers::MethodData<FontBuilder(bool)>(10, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::Bool, 11 },
        }}),
        // Method 'italic'
        QtMocHelpers::MethodData<FontBuilder()>(10, 5, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 4),
        // Method 'stretch'
        QtMocHelpers::MethodData<FontBuilder(int)>(12, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::Int, 12 },
        }}),
        // Method 'letterSpacing'
        QtMocHelpers::MethodData<FontBuilder(qreal, bool)>(13, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::QReal, 14 }, { QMetaType::Bool, 15 },
        }}),
        // Method 'letterSpacing'
        QtMocHelpers::MethodData<FontBuilder(qreal)>(13, 5, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 4, {{
            { QMetaType::QReal, 14 },
        }}),
        // Method 'capitalisation'
        QtMocHelpers::MethodData<FontBuilder(QFont::Capitalization)>(16, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { 0x80000000 | 17, 18 },
        }}),
        // Method 'vaxis'
        QtMocHelpers::MethodData<FontBuilder(const QString &, float)>(19, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::QString, 20 }, { QMetaType::Float, 21 },
        }}),
        // Method 'vaxes'
        QtMocHelpers::MethodData<FontBuilder(const QVariantMap &)>(22, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { 0x80000000 | 23, 24 },
        }}),
        // Method 'build'
        QtMocHelpers::MethodData<QFont() const>(25, 5, QMC::AccessPublic, 0x80000000 | 26),
        // Method 'fill'
        QtMocHelpers::MethodData<FontBuilder(float)>(27, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::Float, 21 },
        }}),
        // Method 'grade'
        QtMocHelpers::MethodData<FontBuilder(float)>(28, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::Float, 21 },
        }}),
        // Method 'width'
        QtMocHelpers::MethodData<FontBuilder(float)>(29, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::Float, 21 },
        }}),
        // Method 'scale'
        QtMocHelpers::MethodData<FontBuilder(qreal)>(30, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::QReal, 31 },
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
    return QtMocHelpers::metaObjectData<FontBuilder, void>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject stowaway::config::FontBuilder::staticMetaObject = { {
    nullptr,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config11FontBuilderE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8stowaway6config11FontBuilderE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8stowaway6config11FontBuilderE_t>.metaTypes,
    nullptr
} };

void stowaway::config::FontBuilder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<FontBuilder *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { FontBuilder _r = _t->family((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        case 1: { FontBuilder _r = _t->size((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        case 2: { FontBuilder _r = _t->weight((*reinterpret_cast<std::add_pointer_t<QFont::Weight>>(_a[1])));
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        case 3: { FontBuilder _r = _t->italic((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])));
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        case 4: { FontBuilder _r = _t->italic();
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        case 5: { FontBuilder _r = _t->stretch((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        case 6: { FontBuilder _r = _t->letterSpacing((*reinterpret_cast<std::add_pointer_t<qreal>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])));
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        case 7: { FontBuilder _r = _t->letterSpacing((*reinterpret_cast<std::add_pointer_t<qreal>>(_a[1])));
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        case 8: { FontBuilder _r = _t->capitalisation((*reinterpret_cast<std::add_pointer_t<QFont::Capitalization>>(_a[1])));
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        case 9: { FontBuilder _r = _t->vaxis((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<float>>(_a[2])));
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        case 10: { FontBuilder _r = _t->vaxes((*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[1])));
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        case 11: { QFont _r = _t->build();
            if (_a[0]) *reinterpret_cast<QFont*>(_a[0]) = std::move(_r); }  break;
        case 12: { FontBuilder _r = _t->fill((*reinterpret_cast<std::add_pointer_t<float>>(_a[1])));
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        case 13: { FontBuilder _r = _t->grade((*reinterpret_cast<std::add_pointer_t<float>>(_a[1])));
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        case 14: { FontBuilder _r = _t->width((*reinterpret_cast<std::add_pointer_t<float>>(_a[1])));
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        case 15: { FontBuilder _r = _t->scale((*reinterpret_cast<std::add_pointer_t<qreal>>(_a[1])));
            if (_a[0]) *reinterpret_cast<FontBuilder*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}
QT_WARNING_POP
