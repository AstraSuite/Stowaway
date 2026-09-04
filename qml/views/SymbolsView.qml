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

    property int currentIndex: (grid.model && grid.model.length > 0) ? 0 : -1

    function columnCount() {
        return Math.max(1, Math.floor(grid.width / grid.cellWidth));
    }

    function resetSelection() {
        var count = (grid.model && grid.model.length) ? grid.model.length : 0;
        currentIndex = count > 0 ? 0 : -1;
        grid.currentIndex = currentIndex;
        if (currentIndex === 0) {
            grid.positionViewAtIndex(0, GridView.Beginning);
        }
    }

    onSearchQueryChanged: resetSelection()
    onSelectedCategoryChanged: resetSelection()

    Component.onCompleted: resetSelection()

    function moveSelection(key) {
        if (grid.count === 0) return;
        var cols = columnCount();
        var idx = currentIndex;
        if (idx < 0) {
            idx = 0;
        } else {
            if (key === Qt.Key_Up) idx -= cols;
            else if (key === Qt.Key_Down) idx += cols;
            else if (key === Qt.Key_Left) idx -= 1;
            else if (key === Qt.Key_Right) idx += 1;
        }
        if (idx < 0) idx = 0;
        if (idx >= grid.count) idx = grid.count - 1;
        currentIndex = idx;
        grid.currentIndex = idx;
        grid.positionViewAtIndex(idx, GridView.Contain);
    }

    function activateItem(character, name) {
        EmojiService.recordUsage(character, name, "symbol");
        AppController.dismissAndPasteText(character, AppController.targetWindowAddress);
    }

    function activateSelection() {
        if (currentIndex < 0 || !grid.model || currentIndex >= grid.model.length) return;
        var data = grid.model[currentIndex];
        activateItem(data.character, data.name);
    }

    Connections {
        target: EmojiService
        function onFavoritesChanged() {
            root.favVersion++;
            var count = (grid.model && grid.model.length) ? grid.model.length : 0;
            if (root.currentIndex >= count) {
                root.currentIndex = Math.max(0, count - 1);
            }
        }
    }

    Connections {
        target: AppController
        function onActiveTabChanged() {
            if (AppController.activeTab === 3 && root.currentIndex < 0 && grid.model && grid.model.length > 0) {
                root.currentIndex = 0;
            }
        }
    }

    Column {
        anchors.fill: parent
        spacing: 8

        // Category pills
        Flickable {
            width: parent.width
            height: Math.round(32 * AppController.uiScale)
            contentWidth: catRow.implicitWidth
            contentHeight: Math.round(32 * AppController.uiScale)
            boundsBehavior: Flickable.DragAndOvershootBounds
            clip: true

            Row {
                id: catRow
                spacing: Math.round(6 * AppController.uiScale)

                Repeater {
                    model: EmojiService.symbolCategories

                    Item {
                        id: catChip
                        width: catText.implicitWidth + Math.round(16 * AppController.uiScale)
                        height: Math.round(28 * AppController.uiScale)

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

        // Symbols Grid
        VerticalFadeGridView {
            id: grid
            width: parent.width
            height: parent.height - Math.round(40 * AppController.uiScale)
            readonly property int columns: Math.max(4, Math.floor(width / Math.max(1, (48 * AppController.uiScale))))
            cellWidth: Math.floor(width / columns)
            cellHeight: Math.round(46 * AppController.uiScale)
            clip: true
            boundsBehavior: Flickable.DragAndOvershootBounds

            model: {
                var dummy = root.favVersion;
                return EmojiService.searchSymbols(root.searchQuery, root.selectedCategory);
            }
            onModelChanged: root.resetSelection()



            // Empty State
            Item {
                anchors.fill: parent
                visible: grid.count === 0

                Column {
                    anchors.centerIn: parent
                    spacing: Math.round(6 * AppController.uiScale)

                    MaterialIcon {
                        text: "search_off"
                        pointSize: Math.round(36 * AppController.uiScale)
                        color: Colours.palette.m3onSurfaceVariant
                        opacity: 0.4
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    StyledText {
                        text: "No symbols found"
                        horizontalAlignment: Text.AlignHCenter
                        font: Tokens.font.body.medium
                        color: Colours.palette.m3onSurfaceVariant
                        opacity: 0.7
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }

            delegate: Item {
                id: symItem
                width: grid.cellWidth
                height: grid.cellHeight

                readonly property bool isHovered: symMouse.containsMouse || starMouse.containsMouse
                readonly property bool isCurrent: index === root.currentIndex

                StyledRect {
                    id: symbolBox
                    anchors.centerIn: parent
                    width: Math.round(40 * AppController.uiScale)
                    height: Math.round(40 * AppController.uiScale)
                    radius: Tokens.rounding.medium
                    color: symItem.isCurrent ? Colours.palette.m3secondaryContainer : (symItem.isHovered ? Colours.palette.m3surfaceContainerHighest : "transparent")

                    Behavior on color {
                        CAnim {}
                    }

                    Text {
                        anchors.centerIn: parent
                        text: modelData.character
                        font.pixelSize: Math.round(20 * AppController.uiScale)
                        color: Colours.palette.m3onSurface
                        renderType: Text.NativeRendering
                    }

                    // Click area to select & paste
                    MouseArea {
                        id: symMouse
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor

                        onClicked: {
                            root.activateItem(modelData.character, modelData.name);
                        }
                    }

                    // Material variable font star with animated fill (white, no grow)
                    Item {
                        id: starBtn
                        anchors.top: parent.top
                        anchors.right: parent.right
                        anchors.topMargin: -2
                        anchors.rightMargin: -2
                        width: Math.round(18 * AppController.uiScale)
                        height: Math.round(18 * AppController.uiScale)
                        z: 10

                        visible: modelData.isFavorite || symItem.isHovered
                        opacity: modelData.isFavorite ? 1.0 : (symItem.isHovered ? 0.7 : 0.0)

                        Behavior on opacity {
                            Anim { type: Anim.FastEffects; duration: 150 }
                        }

                        MaterialIcon {
                            anchors.centerIn: parent
                            text: "star"
                            pointSize: Math.round(14 * AppController.uiScale)
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
                                EmojiService.toggleFavorite(modelData.character, modelData.name, "symbol");
                            }
                        }
                    }
                }
            }
        }
    }
}
