cmake_minimum_required(VERSION 3.19)

set(STOWAWAY_VERSION "1.0.0" CACHE STRING "Version of stowaway")

project(stowaway VERSION ${STOWAWAY_VERSION} LANGUAGES CXX)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "Default install prefix" FORCE)
endif()

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# System configuration directory for quickshell
set(INSTALL_QSCONFDIR "/etc/xdg/quickshell/astra-stowaway"
    CACHE STRING "Quickshell config install dir")

add_subdirectory(plugin)

# Build launcher binary (installed as stowaway)
add_executable(stowaway-launcher launcher/main.cpp)
target_compile_definitions(stowaway-launcher PRIVATE
    STOWAWAY_VERSION="${PROJECT_VERSION}"
)
set_target_properties(stowaway-launcher PROPERTIES
    OUTPUT_NAME "stowaway"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

install(TARGETS stowaway-launcher RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

# Install QML sources and assets for Quickshell
install(DIRECTORY qml assets
    DESTINATION "${INSTALL_QSCONFDIR}"
)
install(FILES shell.qml
    DESTINATION "${INSTALL_QSCONFDIR}"
)
install(FILES README.md OPTIONAL
    DESTINATION "${INSTALL_QSCONFDIR}"
)

install(FILES assets/stowaway.desktop
    DESTINATION "${CMAKE_INSTALL_DATADIR}/applications"
)

install(FILES assets/stowaway.svg
    DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps"
    RENAME stowaway.svg
)

install(FILES assets/stowaway.service
    DESTINATION "${CMAKE_INSTALL_DATADIR}/systemd/user"
)
