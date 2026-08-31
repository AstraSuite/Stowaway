import QtQuick
import Astra.Stowaway
import "."

Item {
    id: root

    property string icon: ""
    property font fontStyle: Tokens.font.icon.small
    property int pointSize: 18
    property int radius: Tokens.rounding.full
    property bool radiusMorph: false
    property alias stateLayer: stateLayer
    property int type: 0

    signal clicked()

    implicitWidth: 32
    implicitHeight: 32

    StyledRect {
        id: bgRect
        anchors.fill: parent
        radius: root.radius
        color: stateLayer.containsMouse ? Colours.palette.m3surfaceContainerHighest : "transparent"

        Behavior on color {
            CAnim {}
        }

        MaterialIcon {
            id: iconLabel
            anchors.centerIn: parent
            text: root.icon
            fontStyle: root.fontStyle
            pointSize: root.pointSize
            color: stateLayer.containsMouse ? Colours.palette.m3onSurface : Colours.palette.m3onSurfaceVariant

            Behavior on color {
                CAnim {}
            }
        }

        StateLayer {
            id: stateLayer
            radius: root.radius
            cursorShape: Qt.PointingHandCursor
            onClicked: root.clicked()
        }
    }
}
