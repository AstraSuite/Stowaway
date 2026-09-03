import Astra.Stowaway
import QtQuick
import QtQuick.Controls
import "../components"
import "../components/containers"
import "../components/effects"

Item {
    id: root

    signal previewRequested(string imagePath, string textContent, string title)

    property int currentIndex: ClipboardManager.filteredItems.length > 0 ? 0 : -1
    property var currentItem: currentIndex >= 0 && currentIndex < ClipboardManager.filteredItems.length ? ClipboardManager.filteredItems[currentIndex] : null
    property string lastQuery: ""

    function moveSelection(key) {
        if (listView.count === 0) return;
        var idx = currentIndex;
        if (idx < 0) {
            idx = 0;
        } else {
            if (key === Qt.Key_Up) idx -= 1;
            else if (key === Qt.Key_Down) idx += 1;
        }
        if (idx < 0) idx = 0;
        if (idx >= listView.count) idx = listView.count - 1;
        currentIndex = idx;
        listView.currentIndex = idx;
        listView.positionViewAtIndex(idx, ListView.Contain);
    }

    function activateSelection() {
        if (currentItem)
            ClipboardManager.selectItem(currentItem.id, AppController.targetWindowAddress);
    }

    Connections {
        target: ClipboardManager
        function onFilteredItemsChanged() {
            if (ClipboardManager.filteredItems.length === 0) {
                root.currentIndex = -1;
            } else if (ClipboardManager.filterQuery !== root.lastQuery) {
                root.lastQuery = ClipboardManager.filterQuery;
                root.currentIndex = 0;
                listView.positionViewAtIndex(0, ListView.Beginning);
            } else if (root.currentIndex < 0) {
                root.currentIndex = 0;
            } else if (root.currentIndex >= ClipboardManager.filteredItems.length) {
                root.currentIndex = Math.max(0, ClipboardManager.filteredItems.length - 1);
            }
        }
    }

    Connections {
        target: AppController
        function onActiveTabChanged() {
            if (AppController.activeTab === 0 && root.currentIndex < 0 && ClipboardManager.filteredItems.length > 0) {
                root.currentIndex = 0;
            }
        }
    }

    Column {
        anchors.fill: parent
        spacing: 8

        // Section Header: Items Count & Clear All Button
        Item {
            width: parent.width
            height: 22

            StyledText {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                text: {
                    var count = ClipboardManager.filteredItems.length;
                    return count === 1 ? "1 item" : (count + " items");
                }
                font: Tokens.font.label.medium
                color: Colours.palette.m3onSurfaceVariant
            }

            Item {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                width: clearAllRow.implicitWidth + 14
                height: 22
                visible: ClipboardManager.filteredItems.length > 0

                StyledRect {
                    anchors.fill: parent
                    radius: Tokens.rounding.full
                    color: clearMouse.containsMouse ? Colours.palette.m3surfaceContainerHighest : "transparent"

                    Row {
                        id: clearAllRow
                        anchors.centerIn: parent
                        spacing: 4

                        MaterialIcon {
                            text: "delete_sweep"
                            pointSize: 15
                            color: Colours.palette.m3error
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        StyledText {
                            text: "Clear All"
                            font: Tokens.font.label.small
                            color: Colours.palette.m3error
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    MouseArea {
                        id: clearMouse
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: ClipboardManager.clearHistory()
                    }
                }
            }
        }

        // Unified Clipboard Item List View
        VerticalFadeListView {
            id: listView
            width: parent.width
            height: parent.height - 30
            clip: true
            spacing: 6
            boundsBehavior: Flickable.DragAndOvershootBounds
            model: ClipboardManager.filteredItems



            // Empty State
            Item {
                anchors.fill: parent
                visible: listView.count === 0

                Column {
                    anchors.centerIn: parent
                    spacing: 8

                    MaterialIcon {
                        text: "inventory_2"
                        pointSize: 42
                        color: Colours.palette.m3onSurfaceVariant
                        opacity: 0.35
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    StyledText {
                        text: ClipboardManager.filterQuery === "" ? "Clipboard history is empty" : "No matching items found"
                        font: Tokens.font.body.medium
                        color: Colours.palette.m3onSurfaceVariant
                        opacity: 0.7
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }

            delegate: StyledRect {
                id: card
                width: listView.width
                height: modelData.type === 4 ? 76 : 60
                radius: Tokens.rounding.large
                color: index === root.currentIndex ? Colours.palette.m3secondaryContainer : (modelData.pinned ? Colours.palette.m3surfaceContainer : Colours.palette.m3surfaceContainerLow)

                Behavior on color {
                    CAnim {}
                }

                Row {
                    anchors.fill: parent
                    anchors.margins: 8
                    spacing: 10

                    // Left Thumbnail / Icon
                    Item {
                        width: modelData.type === 4 ? 60 : 38
                        height: parent.height
                        anchors.verticalCenter: parent.verticalCenter

                        // Image Thumbnail
                        StyledRect {
                            anchors.fill: parent
                            visible: modelData.type === 4
                            radius: Tokens.rounding.medium
                            clip: true
                            color: Colours.palette.m3surfaceContainerHigh

                            Image {
                                anchors.fill: parent
                                fillMode: Image.PreserveAspectCrop
                                source: modelData.type === 4 && modelData.imagePath !== "" ? ("file://" + modelData.imagePath) : ""
                                sourceSize.width: 120
                                sourceSize.height: 120
                            }
                        }

                        // Color Swatch Box
                        StyledRect {
                            anchors.centerIn: parent
                            width: 34
                            height: 34
                            visible: modelData.type === 3
                            radius: Tokens.rounding.medium
                            color: modelData.type === 3 ? modelData.content : "transparent"
                        }

                        // Type Icon for text / code / URL
                        StyledRect {
                            anchors.centerIn: parent
                            width: 34
                            height: 34
                            visible: modelData.type !== 4 && modelData.type !== 3
                            radius: Tokens.rounding.medium
                            color: modelData.type === 1 ? Colours.palette.m3tertiaryContainer : (modelData.type === 2 ? Colours.palette.m3primaryContainer : Colours.palette.m3surfaceContainerHigh)

                            MaterialIcon {
                                text: modelData.type === 1 ? "code" : (modelData.type === 2 ? "link" : "notes")
                                pointSize: 18
                                color: modelData.type === 1 ? Colours.palette.m3onTertiaryContainer : (modelData.type === 2 ? Colours.palette.m3onPrimaryContainer : Colours.palette.m3onSurfaceVariant)
                                anchors.centerIn: parent
                            }
                        }
                    }

                    // Middle Content Info (takes all remaining width, leaving room for pin + delete)
                    Item {
                        width: parent.width - (modelData.type === 4 ? 70 : 48) - 76
                        height: parent.height

                        Column {
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: 2

                            StyledText {
                                width: parent.width
                                text: modelData.previewLine1
                                font: modelData.type === 1 ? Tokens.font.mono.small : Tokens.font.body.medium
                                color: Colours.palette.m3onSurface
                                elide: Text.ElideRight
                                maximumLineCount: 1
                            }

                            StyledText {
                                width: parent.width
                                text: modelData.previewLine2
                                font: modelData.type === 1 ? Tokens.font.mono.small : Tokens.font.body.medium
                                color: Colours.palette.m3onSurfaceVariant
                                elide: Text.ElideRight
                                maximumLineCount: 1
                                opacity: 0.6
                                visible: text.length > 0
                            }
                        }
                    }
                }

                // Card Click: Select & Paste (below buttons in z-order)
                StateLayer {
                    radius: Tokens.rounding.large
                    color: Colours.palette.m3onSurface
                    onClicked: {
                        if (!deleteMouse.containsMouse && !pinMouse.containsMouse)
                            ClipboardManager.selectItem(modelData.id, AppController.targetWindowAddress);
                    }
                }

                // Pin button
                Item {
                    id: pinArea
                    anchors.right: deleteArea.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 4
                    width: 30
                    height: 30

                    StyledRect {
                        anchors.fill: parent
                        radius: Tokens.rounding.full
                        color: pinMouse.containsMouse ? Colours.palette.m3surfaceContainerHighest : "transparent"

                        Behavior on color { CAnim {} }

                        MaterialIcon {
                            text: modelData.pinned ? "push_pin" : "push_pin"
                            pointSize: 18
                            color: modelData.pinned ? Colours.palette.m3primary : (pinMouse.containsMouse ? Colours.palette.m3onSurface : Colours.palette.m3onSurfaceVariant)
                            anchors.centerIn: parent
                            rotation: modelData.pinned ? 45 : 0

                            Behavior on color { CAnim {} }
                            Behavior on rotation { Anim { type: Anim.DefaultSpatial; duration: 200 } }
                        }
                    }

                    MouseArea {
                        id: pinMouse
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: ClipboardManager.togglePin(modelData.id)
                    }
                }

                // Delete button — placed AFTER StateLayer so it sits above it and receives clicks first
                Item {
                    id: deleteArea
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 8
                    width: 30
                    height: 30

                    StyledRect {
                        anchors.fill: parent
                        radius: Tokens.rounding.full
                        color: deleteMouse.containsMouse ? Colours.palette.m3surfaceContainerHighest : "transparent"

                        Behavior on color { CAnim {} }

                        MaterialIcon {
                            text: "close"
                            pointSize: 18
                            color: deleteMouse.containsMouse ? Colours.palette.m3error : Colours.palette.m3onSurfaceVariant
                            anchors.centerIn: parent

                            Behavior on color { CAnim {} }
                        }
                    }

                    MouseArea {
                        id: deleteMouse
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: ClipboardManager.deleteItem(modelData.id)
                    }
                }
            }
        }
    }
}
