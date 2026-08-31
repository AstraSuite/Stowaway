import Astra.Stowaway
import QtQuick
import "."

StyledRect {
    id: root

    property string text: ""
    property string icon: ""
    property color badgeColor: Colours.palette.m3secondaryContainer
    property color textColor: Colours.palette.m3onSecondaryContainer

    implicitWidth: row.implicitWidth + 14
    implicitHeight: 22
    radius: Tokens.rounding.full
    color: badgeColor

    Row {
        id: row
        anchors.centerIn: parent
        spacing: 4

        MaterialIcon {
            text: root.icon
            visible: root.icon !== ""
            pointSize: 13
            color: root.textColor
            anchors.verticalCenter: parent.verticalCenter
        }

        StyledText {
            text: root.text
            font: Tokens.font.label.small
            color: root.textColor
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
