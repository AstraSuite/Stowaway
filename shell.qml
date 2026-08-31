pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import Quickshell
import Quickshell.Wayland
import Astra.Stowaway
import "qml/components"
import "qml/components/effects"
import "qml/views"

ShellRoot {
    id: shellRoot

    FontLoader {
        source: Qt.resolvedUrl("assets/fonts/GoogleSansFlex.ttf")
    }
    FontLoader {
        source: Qt.resolvedUrl("assets/fonts/MaterialSymbolsRounded.ttf")
    }

    Component.onCompleted: {
        ClipboardManager.checkClipboard();
    }

    Variants {
        model: Quickshell.screens

        delegate: PanelWindow {
            id: layerWindow
            required property var modelData
            screen: modelData

            WlrLayershell.layer: WlrLayer.Overlay
            WlrLayershell.keyboardFocus: WlrKeyboardFocus.Exclusive
            WlrLayershell.namespace: "stowaway"

            anchors.top: true
            anchors.bottom: true
            anchors.left: true
            anchors.right: true

            color: "transparent"
            visible: true

            readonly property bool isCurrentMonitor: (modelData.name === PositionController.monitorName || Quickshell.screens.length === 1)
            property bool overlayActive: false

            Component.onCompleted: {
                if (isCurrentMonitor) {
                    PositionController.calculatePosition(390, 500);
                }
                overlayActive = true;
            }

            function dismissWithAnimation() {
                if (!overlayActive) return;
                overlayActive = false;
                AppController.hideOverlay();
            }

            // Click outside anywhere on ANY monitor dismisses overlay immediately
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: (mouse) => {
                    if (!layerWindow.isCurrentMonitor) {
                        layerWindow.dismissWithAnimation();
                    } else if (mouse.x < popupCard.x || mouse.x > popupCard.x + popupCard.width ||
                               mouse.y < popupCard.y || mouse.y > popupCard.y + popupCard.height) {
                        layerWindow.dismissWithAnimation();
                    }
                }
            }

            Connections {
                target: PasteManager
                function onContentCopied(msg) {
                    AppController.showToast(msg);
                }
            }

            Connections {
                target: AppController
                function onRequestDismiss() {
                    if (overlayActive)
                        overlayActive = false;
                    closeLayerTimer.restart();
                }
            }

            // After the exit animation completes, fully unmap the layer so it releases
            // keyboard focus. C++ then sends the paste keystroke to the refocused target.
            Timer {
                id: closeLayerTimer
                interval: 260
                onTriggered: {
                    layerWindow.visible = false;
                }
            }

            onVisibleChanged: {
                if (visible) {
                    if (isCurrentMonitor) {
                        PositionController.calculatePosition(390, 500);
                    }
                    overlayActive = true;
                    focusSearch.restart();
                }
            }

            Timer {
                id: focusSearch
                interval: 30
                onTriggered: {
                    if (overlayActive)
                        popupCard.searchBar.forceActiveFocus();
                }
            }

            // Popup Container positioned dynamically beside the mouse cursor on the active monitor
            Item {
                id: popupCard
                visible: layerWindow.isCurrentMonitor
                x: PositionController.targetX - PositionController.monitorX
                y: (PositionController.targetY - PositionController.monitorY) + (layerWindow.overlayActive ? 0 : 12)
                width: 390
                height: 500

                Keys.onPressed: (event) => {
                    if (event.key === Qt.Key_Escape) {
                        event.accepted = true;
                        if (previewModal.active) {
                            previewModal.active = false;
                        } else {
                            layerWindow.dismissWithAnimation();
                        }
                    } else if (event.modifiers & Qt.ControlModifier) {
                        if (event.key === Qt.Key_1) { AppController.activeTab = 0; event.accepted = true; }
                        else if (event.key === Qt.Key_2) { AppController.activeTab = 1; event.accepted = true; }
                        else if (event.key === Qt.Key_3) { AppController.activeTab = 2; event.accepted = true; }
                        else if (event.key === Qt.Key_4) { AppController.activeTab = 3; event.accepted = true; }
                    }
                }

                scale: layerWindow.overlayActive ? 1.0 : 0.88
                opacity: layerWindow.overlayActive ? 1.0 : 0.0

                Behavior on scale {
                    Anim { type: Anim.DefaultSpatial; duration: 250 }
                }
                Behavior on opacity {
                    Anim { type: Anim.FastEffects; duration: 200 }
                }
                Behavior on y {
                    Anim { type: Anim.DefaultSpatial; duration: 250 }
                }

                // Material 3 Expressive Elevation Shadow (No hard borders!)
                Elevation {
                    level: 3
                    anchors.fill: mainSurface
                }

                // Main Card Surface
                StyledRect {
                    id: mainSurface
                    anchors.fill: parent
                    radius: Tokens.rounding.extraLarge
                    color: Colours.palette.m3surfaceContainer
                    clip: true

                    Column {
                        anchors.fill: parent
                        anchors.margins: 14
                        spacing: 10

                        // Top Search Bar
                        SearchBar {
                            id: searchBar
                            width: parent.width
                            placeholderText: {
                                switch (AppController.activeTab) {
                                    case 1: return "Search emojis...";
                                    case 2: return "Search kaomoji expressions...";
                                    case 3: return "Search unicode symbols...";
                                    default: return "Search clipboard history...";
                                }
                            }

                            onTextChanged: {
                                if (AppController.activeTab === 0) {
                                    ClipboardManager.filterQuery = text;
                                }
                            }

                            onSearchCleared: {
                                if (AppController.activeTab === 0) {
                                    ClipboardManager.filterQuery = "";
                                }
                            }

                            onNavigationKeyPressed: (key) => {
                                switch (AppController.activeTab) {
                                    case 0: clipboardView.moveSelection(key); break;
                                    case 1: emojiView.moveSelection(key); break;
                                    case 2: kaomojiView.moveSelection(key); break;
                                    case 3: symbolsView.moveSelection(key); break;
                                }
                            }

                            onSearchSubmitted: {
                                switch (AppController.activeTab) {
                                    case 0: clipboardView.activateSelection(); break;
                                    case 1: emojiView.activateSelection(); break;
                                    case 2: kaomojiView.activateSelection(); break;
                                    case 3: symbolsView.activateSelection(); break;
                                }
                            }
                        }

                        // Segmented Tab Switcher
                        SegmentedTabBar {
                            id: tabNav
                            width: parent.width
                            currentIndex: AppController.activeTab
                            onTabSelected: idx => AppController.activeTab = idx
                        }

                        // Content View Stack with Fluid Tab Switching Transitions
                        Item {
                            id: viewStack
                            width: parent.width
                            height: parent.height - searchBar.height - tabNav.height - 40
                            clip: true

                            Item {
                                anchors.fill: parent
                                visible: opacity > 0.01
                                opacity: AppController.activeTab === 0 ? 1.0 : 0.0
                                x: AppController.activeTab === 0 ? 0 : (AppController.activeTab > 0 ? -24 : 24)

                                Behavior on opacity {
                                    Anim { type: Anim.FastEffects; duration: 200 }
                                }
                                Behavior on x {
                                    Anim { type: Anim.DefaultSpatial; duration: 220 }
                                }

                                ClipboardView {
                                    id: clipboardView
                                    anchors.fill: parent
                                    onPreviewRequested: (img, txt, title) => {
                                        previewModal.imagePath = img;
                                        previewModal.textContent = txt;
                                        previewModal.title = title;
                                        previewModal.active = true;
                                    }
                                }
                            }

                            Item {
                                anchors.fill: parent
                                visible: opacity > 0.01
                                opacity: AppController.activeTab === 1 ? 1.0 : 0.0
                                x: AppController.activeTab === 1 ? 0 : (AppController.activeTab > 1 ? -24 : 24)

                                Behavior on opacity {
                                    Anim { type: Anim.FastEffects; duration: 200 }
                                }
                                Behavior on x {
                                    Anim { type: Anim.DefaultSpatial; duration: 220 }
                                }

                                EmojiView {
                                    id: emojiView
                                    anchors.fill: parent
                                    searchQuery: searchBar.text
                                }
                            }

                            Item {
                                anchors.fill: parent
                                visible: opacity > 0.01
                                opacity: AppController.activeTab === 2 ? 1.0 : 0.0
                                x: AppController.activeTab === 2 ? 0 : (AppController.activeTab > 2 ? -24 : 24)

                                Behavior on opacity {
                                    Anim { type: Anim.FastEffects; duration: 200 }
                                }
                                Behavior on x {
                                    Anim { type: Anim.DefaultSpatial; duration: 220 }
                                }

                                KaomojiView {
                                    id: kaomojiView
                                    anchors.fill: parent
                                    searchQuery: searchBar.text
                                }
                            }

                            Item {
                                anchors.fill: parent
                                visible: opacity > 0.01
                                opacity: AppController.activeTab === 3 ? 1.0 : 0.0
                                x: AppController.activeTab === 3 ? 0 : (AppController.activeTab > 3 ? -24 : 24)

                                Behavior on opacity {
                                    Anim { type: Anim.FastEffects; duration: 200 }
                                }
                                Behavior on x {
                                    Anim { type: Anim.DefaultSpatial; duration: 220 }
                                }

                                SymbolsView {
                                    id: symbolsView
                                    anchors.fill: parent
                                    searchQuery: searchBar.text
                                }
                            }
                        }

                        // Bottom Status & Shortcut Hints Bar
                        Item {
                            width: parent.width
                            height: 18

                            Row {
                                anchors.centerIn: parent
                                spacing: 8

                                StyledText {
                                    text: "↵ Paste"
                                    font: Tokens.font.label.small
                                    color: Colours.palette.m3onSurfaceVariant
                                    opacity: 0.7
                                }
                                StyledText {
                                    text: "•"
                                    font: Tokens.font.label.small
                                    color: Colours.palette.m3outline
                                    opacity: 0.4
                                }
                                StyledText {
                                    text: "Ctrl+1..4 Tabs"
                                    font: Tokens.font.label.small
                                    color: Colours.palette.m3onSurfaceVariant
                                    opacity: 0.7
                                }
                                StyledText {
                                    text: "•"
                                    font: Tokens.font.label.small
                                    color: Colours.palette.m3outline
                                    opacity: 0.4
                                }
                                StyledText {
                                    text: "Esc Dismiss"
                                    font: Tokens.font.label.small
                                    color: Colours.palette.m3onSurfaceVariant
                                    opacity: 0.7
                                }
                            }
                        }
                    }

                    // Preview Zoom Modal
                    PreviewModal {
                        id: previewModal
                    }

                    // Toast Feedback
                    Toast {
                        id: toast
                        message: AppController.toastMessage
                        show: AppController.toastVisible
                    }
                }
            }
        }
    }
}
