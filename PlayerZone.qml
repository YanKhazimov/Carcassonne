import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import com.carcassonne.cppTypes 1.0
import QmlPresenter 1.0
import EngineEnums 1.0

Rectangle {
    id: root

    required property int playerIndex
    readonly property Player playerData: engine ? engine.getPlayer(playerIndex) : null
    readonly property color activeColor: playerData ? playerData.Color : "transparent"

    readonly property real smallMeeplePositionX: meeplePositioner.x + smallMeeplePlaceholder.x
    readonly property real smallMeeplePositionY: meeplePositioner.y + smallMeeplePlaceholder.y
    property int smallMeepleCount: 8
    readonly property real bigMeeplePositionX: meeplePositioner.x + bigMeeplePlaceholder.x
    readonly property real bigMeeplePositionY: meeplePositioner.y + bigMeeplePlaceholder.y
    property int bigMeepleCount: 2
    readonly property real barnPositionX: meeplePositioner.x + barnPlaceholder.x
    readonly property real barnPositionY: meeplePositioner.y + barnPlaceholder.y
    property int barnCount: 1
    readonly property real pigPositionX: meeplePositioner.x + pigPlaceholder.x
    readonly property real pigPositionY: meeplePositioner.y + pigPlaceholder.y
    property int pigCount: 1
    readonly property real builderPositionX: meeplePositioner.x + builderPlaceholder.x
    readonly property real builderPositionY: meeplePositioner.y + builderPlaceholder.y
    property int builderCount: 1

    readonly property real abbeyPositionX: abbeyPlaceholder.x
    readonly property real abbeyPositionY: abbeyPlaceholder.y
    readonly property real regularTilePositionX: regularTilePlaceholder.x
    readonly property real regularTilePositionY: regularTilePlaceholder.y

    property int buttonsOffset: 0

    required property int tilesInDeck

    signal tileClicked()

    function addMeeple(meepleType, diff) {
        switch (meepleType) {
        case EngineEnums.MeepleSmall: smallMeepleCount += diff; break;
        case EngineEnums.MeepleBig: bigMeepleCount += diff; break;
        case EngineEnums.MeepleBarn: barnCount += diff; break;
        case EngineEnums.MeeplePig: pigCount += diff; break;
        case EngineEnums.MeepleBuilder: builderCount += diff; break;
        }
    }

    implicitWidth: 100
    implicitHeight: 200
    color: "white"
    border.width: 2
    border.color: activeColor
    radius: 10

    Rectangle {
        anchors.fill: parent
        color: activeColor
        opacity: 0.3
        radius: root.radius
    }

    TextEdit {
        id: playerName

        anchors.top: parent.top; anchors.topMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 20
        text: playerData ? playerData.Name : ""
        selectByMouse: true
        Keys.onEscapePressed: focus = false
    }

    Binding {
        target: playerData
        property: "Name"
        value: playerName.text
        when: playerData
    }

    Rectangle {
        id: separator

        height: 2
        anchors.top: playerName.bottom; anchors.topMargin: 5
        anchors.left: parent.left; anchors.leftMargin: 10
        anchors.right: parent.right; anchors.rightMargin: 10

        LinearGradient {
            anchors.fill: parent
            start: Qt.point(0, 0)
            end: Qt.point(parent.width, 0)
            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(activeColor.r, activeColor.g, activeColor.b, 0.3) }
                GradientStop { position: 0.5; color: root.activeColor }
                GradientStop { position: 1.0; color: Qt.rgba(activeColor.r, activeColor.g, activeColor.b, 0.3) }
            }
        }
    }

    Row {
        id: timerRow

        anchors.top: separator.bottom; anchors.topMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 0

        Text {
            id: prevTurnsTime
            text: Qt.formatTime(new Date(0, 0, 0, 0, 0, playerData ? playerData.PreviousTime : 0), "mm:ss")
            font.pixelSize: 15
            visible: playerData && playerData.PreviousTime !== 0 || !currentTurnTime.visible
        }

        Text {
            text: " + "
            font.pixelSize: 15
            visible: prevTurnsTime.visible && currentTurnTime.visible
        }

        Text {
            id: currentTurnTime
            text: Qt.formatTime(new Date(0, 0, 0, 0, 0, playerData ? playerData.CurrentTime : 0), "mm:ss")
            font.pixelSize: 15
            visible: playerData && playerData.CurrentTime !== 0
            color: playerData && playerData.CurrentTime > 30 ? "white" : "black"

            Rectangle {
                anchors.fill: parent
                anchors.margins: -3
                radius: 3
                color: "red"
                visible: playerData && playerData.CurrentTime > 30
                z: parent.z - 1
            }
        }
    }

    Row {
        anchors.top: timerRow.bottom; anchors.topMargin: 5
        anchors.left: parent.left; anchors.leftMargin: 10
        spacing: 15

        Row {
            TileBonusIndicator {
                source: "qrc:/img/barrel.png"
                width: 32
                height: 32
                anchors.verticalCenter: parent.verticalCenter
            }
            Text {
                text: playerData ? " x" + playerData.Barrels : ""
                font.pixelSize: playerData && playerData.BarrelsLead ? 40 : 20
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            TileBonusIndicator {
                source: "qrc:/img/wheat.png"
                width: 32
                height: 32
                anchors.verticalCenter: parent.verticalCenter
            }
            Text {
                text: playerData ? " x" + playerData.Wheat : ""
                font.pixelSize: playerData && playerData.WheatLead ? 40 : 20
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            TileBonusIndicator {
                source: "qrc:/img/cloth.png"
                width: 32
                height: 32
                anchors.verticalCenter: parent.verticalCenter
            }
            Text {
                text: playerData ? " x" + playerData.Cloth : ""
                font.pixelSize: playerData && playerData.ClothLead ? 40 : 20
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Row {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 10
        spacing: 5

        Row {
            visible: playerData && playerData.TownLead

            Text {
                text: engine ? ("город: " + engine.MaxTown) : ""
                font.pixelSize: 20
                anchors.verticalCenter: parent.verticalCenter
            }
            LeadIndicator {
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            visible: playerData && playerData.RoadLead

            Text {
                text: engine ? ("дорога: " + engine.MaxRoad) : ""
                font.pixelSize: 20
                anchors.verticalCenter: parent.verticalCenter
            }
            LeadIndicator {
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }


    Rectangle {
        id: regularTilePlaceholder

        anchors.bottom: parent.bottom; anchors.bottomMargin: 10
        anchors.right: abbeyPlaceholder.left; anchors.rightMargin: 10
        width: Constants.tilePreviewSize
        height: Constants.tilePreviewSize
        color: "transparent"
        border.width: 2
        border.color: Constants.color.schematic.road

        Image {
            anchors.centerIn: parent
            source: "qrc:/img/x_icon.png"
        }

        Image {
            id: tileBack

            source: "qrc:/img/tileBack.png"
            anchors.fill: parent
            visible: tilesInDeck > 0
        }

        MouseArea {
            id: deckBackMouseArea
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            visible: engine && tilesInDeck > 0 && !engine.AllFttingTilesPlayed && playerData && playerData.IsActive &&
                     (engine.GameState === GameEngine.NewTurn ||
                      engine.GameState === GameEngine.TilePlaced &&
                      engine.getAbbeyTile(engine.ActivePlayer).IsPlaced &&
                      !engine.getAbbeyTile(engine.ActivePlayer).IsFixed)
            onClicked: tileClicked()
        }

        ElementActionIndicator {
            target: parent
            visible: deckBackMouseArea.visible
        }
    }

    Text {
        anchors.bottom: regularTilePlaceholder.top; anchors.bottomMargin: 5
        anchors.horizontalCenter: regularTilePlaceholder.horizontalCenter
        text: "x" + tilesInDeck
        font.pixelSize: 20
    }

    Rectangle {
        id: abbeyPlaceholder

        anchors.bottom: parent.bottom; anchors.bottomMargin: 10
        anchors.right: parent.right; anchors.rightMargin: root.buttonsOffset + 10
        width: Constants.tilePreviewSize
        height: Constants.tilePreviewSize
        color: "transparent"
        border.width: 2
        border.color: Constants.color.schematic.road

        Image {
            anchors.centerIn: parent
            source: "qrc:/img/x_icon.png"
        }
    }

    RowLayout {
        id: meeplePositioner

        anchors.right: regularTilePlaceholder.left
        anchors.bottom: regularTilePlaceholder.bottom
        anchors.margins: 10
        spacing: 10
        opacity: 0.2

        MeepleSmall {
            id: smallMeeplePlaceholder
            draggable: false
            playerIndex: root.playerIndex
            Layout.alignment: Qt.AlignHCenter
        }

        MeepleBig {
            id: bigMeeplePlaceholder
            draggable: false
            playerIndex: root.playerIndex
            Layout.alignment: Qt.AlignHCenter
        }

        MeepleBarn {
            id: barnPlaceholder
            draggable: false
            playerIndex: root.playerIndex
            Layout.alignment: Qt.AlignHCenter
        }

        MeepleBuilder {
            id: builderPlaceholder
            draggable: false
            playerIndex: root.playerIndex
            Layout.alignment: Qt.AlignHCenter
        }

        MeeplePig {
            id: pigPlaceholder
            draggable: false
            playerIndex: root.playerIndex
            Layout.alignment: Qt.AlignHCenter
        }
    }

    Text {
        text: "x" + smallMeepleCount
        x: smallMeeplePositionX + Constants.smallMeepleSize/2 - width/2
        anchors.bottom: meeplePositioner.top; anchors.bottomMargin: 10/2
        font.pixelSize: 20
    }
    Text {
        text: "x" + bigMeepleCount
        x: bigMeeplePositionX + 2 * Constants.smallMeepleSize/2 - width/2
        anchors.bottom: meeplePositioner.top; anchors.bottomMargin: 10/2
        font.pixelSize: 20
    }
    Text {
        text: "x" + barnCount
        x: barnPositionX + 2 * Constants.smallMeepleSize/2 - width/2
        anchors.bottom: meeplePositioner.top; anchors.bottomMargin: 10/2
        font.pixelSize: 20
    }
    Text {
        text: "x" + builderCount
        x: builderPositionX + Constants.smallMeepleSize/2 - width/2
        anchors.bottom: meeplePositioner.top; anchors.bottomMargin: 10/2
        font.pixelSize: 20
    }
    Text {
        text: "x" + pigCount
        x: pigPositionX + 2 * Constants.smallMeepleSize/2 - width/2
        anchors.bottom: meeplePositioner.top; anchors.bottomMargin: 10/2
        font.pixelSize: 20
    }
}
