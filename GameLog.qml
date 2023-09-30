import QtQuick 2.15
import QtQuick.Controls 2.15
import QmlPresenter 1.0
import EngineEnums 1.0

Item {
    id: root

    property var highlightedTile: null

    implicitWidth: 500
    implicitHeight: 500
    clip: true

    Component {
        id: scoreComponent

        EventProperties {
            id: properties

            MyText {
                bottomPadding: 5
                text: "+" + properties.score
                font.family: Fonts.funny
                font.pixelSize: 40
                color: properties.playerColor
            }
        }
    }

    Component {
        id: leadChangeComponent

        EventProperties {
            id: properties

            Rectangle {
                width: leadChangeContentRow.width + 2 * 5
                height: parent.height
                color: properties.playerColor
                radius: 5

                Image {
                    opacity: 0.3
                    source: "qrc:/img/background.png"
                    sourceSize.width: 144
                    sourceSize.height: 144
                    anchors.fill: parent
                    fillMode: Image.Tile
                }

                Row {
                    id: leadChangeContentRow

                    x: 5
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 5

                    Row {
                        height: parent.height
                        spacing: -20

                        Repeater {
                            model: properties.score

                            Image {
                                anchors.verticalCenter: parent.verticalCenter
                                source: properties.imagePath
                                height: 40
                                fillMode: Image.PreserveAspectFit
                            }
                        }
                    }

                    Image {
                        anchors.verticalCenter: parent.verticalCenter
                        height: 40
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/img/star.png"

                        MyText {
                            text: properties.objectSize
                            font.pixelSize: 20
                            anchors.centerIn: parent
                            anchors.verticalCenterOffset: 2
                        }
                    }
                }
            }
        }
    }

    Component {
        id: resourceComponent

        EventProperties {
            id: properties

            Row {
                height: parent.height
                spacing: -20

                Repeater {
                    model: properties.score

                    Image {
                        source: properties.imagePath
                        height: parent.height
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }

        }
    }

    Component {
        id: turnComponent

        EventProperties {
            id: properties

            MyText {
                text: "+ход"
                bottomPadding: 5
                font.pixelSize: 30
                color: properties.playerColor
            }
        }
    }

    Component {
        id: meepleReleaseComponent

        EventProperties {
            id: properties

            Rectangle {
                color: "white"
                height: parent.height
                width: meepleReleaseContentRow.width + 10
                radius: 5

                Image {
                    opacity: 0.3
                    source: "qrc:/img/background.png"
                    sourceSize.width: 144
                    sourceSize.height: 144
                    anchors.fill: parent
                    fillMode: Image.Tile
                }

                Row {
                    id: meepleReleaseContentRow

                    x: 5
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 5

                    Image {
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:/img/back.png"
                        width: 40
                        fillMode: Image.PreserveAspectFit
                    }

                    Repeater {
                        model: properties.meeples

                        delegate: ColoredImage {
                            anchors.verticalCenter: parent.verticalCenter
                            height: 40
                            fillMode: Image.PreserveAspectFit
                            source: {
                                switch (MEEPLE_TYPE) {
                                case EngineEnums.MeepleSmall: return "qrc:/img/smallMeeple.png"
                                case EngineEnums.MeepleBig: return "qrc:/img/bigMeeple.png"
                                case EngineEnums.MeepleBarn: return "qrc:/img/barn.png"
                                case EngineEnums.MeepleBuilder: return "qrc:/img/builder.png"
                                case EngineEnums.MeeplePig: return "qrc:/img/pig.png"
                                }
                                return ""
                            }
                            color: engine.Players.getPlayerColor(MEEPLE_PLAYER)
                        }
                    }
                }
            }
        }
    }

    Component {
        id: completionComponent

        EventProperties {
            id: properties

            Row {
                spacing: 5

                MyText {
                    bottomPadding: 5
                    text: " \u00B7 закрывает "
                    font.pixelSize: 30
                    color: "white"
                }
                MyText {
                    bottomPadding: 5
                    text: properties.objectType
                    font.pixelSize: 30
                    font.underline: true
                    color: "white"

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        hoverEnabled: true
                        onEntered: engine.highlight(properties.objectId)
                        onExited: engine.highlight(-1)
                    }
                }
                MyText {
                    bottomPadding: 5
                    text: " размером "
                    font.pixelSize: 30
                    color: "white"
                }
                MyText {
                    bottomPadding: 5
                    text: properties.objectSize
                    font.pixelSize: 30
                    color: "white"
                }
            }
        }
    }

    Component {
        id: meeplePlacementComponent

        EventProperties {
            id: properties

            Row {
                spacing: 5
                MyText {
                    bottomPadding: 5
                    text: properties.playerName
                    font.pixelSize: 30
                    color: properties.playerColor
                }
                MyText {
                    bottomPadding: 5
                    text: " ставит "
                    font.pixelSize: 30
                    color: "white"
                }
                ColoredImage {
                    anchors.verticalCenter: parent.verticalCenter
                    source: {
                        switch (properties.meepleType) {
                        case EngineEnums.MeepleSmall: return "qrc:/img/smallMeeple.png"
                        case EngineEnums.MeepleBig: return "qrc:/img/bigMeeple.png"
                        case EngineEnums.MeepleBarn: return "qrc:/img/barn.png"
                        case EngineEnums.MeepleBuilder: return "qrc:/img/builder.png"
                        case EngineEnums.MeeplePig: return "qrc:/img/pig.png"
                        }
                        return ""
                    }
                    color: properties.playerColor
                }
                MyText {
                    bottomPadding: 5
                    text: " на "
                    font.pixelSize: 30
                    color: "white"
                }
                MyText {
                    bottomPadding: 5
                    text: properties.objectType
                    font.pixelSize: 30
                    font.underline: true
                    color: "white"

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        hoverEnabled: true
                        onEntered: engine.highlight(properties.objectId)
                        onExited: engine.highlight(-1)
                    }
                }
            }
        }
    }

    Component {
        id: extensionComponent

        EventProperties {
            id: properties

            Row {
                spacing: 5

                MyText {
                    bottomPadding: 5
                    text: " \u00B7 дополняет "
                    font.pixelSize: 30
                    color: "white"
                }
                MyText {
                    bottomPadding: 5
                    text: properties.objectType
                    font.pixelSize: 30
                    font.underline: true
                    color: "white"

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        hoverEnabled: true
                        onEntered: engine.highlight(properties.objectId)
                        onExited: engine.highlight(-1)
                    }
                }
                MyText {
                    bottomPadding: 5
                    text: " со строителем"
                    font.pixelSize: 30
                    color: "white"
                }
            }
        }
    }

    Component {
        id: tilePlacementComponent

        EventProperties {
            id: properties

            Row {
                spacing: 5
                MyText {
                    bottomPadding: 5
                    text: properties.playerName
                    font.pixelSize: 30
                    color: properties.playerColor
                }
                MyText {
                    bottomPadding: 5
                    text: " кладёт "
                    font.pixelSize: 30
                    color: "white"
                }
                MyText {
                    bottomPadding: 5
                    text: "фишку"
                    font.pixelSize: 30
                    font.underline: true
                    color: "white"

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        hoverEnabled: true
                        onEntered: root.highlightedTile = properties.tile
                        onExited: root.highlightedTile = null
                    }
                }
            }
        }
    }

    ScrollView {
        id: scrollView

        contentWidth: parent.width - 2 * 10
        anchors.horizontalCenter: parent.horizontalCenter
        height: parent.height
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        function scrollToBottom() {
            ScrollBar.vertical.position = childrenRect.height
        }

        Column {
            id: turnColumn
            width: parent.width - 15 // offset for the scrollbar
            spacing: 10

            onHeightChanged: scrollView.scrollToBottom()

            Repeater {
                id: turnRepeater

                model: engine ? engine.TurnLog : []

                TintColoredRectangle {
                    id: turnBackground

                    width: parent.width
                    height: actionColumn.implicitHeight + 10
                    color: "white"
                    tintColor: COLOR
                    tintOpacity: 0.5
                    radius: 10

                    Column {
                        id: actionColumn

                        anchors.top: parent.top; anchors.topMargin: 5
                        width: parent.width
                        spacing: 5

                        Item {
                            width: parent.width
                            height: childrenRect.height

                            Rectangle {
                                color: "white"
                                height: 1
                                anchors.verticalCenter: turnText.verticalCenter
                                anchors.left: parent.left
                                anchors.right: turnText.left
                                anchors.margins: 10
                            }

                            MyText {
                                id: turnText

                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "Ход " + TURN
                                font.pixelSize: 25
                                color: "white"
                            }

                            Rectangle {
                                color: "white"
                                height: 1
                                anchors.verticalCenter: turnText.verticalCenter
                                anchors.left: turnText.right
                                anchors.right: parent.right
                                anchors.margins: 10
                            }
                        }

                        Repeater {
                            id: actionsRepeater

                            model: ACTIONS

                            Item {
                                width: parent.width
                                height: childrenRect.height

                                Loader {
                                    id: actionLoader

                                    property var init

                                    anchors.left: parent.left; anchors.leftMargin: 10
                                    height: 48
                                    onLoaded: init(item)
                                    sourceComponent: {
                                        switch (EVENT_TYPE) {
                                        case EngineEnums.LogObjectCompletion:
                                            init = function(obj) {
                                                obj.playerName = NAME
                                                obj.playerColor = COLOR
                                                obj.objectType = OBJECT_TYPE
                                                obj.objectId = OBJECT_ID
                                                obj.objectSize = OBJECT_SIZE
                                            }
                                            return completionComponent
                                        case EngineEnums.LogMeeplePlaced:
                                            init = function(obj) {
                                                obj.playerName = NAME
                                                obj.playerColor = COLOR
                                                obj.meepleType = MEEPLE_TYPE
                                                obj.objectType = OBJECT_TYPE
                                                obj.objectId = OBJECT_ID
                                            }
                                            return meeplePlacementComponent
                                        case EngineEnums.LogFreeTurn:
                                            init = function(obj) {
                                                obj.playerName = NAME
                                                obj.playerColor = COLOR
                                                obj.objectType = OBJECT_TYPE
                                                obj.objectId = OBJECT_ID
                                            }
                                            return extensionComponent
                                        case EngineEnums.LogTilePlaced:
                                            init = function(obj) {
                                                obj.playerName = NAME
                                                obj.playerColor = COLOR
                                                obj.tile = TILE
                                            }
                                            return tilePlacementComponent
                                        default:
                                            return null
                                        }
                                    }
                                }

                                Flow {
                                    id: effectsFlow

                                    anchors.right: parent.right; anchors.rightMargin: 10
                                    anchors.left: actionLoader.right; anchors.leftMargin: 100
                                    spacing: 5
                                    layoutDirection: Qt.RightToLeft

                                    Repeater {
                                        id: effectsRepeater

                                        model: EFFECTS

                                        Loader {
                                            property var init

                                            height: 48
                                            onLoaded: init(item)
                                            sourceComponent: {
                                                switch (EVENT_TYPE) {
                                                case EngineEnums.LogScoring:
                                                    init = function(obj) {
                                                        obj.score = POINTS
                                                        obj.playerColor = COLOR
                                                    }
                                                    return scoreComponent
                                                case EngineEnums.LogFreeTurn:
                                                    init = function(obj) {
                                                        obj.playerColor = COLOR
                                                    }
                                                    return turnComponent
                                                case EngineEnums.LogRoadLeadChange: {
                                                    init = function(obj) {
                                                        obj.playerColor = COLOR
                                                        obj.objectSize = OBJECT_SIZE
                                                        obj.score = 1 // 1 badge acquired
                                                        obj.imagePath = "qrc:/img/chieftain.png"
                                                    }
                                                    return leadChangeComponent
                                                }
                                                case EngineEnums.LogTownLeadChange: {
                                                    init = function(obj) {
                                                        obj.playerColor = COLOR
                                                        obj.objectSize = OBJECT_SIZE
                                                        obj.score = 1 // 1 badge acquired
                                                        obj.imagePath = "qrc:/img/king.png"
                                                    }
                                                    return leadChangeComponent
                                                }
                                                case EngineEnums.LogMeeplesReleased:
                                                    init = function(obj) {
                                                        obj.meeples = MEEPLES
                                                    }
                                                    return meepleReleaseComponent
                                                case EngineEnums.LogResourceLeadChange: {
                                                    init = function(obj) {
                                                        obj.playerColor = COLOR
                                                        obj.objectSize = OBJECT_SIZE
                                                        obj.score = POINTS
                                                        switch (RESOURCE_TYPE) {
                                                        case EngineEnums.Barrel: obj.imagePath = "qrc:/img/barrel.png"; break
                                                        case EngineEnums.Wheat: obj.imagePath = "qrc:/img/wheat.png"; break
                                                        case EngineEnums.Cloth: obj.imagePath = "qrc:/img/cloth.png"
                                                        }
                                                    }
                                                    return leadChangeComponent
                                                }
                                                case EngineEnums.LogResource: {
                                                    init = function(obj) {
                                                        obj.score = POINTS
                                                        switch (RESOURCE_TYPE) {
                                                        case EngineEnums.Barrel: obj.imagePath = "qrc:/img/barrel.png"; break
                                                        case EngineEnums.Wheat: obj.imagePath = "qrc:/img/wheat.png"; break
                                                        case EngineEnums.Cloth: obj.imagePath = "qrc:/img/cloth.png"
                                                        }
                                                    }
                                                    return resourceComponent
                                                }
                                                default:
                                                    return null
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            MyText {
                anchors.horizontalCenter: parent.horizontalCenter
                color: "white"
                text: "Конец игры"
                font.pixelSize: 25
                visible: engine.GameState === GameEngine.GameEnd
            }
        }
    }
}
