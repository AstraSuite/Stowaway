import Astra.Stowaway
import QtQuick
import "../components"
import "../components/effects"

Item {
    id: root

    property string message: ""
    property bool show: false

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.bottomMargin: show ? Math.round(24 * AppController.uiScale) : -Math.round(60 * AppController.uiScale)
    opacity: show ? 1 : 0
    scale: show ? 1.0 : 0.85

    implicitWidth: toastContent.implicitWidth + Math.round(28 * AppController.uiScale)
    implicitHeight: Math.round(38 * AppController.uiScale)
    z: 1000

    Behavior on anchors.bottomMargin {
        Anim { type: Anim.FastSpatial }
    }
    Behavior on opacity {
        Anim { type: Anim.FastEffects }
    }
    Behavior on scale {
        Anim { type: Anim.FastSpatial }
    }

    Elevation {
        level: 3
        anchors.fill: toastRect
    }

    StyledRect {
        id: toastRect
        anchors.fill: parent
        radius: Tokens.rounding.full
        color: Colours.palette.m3inverseSurface

        Row {
            id: toastContent
            anchors.centerIn: parent
            spacing: Math.round(8 * AppController.uiScale)

            MaterialIcon {
                text: "check_circle"
                pointSize: Math.round(18 * AppController.uiScale)
                color: Colours.palette.m3inverseOnSurface
                anchors.verticalCenter: parent.verticalCenter
            }

            StyledText {
                text: root.message
                font: Tokens.font.body.medium
                color: Colours.palette.m3inverseOnSurface
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
