{
  lib,
  stdenv,
  cmake,
  ninja,
  pkg-config,
  qt6,
  quickshell,
  wtype,
  wl-clipboard,
  cliphist,
}:
stdenv.mkDerivation (finalAttrs: {
  pname = "stowaway";
  version = "1.0.0";

  src = ./..;

  nativeBuildInputs = [
    cmake
    ninja
    pkg-config
    qt6.wrapQtAppsHook
  ];

  buildInputs = [
    qt6.qtbase
    qt6.qtdeclarative
    qt6.qtsvg
  ];

  cmakeFlags = [
    "-DINSTALL_QMLDIR=lib/qt6/qml"
    "-DINSTALL_QSCONFDIR=share/stowaway"
  ];

  postFixup = ''
    wrapProgram $out/bin/stowaway \
      --prefix PATH : ${lib.makeBinPath [ quickshell wtype wl-clipboard cliphist ]} \
      --prefix QML2_IMPORT_PATH : "$out/lib/qt6/qml" \
      --prefix QML_IMPORT_PATH : "$out/lib/qt6/qml" \
      --prefix LD_LIBRARY_PATH : "$out/lib/qt6/qml/Astra/Stowaway" \
      --set-default STOWAWAY_SHELL_QML "$out/share/stowaway/shell.qml" \
      --set-default STOWAWAY_QML_DIR "$out/lib/qt6/qml" \
      --set-default STOWAWAY_PLUGIN_DIR "$out/lib/qt6/qml/Astra/Stowaway"
  '';

  meta = with lib; {
    description = "A Wayland clipboard manager and character picker overlay for AstraSuite";
    homepage = "https://github.com/AstraSuite/Stowaway";
    license = licenses.gpl3Only;
    platforms = platforms.linux;
    mainProgram = "stowaway";
  };
})
