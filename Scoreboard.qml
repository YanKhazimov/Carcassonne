import QtQuick 2.15
import QtGraphicalEffects 1.15
import QmlPresenter 1.0

Item {
    id: root

    width: childrenRect.width
    height: childrenRect.height

    Row {
        id: header

        Item {
            width: 150
            height: 30
        }

        Rectangle {
            width: 75
            height: 30
            color: "white"
            border.color: "#DDDDDD"

            Text {
                text: "Счет"
                anchors.centerIn: parent
                font.pixelSize: 20
            }
        }

        Rectangle {
            width: 75
            height: 30
            color: "white"
            border.color: "#DDDDDD"

            Text {
                text: "Король"
                anchors.centerIn: parent
                font.pixelSize: 15
            }
        }

        Rectangle {
            width: 75
            height: 30
            color: "white"
            border.color: "#DDDDDD"

            Text {
                text: "Атаман"
                anchors.centerIn: parent
                font.pixelSize: 15
            }
        }

        Rectangle {
            width: 75
            height: 30
            color: "white"
            border.color: "#DDDDDD"

            Text {
                text: "Ресурсы"
                anchors.centerIn: parent
                font.pixelSize: 15
            }
        }
    }

    Repeater {
        model: engine ? engine.Players : []
        delegate: Row {
            y: PLACE * 30
            z: placeAnimation.running ? 1 : 0

            Behavior on y {
                NumberAnimation {
                    id: placeAnimation
                    duration: 1000
                }
            }

            Rectangle {
                width: 150
                height: 30
                color: "transparent"
                LinearGradient {
                    anchors.fill: parent
                    anchors.margins: 1
                    start: Qt.point(0, 0)
                    end: Qt.point(parent.width, 0)
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "transparent" }
                        GradientStop { position: 1.0; color: Qt.rgba(COLOR.r, COLOR.g, COLOR.b, 0.3) }
                    }
                }

                Text {
                    text: NAME
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    elide: Text.ElideRight
                    font.pixelSize: 15
                }
            }

            Rectangle {
                width: 75
                height: 30
                color: Qt.rgba(COLOR.r, COLOR.g, COLOR.b, 0.3)
                border.color: "#DDDDDD"

                Text {
                    property int animatedScore: SCORE
                    Behavior on animatedScore { NumberAnimation { id: scoreAnimation; duration: 1000 } }
                    text: animatedScore
                    anchors.centerIn: parent
                    font.pixelSize: 25
                }
            }

            Rectangle {
                width: 75
                height: 30
                color: Qt.rgba(COLOR.r, COLOR.g, COLOR.b, 0.3)
                border.color: "#DDDDDD"

                Text {
                    property int animatedScore: TOWN_LEAD ? BIGGEST_TOWN : 0
                    Behavior on animatedScore { NumberAnimation { duration: 1000 } }
                    text: "+" + animatedScore
                    visible: animatedScore > 0
                    anchors.centerIn: parent
                    font.pixelSize: 15
                }

                MouseArea {
                    id: townLeadMouseArea

                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    visible: TOWN_LEAD && engine.GameState === GameEngine.GameEnd
                    onClicked: {
                        engine.getPlayer(index).scorePoints(BIGGEST_TOWN)
                        engine.getPlayer(index).setTownLead(false)
                    }

                    Loader { // just putting ElementActionIndicator does not work
                        anchors.fill: parent
                        sourceComponent: ElementActionIndicator {
                            target: parent
                        }
                    }
                }
            }

            Rectangle {
                width: 75
                height: 30
                color: Qt.rgba(COLOR.r, COLOR.g, COLOR.b, 0.3)
                border.color: "#DDDDDD"

                Text {
                    property int animatedScore: ROAD_LEAD ? BIGGEST_ROAD : 0
                    Behavior on animatedScore { NumberAnimation { duration: 1000 } }
                    text: "+" + animatedScore
                    visible: animatedScore > 0
                    anchors.centerIn: parent
                    font.pixelSize: 15
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    visible: ROAD_LEAD && engine.GameState === GameEngine.GameEnd
                    onClicked: {
                        engine.getPlayer(index).scorePoints(BIGGEST_ROAD)
                        engine.getPlayer(index).setRoadLead(false)
                    }

                    Loader { // just putting ElementActionIndicator does not work
                        anchors.fill: parent
                        sourceComponent: ElementActionIndicator {
                            target: parent
                        }
                    }
                }
            }

            Rectangle {
                width: 75
                height: 30
                color: Qt.rgba(COLOR.r, COLOR.g, COLOR.b, 0.3)
                border.color: "#DDDDDD"

                Text {
                    property int animatedScore: WHEAT_LEAD * 10 + BARRELS_LEAD * 10 + CLOTH_LEAD * 10
                    Behavior on animatedScore { NumberAnimation { duration: 1000 } }
                    text: "+" + animatedScore
                    visible: animatedScore > 0
                    anchors.centerIn: parent
                    font.pixelSize: 15
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    visible: (WHEAT_LEAD || BARRELS_LEAD || CLOTH_LEAD) && engine.GameState === GameEngine.GameEnd
                    onClicked: {
                        engine.getPlayer(index).scorePoints(WHEAT_LEAD * 10 + BARRELS_LEAD * 10 + CLOTH_LEAD * 10)
                        engine.getPlayer(index).setWheatLead(false)
                        engine.getPlayer(index).setBarrelsLead(false)
                        engine.getPlayer(index).setClothLead(false)
                    }

                    Loader { // just putting ElementActionIndicator does not work
                        anchors.fill: parent
                        sourceComponent: ElementActionIndicator {
                            target: parent
                        }
                    }
                }
            }
        }
    }
}
