import Astra.Stowaway
import QtQuick
import QtQuick.Controls
import "../components"
import "../components/effects"

Item {
    id: root

    property bool active: false
    property string imagePath: ""
    property string textContent: ""
    property string title: ""

    anchors.fill: parent
    visible: opacity > 0.01
    opacity: active ? 1 : 0
    z: 2000

    Behavior on opacity {
        Anim { type: Anim.FastEffects }
    }

    // Scrim overlay
    Rectangle {
        anchors.fill: parent
        color: Qt.alpha(Colours.palette.m3scrim, 0.6)

        MouseArea {
            anchors.fill: parent
            onClicked: root.active = false
        }
    }

    // Modal Box
    StyledRect {
        id: modalBox
        anchors.centerIn: parent
        width: Math.min(parent.width - 32, 360)
        height: Math.min(parent.height - 48, 420)
        radius: Tokens.rounding.large
        color: Colours.palette.m3surfaceContainerHigh
        scale: root.active ? 1.0 : 0.9

        Behavior on scale {
            Anim { type: Anim.DefaultSpatial }
        }

        Elevation {
            level: 4
            anchors.fill: parent
        }

        Column {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 12

            // Header
            Row {
                width: parent.width
                height: 28

                StyledText {
                    text: root.title
                    font: Tokens.font.title.medium
                    color: Colours.palette.m3onSurface
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - 36
                    elide: Text.ElideRight
                }

                Item {
                    width: 28
                    height: 28
                    anchors.verticalCenter: parent.verticalCenter

                    StyledRect {
                        anchors.fill: parent
                        radius: Tokens.rounding.full
                        color: closeMouse.containsMouse ? Colours.palette.m3surfaceContainerHighest : "transparent"

                        MaterialIcon {
                            text: "close"
                            pointSize: 18
                            color: Colours.palette.m3onSurfaceVariant
                            anchors.centerIn: parent
                        }

                        MouseArea {
                            id: closeMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: root.active = false
                        }
                    }
                }
            }

            // Image Preview Content
            Item {
                width: parent.width
                height: parent.height - 40
                visible: root.imagePath !== ""

                Image {
                    anchors.fill: parent
                    source: root.imagePath !== "" ? "file://" + root.imagePath : ""
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    mipmap: true
                }
            }

            // Text / Code Preview Content
            Flickable {
                width: parent.width
                height: parent.height - 40
                contentWidth: width
                contentHeight: longText.implicitHeight
                clip: true
                visible: root.imagePath === ""

                StyledText {
                    id: longText
                    width: parent.width
                    text: root.textContent
                    font: Tokens.font.mono.small
                    color: Colours.palette.m3onSurface
                    wrapMode: Text.WrapAnywhere
                }

                StyledScrollBar {
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }
            }
        }
    }
}
