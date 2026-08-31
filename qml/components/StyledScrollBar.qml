import Astra.Stowaway
import QtQuick
import QtQuick.Controls

ScrollBar {
    id: control

    implicitWidth: 6
    implicitHeight: 6
    padding: 2

    contentItem: Rectangle {
        implicitWidth: 4
        implicitHeight: 4
        radius: width / 2
        color: Colours.palette.m3onSurfaceVariant
        opacity: control.active ? (control.pressed ? 0.8 : 0.5) : (control.hovered ? 0.35 : 0.15)

        Behavior on opacity {
            NumberAnimation { duration: 150 }
        }
    }

    background: Rectangle {
        color: "transparent"
    }
}
