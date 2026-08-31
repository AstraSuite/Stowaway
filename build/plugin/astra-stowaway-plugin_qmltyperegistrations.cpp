/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#if __has_include(<appcontroller.hpp>)
#  include <appcontroller.hpp>
#endif
#if __has_include(<clipboarditem.hpp>)
#  include <clipboarditem.hpp>
#endif
#if __has_include(<clipboardmanager.hpp>)
#  include <clipboardmanager.hpp>
#endif
#if __has_include(<colours.hpp>)
#  include <colours.hpp>
#endif
#if __has_include(<emojiservice.hpp>)
#  include <emojiservice.hpp>
#endif
#if __has_include(<font.hpp>)
#  include <font.hpp>
#endif
#if __has_include(<fontbuilder.hpp>)
#  include <fontbuilder.hpp>
#endif
#if __has_include(<pastemanager.hpp>)
#  include <pastemanager.hpp>
#endif
#if __has_include(<positioncontroller.hpp>)
#  include <positioncontroller.hpp>
#endif
#if __has_include(<tokens.hpp>)
#  include <tokens.hpp>
#endif


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_Astra_Stowaway()
{
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    qmlRegisterTypesAndRevisions<stowaway::config::AnimCurves>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::config::AnimDurationTokens>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::config::ColoursSingleton>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::config::FontBuilder>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::config::FontBuilders>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::config::FontStyle>("Astra.Stowaway", 1);
    QMetaType::fromType<stowaway::config::FontStyleBase *>().id();
    qmlRegisterTypesAndRevisions<stowaway::config::FontTokens>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::config::IconFontStyle>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::config::M3Palette>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::config::PaddingTokens>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::config::RoundingTokens>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::config::SpacingTokens>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::config::TokensSingleton>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::core::AppController>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::core::ClipboardItem>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::core::ClipboardManager>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::core::EmojiService>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::core::PasteManager>("Astra.Stowaway", 1);
    qmlRegisterTypesAndRevisions<stowaway::core::PositionController>("Astra.Stowaway", 1);
    QT_WARNING_POP
    qmlRegisterModule("Astra.Stowaway", 1, 0);
}

static const QQmlModuleRegistration astraStowawayRegistration("Astra.Stowaway", qml_register_types_Astra_Stowaway);
