import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import QtQuick.Window 2.15

Item {
    id: root

    signal urlRequested(var urlAddress)
    signal exitRequested()

    property var currentColorOffsets: [ 0, 1, 2, 3 ]

    function colorIndex(index) {
        while (index < 0)
        {
            index += engine.PossibleColors.length
        }
        return index % engine.PossibleColors.length
    }

    width: Screen.width
    height: Screen.height

    ScreenAdapter {
        id: screenAdapter

        width: 1920
        height: 1080
        anchors.centerIn: parent

        Image {
            source: "qrc:/img/title.png"
            anchors.right: parent.right
            anchors.left: backgroundStripe.right
            anchors.margins: 200
            anchors.verticalCenter: parent.verticalCenter
            fillMode: Image.PreserveAspectFit
        }

        Item {
            id: backgroundStripe

            width: 400
            anchors.top: parent.top; anchors.topMargin: -((Screen.height - screenAdapter.height * Constants.screenScale)/2) / Constants.screenScale
            anchors.bottom: parent.bottom; anchors.bottomMargin: -((Screen.height - screenAdapter.height * Constants.screenScale)/2) / Constants.screenScale
            anchors.left: parent.left; anchors.leftMargin: 200

            RadialGradient {
                anchors.fill: parent
                angle: 0
                horizontalRadius: 400
                verticalRadius: height
                gradient: Gradient {
                    GradientStop { position: 0.0; color: Qt.rgba(0.8, 0.8, 0.8, 1.0) }
                    GradientStop { position: 1.0; color: Qt.rgba(0.8, 0.8, 0.8, 0.0) }
                }
            }
        }

        Column {
            anchors.centerIn: backgroundStripe
            spacing: 5

            Item {
                id: playersCountRect

                property int playerCount: 3

                width: parent.width
                height: childrenRect.height

                Row {
                    spacing: -15
                    anchors.horizontalCenter: parent.horizontalCenter

                    ColoredImage {
                        id: meeple0
                        source: "qrc:/img/bigMeeple.png"
                        color: engine ? engine.PossibleColors[currentColorOffsets[0]] : "transparent"
                    }

                    ColoredImage {
                        id: meeple1
                        source: "qrc:/img/bigMeeple.png"
                        color: engine ? engine.PossibleColors[currentColorOffsets[1]] : "transparent"
                    }

                    ColoredImage {
                        id: meeple2
                        source: "qrc:/img/bigMeeple.png"
                        color: engine ? engine.PossibleColors[currentColorOffsets[2]] : "transparent"
                        visible: playersCountRect.playerCount > 2
                    }

                    ColoredImage {
                        id: meeple3
                        source: "qrc:/img/bigMeeple.png"
                        color: engine ? engine.PossibleColors[currentColorOffsets[3]] : "transparent"
                        visible: playersCountRect.playerCount > 3
                    }
                }

                MenuArrows {
                    leftActive: playersCountRect.playerCount > 2
                    rightActive: playersCountRect.playerCount < 4

                    leftColor: "white"
                    rightColor: "white"

                    function leftClickCallback() {
                        playersCountRect.playerCount--
                    }
                    function rightClickCallback() {
                        playersCountRect.playerCount++
                    }
                }
            }

            MyText {
                anchors.horizontalCenter: parent.horizontalCenter
                text: playersCountRect.playerCount + " игрока"
                font.pixelSize: 20
            }

            Item {
                height: 10
                width: 10
            }

            Repeater {
                id: playerRepeater

                property var meeples: [meeple0, meeple1, meeple2, meeple3]
                model: currentColorOffsets
                delegate: Item {
                    id: _delegate
                    property alias text: textEdit.text

                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 300
                    height: 30

                    property var rects: [leftRect, centralRect, rightRect]
                    property color nextColor: engine ? engine.PossibleColors[root.colorIndex(currentColorOffsets[index] + 1)] : "transparent"
                    property color prevColor: engine ? engine.PossibleColors[root.colorIndex(currentColorOffsets[index] - 1)] : "transparent"

                    Rectangle {
                        id: centralRect

                        width: 300
                        height: 30
                        color: engine ? engine.PossibleColors[currentColorOffsets[index]] : "transparent"

                        Behavior on width { NumberAnimation { duration: 200 } }
                        Behavior on x { NumberAnimation { duration: 200 } }
                    }

                    Rectangle {
                        id: leftRect

                        width: 0
                        height: 30

                        Behavior on width { NumberAnimation { duration: 200 } }
                        Behavior on x { NumberAnimation { duration: 200 } }
                    }

                    Rectangle {
                        id: rightRect

                        width: 0
                        height: 30
                        x: 300

                        Behavior on width { NumberAnimation { duration: 200 } }
                        Behavior on x { NumberAnimation { duration: 200 } }
                    }

                    TextEdit {
                        id: textEdit
                        anchors.centerIn: parent
                        font.pixelSize: 20
                        font.family: Fonts.font6
                        font.bold: true
                        selectByMouse: true
                        color: "white"

                        Component.onCompleted: text = "Игрок %1".arg(index + 1)
                    }

                    MouseArea {
                        id: blocker
                        visible: index >= playersCountRect.playerCount
                        width: parent.width
                        height: parent.height

                        Rectangle {
                            anchors.fill: parent
                            color: "silver"

                            MyText {
                                anchors.centerIn: parent
                                text: "Пусто"
                                font.pixelSize: 15
                            }
                        }
                    }

                    MenuArrows {
                        leftActive: index < playersCountRect.playerCount
                        rightActive: index < playersCountRect.playerCount

                        leftColor: _delegate.prevColor
                        rightColor: _delegate.nextColor

                        function leftClickCallback() {
                            let newColorIndex = root.colorIndex(currentColorOffsets[index] - 1)
                            const LEFT = 0
                            const CENTRAL = 1
                            const RIGHT = 2
                            _delegate.rects[LEFT].color = engine.PossibleColors[newColorIndex]
                            _delegate.rects[LEFT].width = 300
                            _delegate.rects[CENTRAL].x = 300
                            _delegate.rects[CENTRAL].width = 0
                            _delegate.rects[RIGHT].x = 0

                            currentColorOffsets[index] = newColorIndex
                            playerRepeater.meeples[index].color = engine.PossibleColors[newColorIndex]
                            _delegate.nextColor = engine.PossibleColors[root.colorIndex(currentColorOffsets[index] + 1)]
                            _delegate.prevColor = engine.PossibleColors[root.colorIndex(currentColorOffsets[index] - 1)]
                            _delegate.rects = [_delegate.rects[RIGHT], _delegate.rects[LEFT], _delegate.rects[CENTRAL]]
                        }
                        function rightClickCallback() {
                            let newColorIndex = root.colorIndex(currentColorOffsets[index] + 1)
                            const LEFT = 0
                            const CENTRAL = 1
                            const RIGHT = 2
                            _delegate.rects[RIGHT].color = engine.PossibleColors[newColorIndex]
                            _delegate.rects[RIGHT].x = 0
                            _delegate.rects[RIGHT].width = 300
                            _delegate.rects[CENTRAL].width = 0
                            _delegate.rects[LEFT].x = 300

                            currentColorOffsets[index] = newColorIndex
                            playerRepeater.meeples[index].color = engine.PossibleColors[newColorIndex]
                            _delegate.nextColor = engine.PossibleColors[root.colorIndex(currentColorOffsets[index] + 1)]
                            _delegate.prevColor = engine.PossibleColors[root.colorIndex(currentColorOffsets[index] - 1)]
                            _delegate.rects = [_delegate.rects[CENTRAL], _delegate.rects[RIGHT], _delegate.rects[LEFT]]
                        }
                    }
                }
            }

            Item {
                height: 10
                width: 10
            }

            MenuButton {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Начать игру"
                actionIndicated: false
                font.family: Fonts.font4
                onClicked: {
                    var colors = []
                    var names = []
                    for (var i = 0; i < playersCountRect.playerCount; ++i) {
                        colors.push(engine.PossibleColors[currentColorOffsets[i]])
                        names.push(playerRepeater.itemAt(i).text)
                    }
                    engine.populatePlayers(colors, names)
                    engine.mapModel.setSize(15)
                    root.urlRequested("qrc:/GameWindow.qml")
                }
            }
            MenuButton {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Выход"
                actionIndicated: false
                font.family: Fonts.font4
                onClicked: {
                    root.exitRequested()
                }
            }
        }
    }
}
