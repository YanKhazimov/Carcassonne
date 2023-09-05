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
            width: 250
            height: 30
        }

        Rectangle {
            width: 75
            height: 30
            color: "white"
            border.color: "#DDDDDD"

            MyText {
                text: "СЧЁТ"
                anchors.centerIn: parent
                font.pixelSize: 20
                font.family: Fonts.bonuses
            }
        }

        Rectangle {
            width: 75
            height: 30
            color: "white"
            border.color: "#DDDDDD"

            MyText {
                text: "КОРОЛЬ"
                anchors.centerIn: parent
                font.pixelSize: 15
                font.family: Fonts.bonuses
            }
        }

        Rectangle {
            width: 75
            height: 30
            color: "white"
            border.color: "#DDDDDD"

            MyText {
                text: "АТАМАН"
                anchors.centerIn: parent
                font.pixelSize: 15
                font.family: Fonts.bonuses
            }
        }

        Rectangle {
            width: 75
            height: 30
            color: "white"
            border.color: "#DDDDDD"

            MyText {
                text: "РЕСУРСЫ"
                anchors.centerIn: parent
                font.pixelSize: 15
                font.family: Fonts.bonuses
            }
        }
    }

    Repeater {
        model: engine ? engine.Players : []
        delegate: Row {
            id: playerRow

            readonly property int modelPlace: PLACE
            property int visualPlace

            y: visualPlace * 30
            Component.onCompleted: visualPlace = modelPlace
            onModelPlaceChanged: {
                z = modelPlace < visualPlace ? 1 : 0 // scoring player's row gets in the foreground
                visualPlace = modelPlace
            }

            Behavior on y {
                NumberAnimation {
                    id: placeAnimation
                    duration: 1000
                    onRunningChanged: {
                        if (!running)
                            playerRow.z = 0
                    }
                }
            }

            Item {
                width: 250
                height: 30

                TintColoredRectangle {
                    id: nameRectangleSource

                    visible: false
                    anchors.fill: parent
                    color: "white"
                    border.color: "#DDDDDD"
                    tintColor: COLOR
                    tintOpacity: 0.5
                }

                Item {
                    id: nameRectangleMask

                    anchors.fill: parent
                    visible: false

                    LinearGradient {
                        anchors.fill: parent
                        start: Qt.point(0, 0)
                        end: Qt.point(parent.width, 0)
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "transparent" }
                            GradientStop { position: 1.0; color: Qt.rgba(1.0, 1.0, 1.0) }
                        }
                    }
                }

                OpacityMask {
                    source: nameRectangleSource
                    anchors.fill: parent
                    maskSource: nameRectangleMask
                }

                MyText {
                    text: NAME
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    elide: Text.ElideRight
                    font.pixelSize: 15
                    font.family: Fonts.font6
                }
            }

            TintColoredRectangle {
                width: 75
                height: 30
                color: "white"
                border.color: "#DDDDDD"
                tintColor: COLOR
                tintOpacity: 0.5

                MyText {
                    property int animatedScore: SCORE
                    Behavior on animatedScore { NumberAnimation { id: scoreAnimation; duration: 1000 } }
                    text: animatedScore
                    anchors.centerIn: parent
                    font.pixelSize: 25
                    font.family: Fonts.bonuses
                }
            }

            TintColoredRectangle {
                width: 75
                height: 30
                color: "white"
                border.color: "#DDDDDD"
                tintColor: COLOR
                tintOpacity: 0.5

                MyText {
                    property int animatedScore: TOWN_LEAD ? BIGGEST_TOWN : 0
                    Behavior on animatedScore { NumberAnimation { duration: 1000 } }
                    text: "+" + animatedScore
                    visible: animatedScore > 0
                    anchors.centerIn: parent
                    font.pixelSize: 15
                    font.family: Fonts.bonuses
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

            TintColoredRectangle {
                width: 75
                height: 30
                color: "white"
                border.color: "#DDDDDD"
                tintColor: COLOR
                tintOpacity: 0.5

                MyText {
                    property int animatedScore: ROAD_LEAD ? BIGGEST_ROAD : 0
                    Behavior on animatedScore { NumberAnimation { duration: 1000 } }
                    text: "+" + animatedScore
                    visible: animatedScore > 0
                    anchors.centerIn: parent
                    font.pixelSize: 15
                    font.family: Fonts.bonuses
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

            TintColoredRectangle {
                width: 75
                height: 30
                color: "white"
                border.color: "#DDDDDD"
                tintColor: COLOR
                tintOpacity: 0.5

                MyText {
                    property int animatedScore: WHEAT_LEAD * 10 + BARRELS_LEAD * 10 + CLOTH_LEAD * 10
                    Behavior on animatedScore { NumberAnimation { duration: 1000 } }
                    text: "+" + animatedScore
                    visible: animatedScore > 0
                    anchors.centerIn: parent
                    font.pixelSize: 15
                    font.family: Fonts.bonuses
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

            Item {
                width: 250
                height: 30

                TintColoredRectangle {
                    id: timeRectangleSource

                    visible: false
                    anchors.fill: parent
                    color: "white"
                    border.color: "#DDDDDD"
                    tintColor: COLOR
                    tintOpacity: 0.5
                }

                Item {
                    id: timeRectangleMask

                    anchors.fill: parent
                    visible: false

                    LinearGradient {
                        anchors.fill: parent
                        start: Qt.point(parent.width, 0)
                        end: Qt.point(0, 0)
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "transparent" }
                            GradientStop { position: 1.0; color: Qt.rgba(1.0, 1.0, 1.0) }
                        }
                    }
                }

                OpacityMask {
                    source: timeRectangleSource
                    anchors.fill: parent
                    maskSource: timeRectangleMask
                }

                Row {
                    id: timerRow

                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 0

                    Text {
                        id: prevTurnsTime

                        text: Qt.formatTime(new Date(0, 0, 0, 0, 0, PAST_TURNS_TIME), PAST_TURNS_TIME > 3599 ? "h:mm:ss" : "mm:ss")
                        font.pixelSize: 15
                        font.family: Fonts.font4
                        visible: PAST_TURNS_TIME !== 0 || !currentTurnTime.visible
                    }

                    Text {
                        text: " + "
                        font.pixelSize: 15
                        font.family: Fonts.font4
                        visible: prevTurnsTime.visible && currentTurnTime.visible
                    }

                    Text {
                        id: currentTurnTime

                        text: Qt.formatTime(new Date(0, 0, 0, 0, 0, CURRENT_TURN_TIME), CURRENT_TURN_TIME > 3599 ? "h:mm:ss" : "mm:ss")
                        font.pixelSize: 15
                        font.family: Fonts.font4
                        visible: CURRENT_TURN_TIME !== 0
                        color: CURRENT_TURN_TIME > 30 ? "white" : "black"

                        Rectangle {
                            anchors.fill: parent
                            anchors.margins: -3
                            radius: 3
                            color: "red"
                            visible: CURRENT_TURN_TIME > 30
                            z: parent.z - 1
                        }
                    }
                }
            }
        }
    }
}
