import QtQuick
import Astra.Stowaway
import "."

TextFieldBase {
    id: root

    readonly property alias bg: bg
    readonly property alias searchIcon: searchIcon
    readonly property alias clearIcon: clearIcon

    signal searchCleared()
    signal searchSubmitted()
    signal navigationKeyPressed(int key)

    leftPadding: searchIcon.width + searchIcon.anchors.leftMargin + Tokens.spacing.medium
    rightPadding: clearIcon.width + clearIcon.anchors.rightMargin + Tokens.spacing.medium
    topPadding: Tokens.padding.medium
    bottomPadding: Tokens.padding.medium

    onAccepted: searchSubmitted()

    Keys.onPressed: (event) => {
        if (event.key === Qt.Key_Escape) {
            event.accepted = true;
            AppController.hideOverlay();
        } else if (event.key === Qt.Key_Up || event.key === Qt.Key_Down ||
                   event.key === Qt.Key_Left || event.key === Qt.Key_Right) {
            event.accepted = true;
            navigationKeyPressed(event.key);
        } else if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
            event.accepted = true;
            searchSubmitted();
        } else if (event.modifiers & Qt.ControlModifier) {
            if (event.key === Qt.Key_1) { AppController.activeTab = 0; event.accepted = true; }
            else if (event.key === Qt.Key_2) { AppController.activeTab = 1; event.accepted = true; }
            else if (event.key === Qt.Key_3) { AppController.activeTab = 2; event.accepted = true; }
            else if (event.key === Qt.Key_4) { AppController.activeTab = 3; event.accepted = true; }
        }
    }

    onPressed: {
        if (!stateLayer.disabled)
            stateLayer.press(stateLayer.mouseX, stateLayer.mouseY);
    }

    background: StyledRect {
        id: bg

        anchors.fill: parent
        color: root.activeFocus ? Colours.palette.m3surfaceContainerHighest : Colours.palette.m3surfaceContainerHigh
        radius: Tokens.rounding.full

        Behavior on color {
            CAnim {}
        }

        StateLayer {
            id: stateLayer

            cursorShape: Qt.IBeamCursor
            disabled: root.activeFocus
            manualPressOverride: tapHandler.pressed
            onClicked: root.focus = true
        }
    }

    StyledText {
        id: placeholder

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: root.leftPadding
        anchors.rightMargin: root.rightPadding

        text: root.placeholderText
        color: root.placeholderTextColor
        font: root.font
        elide: Text.ElideRight

        opacity: root.text ? 0 : 0.7

        Behavior on opacity {
            Anim {
                type: Anim.DefaultEffects
            }
        }
    }

    MaterialIcon {
        id: searchIcon

        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: Tokens.padding.large

        text: "search"
        color: root.activeFocus ? Colours.palette.m3primary : Colours.palette.m3onSurfaceVariant
        fontStyle: Tokens.font.icon.builders.medium.scale(0.9).build()

        Behavior on color {
            CAnim {}
        }
    }

    IconButton {
        id: clearIcon

        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: Tokens.padding.small

        icon: "clear"
        pointSize: 18
        radius: Tokens.rounding.full
        radiusMorph: false
        enabled: root.text.length > 0
        stateLayer.hoverEnabled: enabled
        onClicked: {
            root.clear();
            root.searchCleared();
            root.forceActiveFocus();
        }

        opacity: root.text ? 1 : 0
        visible: opacity > 0.01

        Behavior on opacity {
            Anim {
                type: Anim.DefaultEffects
            }
        }
    }

    TapHandler {
        id: tapHandler
    }
}
