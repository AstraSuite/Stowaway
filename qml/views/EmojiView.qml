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

    function columnCount() {
        return Math.max(1, Math.floor(grid.width / grid.cellWidth));
    }

    function moveSelection(key) {
        if (grid.count === 0) return;
        var cols = columnCount();
        var idx = currentIndex < 0 ? 0 : currentIndex;
        if (key === Qt.Key_Up) idx -= cols;
        else if (key === Qt.Key_Down) idx += cols;
        else if (key === Qt.Key_Left) idx -= 1;
        else if (key === Qt.Key_Right) idx += 1;
        if (idx < 0) idx = 0;
        if (idx >= grid.count) idx = grid.count - 1;
        currentIndex = idx;
        grid.currentIndex = idx;
        grid.positionViewAtIndex(idx, GridView.Contain);
    }

    function activateItem(character, name) {
        EmojiService.recordUsage(character, name, "emoji");
        AppController.dismissAndPasteText(character, AppController.targetWindowAddress);
    }

    function activateSelection() {
        if (currentIndex < 0 || currentIndex >= grid.model.length) return;
        var data = grid.model[currentIndex];
        activateItem(data.character, data.name);
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
                    model: EmojiService.emojiCategories

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

        // Emoji Grid
        VerticalFadeGridView {
            id: grid
            width: parent.width
            height: parent.height - 40
            cellWidth: width / 8
            cellHeight: 44
            clip: true
            boundsBehavior: Flickable.DragAndOvershootBounds

            model: {
                var dummy = root.favVersion;
                return EmojiService.searchEmojis(root.searchQuery, root.selectedCategory);
            }



            // Empty State
            Item {
                anchors.fill: parent
                visible: grid.count === 0

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
                        text: "No emojis found"
                        horizontalAlignment: Text.AlignHCenter
                        font: Tokens.font.body.medium
                        color: Colours.palette.m3onSurfaceVariant
                        opacity: 0.7
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }

            delegate: Item {
                id: cellItem
                width: grid.cellWidth
                height: grid.cellHeight

                readonly property bool isHovered: cellMouse.containsMouse || starMouse.containsMouse
                readonly property bool isCurrent: index === root.currentIndex

                StyledRect {
                    id: emojiBox
                    anchors.centerIn: parent
                    width: 38
                    height: 38
                    radius: Tokens.rounding.medium
                    color: cellItem.isCurrent ? Colours.palette.m3secondaryContainer : (cellItem.isHovered ? Colours.palette.m3surfaceContainerHighest : "transparent")

                    Behavior on color {
                        CAnim {}
                    }

                    Text {
                        anchors.centerIn: parent
                        text: modelData.character
                        font.pixelSize: 22
                        renderType: Text.NativeRendering
                    }

                    // Click area to select & paste
                    MouseArea {
                        id: cellMouse
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor

                        onClicked: {
                            root.activateItem(modelData.character, modelData.name);
                        }
                    }

                    // Material variable font star with animated fill
                    Item {
                        id: starBtn
                        anchors.top: parent.top
                        anchors.right: parent.right
                        anchors.topMargin: -2
                        anchors.rightMargin: -2
                        width: 18
                        height: 18
                        z: 10

                        visible: modelData.isFavorite || cellItem.isHovered
                        opacity: modelData.isFavorite ? 1.0 : (cellItem.isHovered ? 0.7 : 0.0)

                        Behavior on opacity {
                            Anim { type: Anim.FastEffects; duration: 150 }
                        }

                        MaterialIcon {
                            anchors.centerIn: parent
                            text: "star"
                            pointSize: 14
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
                                EmojiService.toggleFavorite(modelData.character, modelData.name, "emoji");
                            }
                        }
                    }
                }
            }
        }
    }
}
