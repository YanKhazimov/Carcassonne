import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Popup {
    id: root

    implicitWidth: 500
    implicitHeight: 500
    topPadding: 10

    background: Rectangle {
        id: background

        color: "white"

        Image {
            opacity: 0.3
            source: "qrc:/img/background.png"
            sourceSize.width: 144
            sourceSize.height: 144
            anchors.fill: parent
            fillMode: Image.Tile
        }
    }

    contentItem: Item {
        width: availableWidth
        height: availableHeight

        ColumnLayout {
            anchors.fill: parent
            spacing: 10

            MyText {
                text: "Оставшиеся ресурсы"
                Layout.alignment: Qt.AlignHCenter
                font.pixelSize: 25
                font.family: Fonts.bonuses
            }

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
                    }
                }
            }

            MyText {
                text: "Оставшиеся фишки"
                Layout.topMargin: 20
                Layout.alignment: Qt.AlignHCenter
                font.pixelSize: 25
                font.family: Fonts.bonuses
            }

            ScrollView {
                contentWidth: parent.width
                Layout.fillHeight: true
                clip: true
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn

                Flow {
                    width: parent.width
                    bottomPadding: Constants.tilePreviewSize/4/2 // making copies not clip
                    spacing: 25

                    Repeater {
                        id: remainingTilesRepeater
                        model: engine ? engine.remainingTilesModel : []

                        delegate: Image {
                            required property int index // https://bugreports.qt.io/browse/QTBUG-86009
                            width: Constants.tilePreviewSize
                            height: Constants.tilePreviewSize

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
    }
}
