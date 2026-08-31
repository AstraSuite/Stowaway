import Astra.Stowaway
import QtQuick
import "."

StyledRect {
    id: root

    property int currentIndex: 0
    property var tabs: [
        { title: "Clips", icon: "content_paste" },
        { title: "Emoji", icon: "sentiment_satisfied" },
        { title: "Kaomoji", icon: "face" },
        { title: "Symbols", icon: "auto_awesome" }
    ]

    signal tabSelected(int index)

    implicitWidth: 360
    implicitHeight: 38
    radius: Tokens.rounding.full
    color: Colours.palette.m3surfaceContainerLow

    Item {
        anchors.fill: parent
        anchors.margins: 3

        // Sliding Active Indicator Pill
        StyledRect {
            id: indicator
            width: parent.width / root.tabs.length
            height: parent.height
            x: root.currentIndex * width
            radius: Tokens.rounding.full
            color: Colours.palette.m3secondaryContainer

            Behavior on x {
                Anim { type: Anim.DefaultSpatial; duration: 200 }
            }
        }

        Row {
            anchors.fill: parent

            Repeater {
                model: root.tabs

                Item {
                    id: tabItem
                    width: parent.width / root.tabs.length
                    height: parent.height

                    readonly property bool selected: index === root.currentIndex

                    Row {
                        anchors.centerIn: parent
                        spacing: 5

                        MaterialIcon {
                            text: modelData.icon
                            pointSize: 16
                            color: tabItem.selected ? Colours.palette.m3onSecondaryContainer : Colours.palette.m3onSurfaceVariant
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        StyledText {
                            text: modelData.title
                            font: Tokens.font.label.medium
                            color: tabItem.selected ? Colours.palette.m3onSecondaryContainer : Colours.palette.m3onSurfaceVariant
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    StateLayer {
                        color: tabItem.selected ? Colours.palette.m3onSecondaryContainer : Colours.palette.m3onSurface
                        radius: Tokens.rounding.full
                        onClicked: {
                            root.currentIndex = index;
                            root.tabSelected(index);
                        }
                    }
                }
            }
        }
    }
}
