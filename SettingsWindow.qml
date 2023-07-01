import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Item {
    id: root

    signal urlRequested(var urlAddress)

    function colorIndex(index) {
        while (index < 0)
        {
            index += engine.PossibleColors.length
        }
        return index % engine.PossibleColors.length
    }

    width: 1280
    height: 980

    Column {
        anchors.centerIn: parent
        spacing: 5

        Item {
            id: headerClipper

            clip: true
            width: 300
            height: 30
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                id: playersCountRect
                anchors.horizontalCenter: parent.horizontalCenter
                Behavior on anchors.horizontalCenterOffset { NumberAnimation { duration: 200 } }

                property int playerCount: 3

                width: 500
                height: 30
                color: "transparent"

                LinearGradient {
                    anchors.fill: parent
                    start: Qt.point(0, 0)
                    end: Qt.point(parent.width, 0)
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "transparent" }
                        GradientStop { position: 0.2; color: "silver" }
                        GradientStop { position: 0.8; color: "silver" }
                        GradientStop { position: 1.0; color: "transparent" }
                    }
                }

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    Item {
                        width: 100
                        height: 30

                        Text {
                            anchors.centerIn: parent
                            text: "2 игрока"
                            font.pixelSize: playersCountRect.playerCount === 2 ? 20 : 15
                        }
                    }
                    Rectangle {
                        width: 1
                        height: 20
                        color: "black"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Item {
                        width: 100
                        height: 30

                        Text {
                            anchors.centerIn: parent
                            text: "3 игрока"
                            font.pixelSize: playersCountRect.playerCount === 3 ? 20 : 15
                        }
                    }
                    Rectangle {
                        width: 1
                        height: 20
                        color: "black"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Item {
                        width: 100
                        height: 30

                        Text {
                            anchors.centerIn: parent
                            text: "4 игрока"
                            font.pixelSize: playersCountRect.playerCount === 4 ? 20 : 15
                        }
                    }
                }
            }

            MouseArea {
                anchors.left: parent.left
                width: 100
                height: 30
                cursorShape: Qt.PointingHandCursor
                visible: playersCountRect.playerCount > 2
                onClicked: {
                    playersCountRect.playerCount--
                    playersCountRect.anchors.horizontalCenterOffset += 101
                }
            }

            MouseArea {
                anchors.right: parent.right
                width: 100
                height: 30
                cursorShape: Qt.PointingHandCursor
                visible: playersCountRect.playerCount < 4
                onClicked: {
                    playersCountRect.playerCount++
                    playersCountRect.anchors.horizontalCenterOffset -= 101
                }
            }
        }

        Item {
            height: 10
            width: 10
        }

        Repeater {
            id: playerRepeater

            model: 4
            delegate: Item {
                property alias text: textEdit.text
                function getColor() {
                    return colorRepeater.itemAt(playerRow.colorOffset).color
                }

                anchors.horizontalCenter: parent.horizontalCenter
                width: 300
                height: 30

                Item {
                    id: clipper

                    clip: true
                    anchors.fill: parent

                    Row {
                        id: playerRow

                        property int colorOffset: index
                        anchors.left: parent.left
                        anchors.leftMargin: (-colorRepeater.model/2 - index) * 300
                        Behavior on anchors.leftMargin {
                            NumberAnimation {
                                id: colorAnimation
                                duration: 200
                            }
                        }

                        Repeater {
                            id: colorRepeater
                            model: engine ? 10 * engine.PossibleColors.length : 0
                            delegate: Rectangle {
                                id: playerColorBar

                                width: 300
                                height: 30
                                color: engine ? engine.PossibleColors[root.colorIndex(index)]
                                              : "transparent"
                            }
                        }
                    }

                    TextEdit {
                        id: textEdit
                        anchors.centerIn: parent
                        font.pixelSize: 20
                        selectByMouse: true
                        color: "white"

                        Component.onCompleted: text = "Игрок %1".arg(index + 1)
                    }

                    MouseArea {
                        id: blocker
                        x: index >= playersCountRect.playerCount ? 0 : parent.width
                        width: parent.width
                        height: parent.height
                        Behavior on x { NumberAnimation { duration: 200 } }

                        Rectangle {
                            anchors.fill: parent
                            color: "silver"

                            Text {
                                anchors.centerIn: parent
                                text: "Пусто"
                                font.pixelSize: 20
                            }
                        }
                    }
                }

                MouseArea {
                    anchors.right: parent.left
                    width: 30
                    height: 30
                    cursorShape: Qt.PointingHandCursor
                    visible: index < playersCountRect.playerCount && !colorAnimation.running
                    onClicked: {
                        playerRow.colorOffset = root.colorIndex(playerRow.colorOffset - 1)
                        playerRow.anchors.leftMargin += 300
                    }

                    Rectangle {
                        anchors.fill: parent
                        color: engine ? engine.PossibleColors[root.colorIndex(playerRow.colorOffset - 1)]
                                      : "transparent"
                        opacity: 0.4
                    }

                    Text {
                        anchors.centerIn: parent
                        text: "<"
                        color: "black"
                        font.pixelSize: 20
                    }
                }

                MouseArea {
                    anchors.left: parent.right
                    width: 30
                    height: 30
                    cursorShape: Qt.PointingHandCursor
                    visible: index < playersCountRect.playerCount && !colorAnimation.running
                    onClicked: {
                        playerRow.colorOffset = root.colorIndex(playerRow.colorOffset + 1)
                        playerRow.anchors.leftMargin -= 300
                    }

                    Rectangle {
                        anchors.fill: parent
                        color: engine ? engine.PossibleColors[root.colorIndex(playerRow.colorOffset + 1)]
                                      : "transparent"
                        opacity: 0.4
                    }


                    Text {
                        anchors.centerIn: parent
                        text: ">"
                        color: "black"
                        font.pixelSize: 20
                    }
                }
            }
        }

        Item {
            height: 10
            width: 10
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "15x15"
            font.pixelSize: 30
        }

        Item {
            height: 10
            width: 10
        }

        MenuButton {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Начать игру"
            onClicked: {
                var colors = []
                var names = []
                for (var i = 0; i < playersCountRect.playerCount; ++i) {
                    colors.push(playerRepeater.itemAt(i).getColor())
                    names.push(playerRepeater.itemAt(i).text)
                }
                engine.populatePlayers(colors, names)
                engine.mapModel.setSize(15)
                root.urlRequested("qrc:/GameWindow.qml")
            }
        }
    }
}
