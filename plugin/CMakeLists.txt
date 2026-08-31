cmake_minimum_required(VERSION 3.19)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick DBus Svg Network)

qt_standard_project_setup(REQUIRES 6.5)

set(QT_QML_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qml")

qt_add_qml_module(astra-stowaway-plugin
    URI Astra.Stowaway
    VERSION 1.0
    SOURCES
        ../src/config/fontbuilder.hpp
        ../src/config/fontbuilder.cpp
        ../src/config/font.hpp
        ../src/config/font.cpp
        ../src/config/tokens.hpp
        ../src/config/tokens.cpp
        ../src/config/colours.hpp
        ../src/config/colours.cpp
        ../src/core/hyprlandipc.hpp
        ../src/core/hyprlandipc.cpp
        ../src/core/positioncontroller.hpp
        ../src/core/positioncontroller.cpp
        ../src/core/clipboarditem.hpp
        ../src/core/clipboarditem.cpp
        ../src/core/clipboardmanager.hpp
        ../src/core/clipboardmanager.cpp
        ../src/core/pastemanager.hpp
        ../src/core/pastemanager.cpp
        ../src/core/emojiservice.hpp
        ../src/core/emojiservice.cpp
        ../src/core/thumbnailprovider.hpp
        ../src/core/thumbnailprovider.cpp
        ../src/core/appcontroller.hpp
        ../src/core/appcontroller.cpp
    RESOURCES
        ../assets/fonts/GoogleSansFlex.ttf
        ../assets/fonts/MaterialSymbolsRounded.ttf
        ../assets/material_icons.txt
        ../assets/stowaway.svg
        ../assets/data/emojis.json
        ../assets/data/kaomoji.json
        ../assets/data/symbols.json
)

target_include_directories(astra-stowaway-plugin PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/config
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/core
)

target_link_libraries(astra-stowaway-plugin PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::DBus
    Qt6::Svg
    Qt6::Network
)

include(GNUInstallDirs)
set(INSTALL_QMLDIR "${CMAKE_INSTALL_LIBDIR}/qt6/qml"
    CACHE STRING "QML module install dir")

qt_query_qml_module(astra-stowaway-plugin
    URI module_uri
    PLUGIN_TARGET module_plugin_target
    TARGET_PATH module_target_path
    QMLDIR module_qmldir
    TYPEINFO module_typeinfo
)

install(TARGETS astra-stowaway-plugin
    LIBRARY DESTINATION "${INSTALL_QMLDIR}/${module_target_path}"
    RUNTIME DESTINATION "${INSTALL_QMLDIR}/${module_target_path}"
)
install(TARGETS "${module_plugin_target}"
    LIBRARY DESTINATION "${INSTALL_QMLDIR}/${module_target_path}"
    RUNTIME DESTINATION "${INSTALL_QMLDIR}/${module_target_path}"
)
install(FILES "${module_qmldir}" DESTINATION "${INSTALL_QMLDIR}/${module_target_path}")
install(FILES "${module_typeinfo}" DESTINATION "${INSTALL_QMLDIR}/${module_target_path}")
