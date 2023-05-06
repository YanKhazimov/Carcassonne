import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    implicitWidth: 500
    implicitHeight: 500
    topPadding: 50

    background: Rectangle {
        color: "lightgrey"

        Text {
            text: "Оставшиеся фишки"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 25
        }

        TileViewSwitch {
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20
        }
    }

    contentItem: ScrollView {
        contentWidth: availableWidth
        clip: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        Flow {
            width: parent.width
            spacing: 25
            Repeater {
                id: remainingTilesRepeater
                model: engine.remainingTilesModel

                delegate: Tile {
                    required property int index // https://bugreports.qt.io/browse/QTBUG-86009
                    board: null
                    width: Constants.tilePreviewSize
                    height: Constants.tilePreviewSize

                    // dimmer
                    Rectangle {
                        anchors.fill: parent
                        color: Qt.rgba(0.5, 0.5, 0.5, 0.6)
                        visible: tileData.IsFixed
                    }

                    Component.onCompleted: {
                        tileData = engine.getRemainingTile(index)
                    }

                    Text {
                        text: tileData.Picture.toString().slice(tileData.Picture.toString().lastIndexOf("/")+1)
                        font.bold: true
                        visible: Preferences.schematicView
                    }

                    Rectangle {
                        readonly property int copies: remainingTilesRepeater.model.getTileCopies(index)

                        color: "white"
                        width: Constants.tilePreviewSize/4
                        height: Constants.tilePreviewSize/4
                        radius: width/4
                        border.width: 2
                        border.color: "red"
                        anchors.horizontalCenter: parent.right
                        anchors.horizontalCenterOffset: -width/4
                        anchors.verticalCenter: parent.bottom
                        anchors.verticalCenterOffset: -height/4
                        visible: copies > 1

                        Text {
                            anchors.centerIn: parent
                            text: "x" + parent.copies
                        }
                    }
                }
            }
        }
    }
}