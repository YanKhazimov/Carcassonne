import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    implicitWidth: 500
    implicitHeight: 500

    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        spacing: 20

        Row {
            id: resourcesRow

            spacing: 15
            Layout.alignment: Qt.AlignHCenter

            Row {
                spacing: 5
                TileBonusIndicator {
                    source: "qrc:/img/barrel.png"
                    width: 32
                    height: 32
                    anchors.verticalCenter: parent.verticalCenter
                }
                MyText {
                    text: engine ? ("x" + engine.UnassignedBarrels) : ""
                    font.pixelSize: 20
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: Fonts.bonuses
                    color: "white"
                }
            }

            Row {
                spacing: 5
                TileBonusIndicator {
                    source: "qrc:/img/wheat.png"
                    width: 32
                    height: 32
                    anchors.verticalCenter: parent.verticalCenter
                }
                MyText {
                    text: engine ? ("x" + engine.UnassignedWheat) : ""
                    font.pixelSize: 20
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: Fonts.bonuses
                    color: "white"
                }
            }

            Row {
                spacing: 5
                TileBonusIndicator {
                    source: "qrc:/img/cloth.png"
                    width: 32
                    height: 32
                    anchors.verticalCenter: parent.verticalCenter
                }
                MyText {
                    text: engine ? ("x" + engine.UnassignedCloth) : ""
                    font.pixelSize: 20
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: Fonts.bonuses
                    color: "white"
                }
            }
        }

        ScrollView {
            contentWidth: parent.width
            Layout.fillHeight: true
            clip: true
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn

            Flow {
                id: tileFlow

                readonly property int tileSize: Constants.tilePreviewSize

                width: parent.width / (tileSize + spacing) * (tileSize + spacing) // integer number of (tile + space)
                anchors.horizontalCenter: parent.horizontalCenter
                bottomPadding: tileSize/4/2 // making copies not clip
                spacing: 15

                Repeater {
                    id: remainingTilesRepeater
                    model: engine ? engine.remainingTilesModel : []

                    delegate: Image {
                        required property int index // https://bugreports.qt.io/browse/QTBUG-86009
                        width: tileFlow.tileSize
                        height: tileFlow.tileSize

                        // dimmer
                        Rectangle {
                            id: dimmer
                            anchors.fill: parent
                            color: Qt.rgba(0.5, 0.5, 0.5, 0.6)
                            visible: index > 0 && engine && engine.getRemainingTile(index).IsFixed // index > 0 seems to initialize engine.getRemainingTile(index) to not be null
                        }

                        Rectangle {
                            id: border

                            anchors.fill: parent
                            color: "transparent"
                            border.width: 2
                            border.color: "black"
                            visible: !dimmer.visible
                        }

                        Component.onCompleted: {
                            source = engine.getRemainingTile(index).Picture
                        }

                        Rectangle {
                            readonly property int copies: remainingTilesRepeater.model.getTileCopies(index)

                            color: "white"
                            width: tileFlow.tileSize/4
                            height: tileFlow.tileSize/4
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
}
