import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQml 2.15
import QmlPresenter 1.0
import "schematic"

Item {
    id: root

    width: 1280
    height: 980
    property var tiles: []
    property var abbeyTiles: []
    property var meeples: []
    property var activeMeeple: null
    readonly property var zones: [playerZoneNW, playerZoneNE, playerZoneSW, playerZoneSE]
    readonly property var zoneColumns: [leftPlayers, rightPlayers, leftPlayers, rightPlayers]
    property int tilesInDeck
    property Item lastPlacedTile: null

    signal urlRequested(var urlAddress)

    Binding {
        target: engine
        property: "TilePictureOpacity"
        value: activeMeeple ? 0.6 : 1
    }

    Binding {
        target: Constants.color.schematic
        property: "highlighter"
        value: (lastPlacedTile && lastPlacedTile.acceptsActiveMeeple) ? Constants.color.schematic.highlighterRight : Constants.color.schematic.highlighterWrong
        when: lastPlacedTile && activeMeeple && activeMeeple.dragActive
        restoreMode: Binding.RestoreBindingOrValue
    }

    function createTileItem(x, y) {
        var comp = Qt.createComponent("Tile.qml")
        if (comp.status === Component.Ready) {
            var obj = comp.createObject(root,
                                     {
                                         "tileData": engine.getTile(tiles.length),
                                         "x": x,
                                         "y": y,
                                         "board": board
                                     })
            obj.dragStarted.connect(function() {
                if (abbeyTiles[engine.ActivePlayer].tileData.IsPlaced && !abbeyTiles[engine.ActivePlayer].tileData.IsFixed)
                {
                    abbeyTiles[engine.ActivePlayer].tileData.displace()
                    abbeyTiles[engine.ActivePlayer].resetPosition()
                    engine.GameState = engine.deck.rowCount() - tiles.length === tilesInDeck ?
                                GameEngine.NewTurn : GameEngine.TileDrawn
                }

                if (engine.GameState === GameEngine.TileDrawn)
                {
                    // the drag is from a player zone
                    tilesInDeck--
                }
            })
            obj.dragCancelled.connect(function() {
                tilesInDeck++
                engine.GameState = GameEngine.TileDrawn
            })

            return obj
        }
        console.error("Tile component status:", comp.status, comp.errorString())
        return null
    }

    function createAbbeyTileItem(x, y, playerIndex) {
        var comp = Qt.createComponent("Tile.qml")
        if (comp.status === Component.Ready) {
            var obj = comp.createObject(root,
                                        {
                                            "tileData": engine.getAbbeyTile(playerIndex),
                                            "x": x,
                                            "y": y,
                                            "board": board,
                                            "z": 1,
                                            "playerIndex": playerIndex
                                        })
            obj.dragStarted.connect(function() {
                if (tiles[tiles.length - 1].tileData.IsPlaced &&
                        !tiles[tiles.length - 1].tileData.IsFixed) {
                    tiles[tiles.length - 1].tileData.displace()
                    tiles[tiles.length - 1].resetPosition()
                    tilesInDeck++
                    engine.GameState = GameEngine.TileDrawn
                }
            })

            obj.dragCancelled.connect(function() {
                engine.GameState = engine.deck.rowCount() - tiles.length === tilesInDeck ?
                            GameEngine.NewTurn : GameEngine.TileDrawn
            })
            return obj
        }
        console.error("Abbey tile component status:", comp.status, comp.errorString())
        return null
    }

    function createMeepleItem(type, x, y, playerIndex) {
        var comp = Qt.createComponent(type)
        if (comp.status === Component.Ready) {
            var obj = comp.createObject(root,
                                        {
                                            "x": x,
                                            "y": y,
                                            "playerIndex": playerIndex
                                        })
            obj.dragStarted.connect(function() {
                if (root.activeMeeple !== obj)
                {
                    if (root.activeMeeple) {
                        root.activeMeeple.resetPosition()
                        if (engine.GameState === GameEngine.MeeplePlaced)
                            zones[engine.ActivePlayer].addMeeple(root.activeMeeple.type, 1)
                        root.activeMeeple = null
                    }
                }

                if (engine.GameState === GameEngine.TileFixed || root.activeMeeple !== obj)
                {
                    // the drag is from a player zone
                    zones[engine.ActivePlayer].addMeeple(obj.type, -1)
                }
                if (root.activeMeeple !== obj)
                {
                    root.activeMeeple = obj
                }
                dimmer.dimAround(engine.mapModel.LatestTile.X, engine.mapModel.LatestTile.Y)
            })
            obj.dragFinished.connect(function() {
                dimmer.undim()
                if (engine.GameState === GameEngine.TileFixed) {
                    zones[engine.ActivePlayer].addMeeple(obj.type, 1)
                }
            })
            obj.reset.connect(function() {
               zones[obj.playerIndex].addMeeple(obj.type, 1)
                root.activeMeeple = null
            })
            return obj
        }
        else {
            console.error(type, "component status:", comp.status, comp.errorString())
        }
        return null
    }

    function createMeepleItems() {
        var i
        for (var zone = 0; zone < zones.length; ++zone)
        {
            if (zones[zone].playerData)
            {
                for (i = 0; i < 8; ++i)
                {
                    meeples.push(createMeepleItem("MeepleSmall.qml",
                                              zoneColumns[zone].x + zones[zone].x + zones[zone].smallMeeplePositionX,
                                              zoneColumns[zone].y + zones[zone].y + zones[zone].smallMeeplePositionY,
                                              zone))
                }
                for (i = 0; i < 2; ++i)
                {
                    meeples.push(createMeepleItem("MeepleBig.qml",
                                              zoneColumns[zone].x + zones[zone].x + zones[zone].bigMeeplePositionX,
                                              zoneColumns[zone].y + zones[zone].y + zones[zone].bigMeeplePositionY,
                                              zone))
                }
                meeples.push(createMeepleItem("MeepleBarn.qml",
                                          zoneColumns[zone].x + zones[zone].x + zones[zone].barnPositionX,
                                          zoneColumns[zone].y + zones[zone].y + zones[zone].barnPositionY,
                                          zone))
                meeples.push(createMeepleItem("MeeplePig.qml",
                                          zoneColumns[zone].x + zones[zone].x + zones[zone].pigPositionX,
                                          zoneColumns[zone].y + zones[zone].y + zones[zone].pigPositionY,
                                          zone))
                meeples.push(createMeepleItem("MeepleBuilder.qml",
                                          zoneColumns[zone].x + zones[zone].x + zones[zone].builderPositionX,
                                          zoneColumns[zone].y + zones[zone].y + zones[zone].builderPositionY,
                                          zone))
            }
        }
    }

    Component.onCompleted: {
        tilesInDeck = engine.deck.rowCount() - 1
        for (var zone = 0; zone < zones.length; ++zone)
        {
            if (zones[zone].playerData) {
                abbeyTiles.push(createAbbeyTileItem(
                                    zoneColumns[zone].x + zones[zone].x + zones[zone].abbeyPositionX,
                                    zoneColumns[zone].y + zones[zone].y + zones[zone].abbeyPositionY,
                                    zone))
            }
        }
        board.boardRepositioned.connect(function() {
            for (var zone = 0; zone < abbeyTiles.length; ++zone)
            {
                abbeyTiles[zone].setDefaultPosition(
                            zoneColumns[zone].x + zones[zone].x + zones[zone].abbeyPositionX,
                            zoneColumns[zone].y + zones[zone].y + zones[zone].abbeyPositionY)
                if (!abbeyTiles[zone].tileData.IsFixed)
                    abbeyTiles[zone].resetPosition()
            }
        })

        createMeepleItems()
    }

    Image {
        id: background
        source: "qrc:/img/background.png"
        anchors.fill: parent
        sourceSize.width: 144
        sourceSize.height: 144
        fillMode: Image.Tile
        opacity: 0.5
        Keys.onTabPressed: {
            engine.switchActivePlayer()
            console.log("active player", engine.ActivePlayer)
        }
        Component.onCompleted: forceActiveFocus()
    }

    Board {
        id: board

        height: 760
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        width: height
        anchors.horizontalCenter: parent.horizontalCenter

        Component.onCompleted: {
            // place and fix the starting tile
            engine.mapModel.placeTile(engine.getTile(0), 0, 0)
            engine.mapModel.fixTile(engine.getTile(0))

            // create an Item for it
            tiles.push(createTileItem(board.x + board.getX(0), board.y + board.getY(0)))
        }
    }

    Dimmer {
        id: dimmer

        board: board
        z: 1
    }

    Rectangle {
        id: generalInfo

        anchors.top: parent.top
        anchors.bottom: board.top
        anchors.horizontalCenter: board.horizontalCenter
        width: board.width
        anchors.margins: 10
        color: "#DDDDDD"

        Row {
            anchors.centerIn: parent
            spacing: 20

            Column {
                id: buttonPanel

                anchors.verticalCenter: parent.verticalCenter
                spacing: 15

                MenuButton {
                    id: rotateTileButton
                    text: "Повернуть"
                    onClicked: tiles[tiles.length - 1].tileData.rotateClockwise()
                }

                MenuButton {
                    id: fixTileButton
                    text: "Поставить"
                    onClicked: {
                        engine.mapModel.fixTile(board.activeTile.tileData/*engine.getTile(tiles.length - 1)*/)
                        lastPlacedTile = board.activeTile
                        engine.updateHighlight()
                        board.activeTile.tileData.layoutChanged.disconnect(board.updateActiveTileRotation)
                        board.activeTile = null
                        engine.GameState = GameEngine.TileFixed
                    }
                }

                MenuButton {
                    id: fixMeepleButton
                    text: "Занять"
                    onClicked: {
                        lastPlacedTile.fixMeeple()
                        engine.highlight(-1)
                        root.activeMeeple = null
                        engine.GameState = GameEngine.NewTurn
                    }
                }

                MenuButton {
                    id: skipMeepleButton
                    text: "Передать ход"
                    onClicked: {
                        if (root.activeMeeple) {
                            root.activeMeeple.resetPosition()
                            if (engine.GameState === GameEngine.MeeplePlaced)
                                zones[engine.ActivePlayer].addMeeple(root.activeMeeple.type, 1)
                            root.activeMeeple = null
                        }
                        engine.highlight(-1)
                        engine.GameState = GameEngine.NewTurn
                    }
                }
            }

            Column {
                id: resourcesColumn

                anchors.verticalCenter: parent.verticalCenter
                spacing: 5

                Row {
                    spacing: 5
                    TileBonusIndicator {
                        source: "qrc:/img/barrel.png"
                        width: 32
                        height: 32
                    }
                    Text {
                        text: "x" + engine.UnassignedBarrels
                        font.pixelSize: 20
                    }
                }

                Row {
                    spacing: 5
                    TileBonusIndicator {
                        source: "qrc:/img/wheat.png"
                        width: 32
                        height: 32
                    }
                    Text {
                        text: "x" + engine.UnassignedWheat
                        font.pixelSize: 20
                    }
                }

                Row {
                    spacing: 5
                    TileBonusIndicator {
                        source: "qrc:/img/cloth.png"
                        width: 32
                        height: 32
                    }
                    Text {
                        text: "x" + engine.UnassignedCloth
                        font.pixelSize: 20
                    }
                }
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 5

                Scoreboard {
                    id: scoreboard
                }

                BinarySwitch {
                    id: tileViewSwitch

                    anchors.right: scoreboard.right
                    leftOption: "Картинки"
                    rightOption: "Схемы"
                    defaultState: Preferences.schematicView ? BinarySwitch.SwitchState.RIGHT : BinarySwitch.SwitchState.LEFT
                    onStateChanged: Preferences.schematicView = (state == BinarySwitch.SwitchState.RIGHT)
                }
            }
        }
    }

    function drawTile(zoneColumn, playerZone, playerIndex) {
        var tile = createTileItem(zoneColumn.x + playerZone.x + playerZone.regularTilePositionX,
                                  zoneColumn.y + playerZone.y + playerZone.regularTilePositionY)
        tile.playerIndex = playerIndex
        board.activeTile = tile
        tiles.push(tile)
        engine.GameState = GameEngine.TileDrawn
    }

    Column {
        id: leftPlayers

        anchors.right: board.left
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: 10
        spacing: 10

        PlayerZone {
            id: playerZoneNW

            width: parent.width
            height: (root.height - parent.spacing - 2 * parent.anchors.margins)/2
            playerIndex: 0
            visible: engine.PlayerCount > playerIndex
            tilesInDeck: playerData && playerData.IsActive ? root.tilesInDeck : Math.max(0, root.tilesInDeck - 1)
            onTileClicked: drawTile(leftPlayers, playerZoneNW, playerIndex)
        }

        PlayerZone {
            id: playerZoneSW

            width: parent.width
            height: (root.height - parent.spacing - 2 * parent.anchors.margins)/2
            playerIndex: 2
            visible: engine.PlayerCount > playerIndex
            tilesInDeck: playerData && playerData.IsActive ? root.tilesInDeck : Math.max(0, root.tilesInDeck - 1)
            onTileClicked: drawTile(leftPlayers, playerZoneSW, playerIndex)
        }
    }

    Column {
        id: rightPlayers

        anchors.left: board.right
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: 10
        spacing: 10

        PlayerZone {
            id: playerZoneNE

            width: parent.width
            height: (root.height - parent.spacing - 2 * parent.anchors.margins)/2
            playerIndex: 1
            visible: engine.PlayerCount > playerIndex
            tilesInDeck: playerData && playerData.IsActive ? root.tilesInDeck : Math.max(0, root.tilesInDeck - 1)
            onTileClicked: drawTile(rightPlayers, playerZoneNE, playerIndex)
        }

        PlayerZone {
            id: playerZoneSE

            width: parent.width
            height: (root.height - parent.spacing - 2 * parent.anchors.margins)/2
            playerIndex: 3
            visible: engine.PlayerCount > playerIndex
            tilesInDeck: playerData && playerData.IsActive ? root.tilesInDeck : Math.max(0, root.tilesInDeck - 1)
            onTileClicked: drawTile(rightPlayers, playerZoneSE, playerIndex)
        }
    }

//    Connections {
//        target: engine
//        function onGameStateChanged() {
//            console.log("engine.GameState", engine.GameState)
//        }
//    }

    Item {
        id: state

        state: engine.GameState

        states: [
            State {
                name: GameEngine.NewTurn
                PropertyChanges {
                    target: rotateTileButton
                    enabled: false
                }
                PropertyChanges {
                    target: fixTileButton
                    enabled: false
                }
                PropertyChanges {
                    target: fixMeepleButton
                    enabled: false
                }
                PropertyChanges {
                    target: skipMeepleButton
                    enabled: false
                }
            },
            State {
                name: GameEngine.TileDrawn
                PropertyChanges {
                    target: fixTileButton
                    enabled: false
                }
                PropertyChanges {
                    target: fixMeepleButton
                    enabled: false
                }
                PropertyChanges {
                    target: skipMeepleButton
                    enabled: false
                }
            },
            State {
                name: GameEngine.TilePlaced
                PropertyChanges {
                    target: fixTileButton
                    enabled: board.activeTile && board.activeTile.properlyRotated
                }
                PropertyChanges {
                    target: fixMeepleButton
                    enabled: false
                }
                PropertyChanges {
                    target: skipMeepleButton
                    enabled: false
                }
            },
            State {
                name: GameEngine.TileFixed
                PropertyChanges {
                    target: rotateTileButton
                    enabled: false
                }
                PropertyChanges {
                    target: fixTileButton
                    enabled: false
                }
                PropertyChanges {
                    target: fixMeepleButton
                    enabled: false
                }
            },
            State {
                name: GameEngine.MeeplePlaced
                PropertyChanges {
                    target: rotateTileButton
                    enabled: false
                }
                PropertyChanges {
                    target: fixTileButton
                    enabled: false
                }
            }
        ]
    }
}
