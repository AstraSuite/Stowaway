import Astra.Stowaway
import QtQuick
import QtQuick.Controls
import "../components"
import "../components/containers"
import "../components/effects"

Item {
    id: root

    property string searchQuery: ""
    property string selectedCategory: "All"

    property int favVersion: 0

    property int currentIndex: -1
    readonly property var currentData: currentIndex >= 0 && currentIndex < kaomojiRepeater.model.length ? kaomojiRepeater.model[currentIndex] : null

    function moveSelection(key) {
        if (kaomojiRepeater.count === 0) return;
        var idx = currentIndex < 0 ? 0 : currentIndex;
        if (key === Qt.Key_Up) idx -= 1;
        else if (key === Qt.Key_Down) idx += 1;
        else if (key === Qt.Key_Left) idx -= 1;
        else if (key === Qt.Key_Right) idx += 1;
        if (idx < 0) idx = 0;
        if (idx >= kaomojiRepeater.count) idx = kaomojiRepeater.count - 1;
        currentIndex = idx;
        var item = kaomojiRepeater.itemAt(idx);
        if (item)
            flickable.positionViewAtRect(item);
    }

    function activateItem(character, name) {
        EmojiService.recordUsage(character, name, "kaomoji");
        AppController.dismissAndPasteText(character, AppController.targetWindowAddress);
    }

    function activateSelection() {
        if (currentData)
            activateItem(currentData.character, currentData.name);
    }

    Connections {
        target: EmojiService
        function onFavoritesChanged() {
            root.favVersion++;
        }
    }

    Column {
        anchors.fill: parent
        spacing: 8

        // Category pills
        Flickable {
            width: parent.width
            height: 32
            contentWidth: catRow.implicitWidth
            contentHeight: 32
            boundsBehavior: Flickable.DragAndOvershootBounds
            clip: true

            Row {
                id: catRow
                spacing: 6

                Repeater {
                    model: EmojiService.kaomojiCategories

                    Item {
                        id: catChip
                        width: catText.implicitWidth + 16
                        height: 28

                        readonly property bool isSelected: root.selectedCategory === modelData

                        StyledRect {
                            anchors.fill: parent
                            radius: Tokens.rounding.full
                            color: catChip.isSelected ? Colours.palette.m3secondaryContainer : Colours.palette.m3surfaceContainerHigh

                            Behavior on color {
                                CAnim {}
                            }

                            StyledText {
                                id: catText
                                anchors.centerIn: parent
                                text: modelData
                                font: Tokens.font.label.medium
                                color: catChip.isSelected ? Colours.palette.m3onSecondaryContainer : Colours.palette.m3onSurfaceVariant
                            }

                            StateLayer {
                                radius: Tokens.rounding.full
                                color: catChip.isSelected ? Colours.palette.m3onSecondaryContainer : Colours.palette.m3onSurface
                                onClicked: root.selectedCategory = modelData
                            }
                        }
                    }
                }
            }
        }

        // Kaomoji Flow View
        VerticalFadeFlickable {
            id: flickable
            width: parent.width
            height: parent.height - 40
            contentWidth: width
            contentHeight: flow.implicitHeight + 20
            clip: true
            boundsBehavior: Flickable.DragAndOvershootBounds



            // Empty State
            Item {
                anchors.fill: parent
                visible: kaomojiRepeater.count === 0

                Column {
                    anchors.centerIn: parent
                    spacing: 6

                    MaterialIcon {
                        text: "search_off"
                        pointSize: 36
                        color: Colours.palette.m3onSurfaceVariant
                        opacity: 0.4
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    StyledText {
                        text: "No kaomoji found"
                        horizontalAlignment: Text.AlignHCenter
                        font: Tokens.font.body.medium
                        color: Colours.palette.m3onSurfaceVariant
                        opacity: 0.7
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }

            Flow {
                id: flow
                width: parent.width
                spacing: 8

                Repeater {
                    id: kaomojiRepeater
                    model: {
                        var dummy = root.favVersion;
                        return EmojiService.searchKaomoji(root.searchQuery, root.selectedCategory);
                    }

                    StyledRect {
                        id: kaoCard
                        width: kaoRow.implicitWidth + (starBtn.visible ? 34 : 20)
                        height: 38
                        radius: Tokens.rounding.medium
                        color: index === root.currentIndex ? Colours.palette.m3secondaryContainer : (kaoMouse.containsMouse || starMouse.containsMouse ? Colours.palette.m3surfaceContainerHighest : Colours.palette.m3surfaceContainerLow)

                        Behavior on color {
                            CAnim {}
                        }

                        Row {
                            id: kaoRow
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: 6

                            Text {
                                text: modelData.character
                                font.pixelSize: 14
                                color: Colours.palette.m3onSurface
                                renderType: Text.NativeRendering
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }

                        // Main click area
                        MouseArea {
                            id: kaoMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor

                            onClicked: {
                                root.activateItem(modelData.character, modelData.name);
                            }
                        }

                        // Star Button with Atlas-style variable font fill animation (solid white, no size growth)
                        Item {
                            id: starBtn
                            anchors.right: parent.right
                            anchors.rightMargin: 8
                            anchors.verticalCenter: parent.verticalCenter
                            width: 20
                            height: 20
                            z: 10

                            visible: modelData.isFavorite || kaoMouse.containsMouse || starMouse.containsMouse
                            opacity: modelData.isFavorite ? 1.0 : ((kaoMouse.containsMouse || starMouse.containsMouse) ? 0.7 : 0.0)

                            Behavior on opacity {
                                Anim { type: Anim.FastEffects; duration: 150 }
                            }

                            MaterialIcon {
                                anchors.centerIn: parent
                                text: "star"
                                pointSize: 15
                                color: Colours.palette.m3onSurface
                                fill: modelData.isFavorite ? 1.0 : 0.0

                                Behavior on fill {
                                    Anim { type: Anim.DefaultEffects }
                                }
                            }

                            MouseArea {
                                id: starMouse
                                anchors.fill: parent
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor
                                onClicked: (mouse) => {
                                    mouse.accepted = true;
                                    EmojiService.toggleFavorite(modelData.character, modelData.name, "kaomoji");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
