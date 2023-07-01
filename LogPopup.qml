import QtQuick 2.15
import QtQuick.Controls 2.15
import EngineEnums 1.0

Popup {
    id: root

    implicitWidth: 500
    implicitHeight: 500
    topPadding: 50

    background: Rectangle {
        color: "lightgrey"

        Text {
            text: "Ход игры"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 25
        }
    }

    contentItem: ScrollView {
        contentWidth: availableWidth
        clip: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        Column {
            width: parent.width
            spacing: 20

            Repeater {
                model: engine ? engine.GameLog : []

                Text {
                    textFormat: Text.StyledText
                    text: {
                        let meepleImage = {
                            1: "qrc:/img/smallMeeple.png",
                            2: "qrc:/img/bigMeeple.png",
                            3: "qrc:/img/barn.png",
                            4: "qrc:/img/builder.png",
                            5: "qrc:/img/pig.png"
                        }
                        let imageWidth = {
                            1: "20",
                            2: "40",
                            3: "40",
                            4: "20",
                            5: "40"
                        }
                        let imageHeight = {
                            1: "20",
                            2: "40",
                            3: "40",
                            4: "40",
                            5: "20"
                        }
                        switch(TYPE) {
                        case EngineEnums.LogScoring:
                            return "<ul><li><font color=\"%3\" size=\"7\">%1</font> получает <font size=\"5\">%2</font> очков</li></ul>".arg(NAME).arg(POINTS).arg(COLOR)
                        case EngineEnums.LogObjectCompletion:
                            return "<font color=\"%3\" size=\"7\">%1</font> достраивает <font size=\"5\">%2</font> размера <font size=\"5\">%4</font>".arg(NAME).arg(OBJECT_TYPE).arg(COLOR).arg(OBJECT_SIZE)
                        case EngineEnums.LogFreeTurn:
                            return "<ul><li>Строитель приносит игроку <font color=\"%2\" size=\"7\">%1</font> дополнительный ход</li></ul>".arg(NAME).arg(COLOR)
                        case EngineEnums.LogRoadLeadChange:
                            return "<ul><li><font color=\"%2\" size=\"7\">%1</font> становится <font size=\"5\">атаманом</font> с дорогой размера <font size=\"5\">%3</font></li></ul>".arg(NAME).arg(COLOR).arg(OBJECT_SIZE)
                        case EngineEnums.LogTownLeadChange:
                            return "<ul><li><font color=\"%2\" size=\"7\">%1</font> становится <font size=\"5\">королем</font> с городом размера <font size=\"5\">%3</font></li></ul>".arg(NAME).arg(COLOR).arg(OBJECT_SIZE)
                        case EngineEnums.LogMeeplePlaced:
                            return "<font color=\"%1\" size=\"7\">%2</font> занимает <font size=\"5\">%3</font>, используя <img src=\"%4\" align=\"middle\" width=\"%5\" height=\"%6\">"
                            .arg(COLOR).arg(NAME).arg(OBJECT_TYPE).arg(meepleImage[MEEPLE_TYPE]).arg(imageWidth).arg(imageHeight)
                        case EngineEnums.LogMeepleReleased:
                            let images = ""
                            for (let i = 0; i < MEEPLE_TYPES.length; ++i)
                                images += "<img src=\"%1\" align=\"middle\" width=\"%2\" height=\"%3\">, ".arg(meepleImage[MEEPLE_TYPES[i]]).arg(imageWidth).arg(imageHeight)
                            return "<ul><li>%1 освобождаются</li></ul>".arg(images)
                        case EngineEnums.LogNewTurn:
                            return "Ход %1".arg(OBJECT_SIZE)
                        case EngineEnums.LogResourceLeadChange:
                            return "<ul><li><font color=\"%2\" size=\"7\">%1</font> становится лидером по %3 <font size=\"5\">(%4)</font></li></ul>".arg(NAME).arg(COLOR).arg(OBJECT_TYPE).arg(OBJECT_SIZE)
                        case EngineEnums.LogGameEnd:
                            return "Подсчет очков"
                        default:
                            return "Неизвестное событие"
                        }
                    }
                }
            }
        }
    }
}
