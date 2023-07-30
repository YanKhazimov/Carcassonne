import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQml 2.15
import QmlPresenter 1.0
import "schematic"

Item {
    id: root

    property var tiles: []
    property var abbeyTiles: []
    property var meeples: []
    property var activeMeeple: null
    readonly property var zones: [playerZoneNW, playerZoneNE, playerZoneSW, playerZoneSE]
    property int tilesInDeck
    property Item lastPlacedTile: null

    signal urlRequested(var urlAddress)

    function onLoaded() {
        initialAnimation.start()
    }

    SequentialAnimation {
        id: initialAnimation

        signal meeplesSpawned()
        signal abbeyTilesSpawned()

        NumberAnimation {
            id: slideInAnimation

            property real progressPercentage: 0.0

            duration: 1500
            from: 0.0
            to: 1.0
            target: slideInAnimation
            property: "progressPercentage"
        }

        ScriptAction {
            script: {
                initialAnimation.meeplesSpawned.connect(spawnAbbeyTiles)
                initialAnimation.abbeyTilesSpawned.connect(function() {
                    // game start
                    engine.passTurn(tiles.length)
                })

                spawnMeepleItems()
            }
        }
    }

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

    Keys.onPressed: {
        if (event.key === Qt.Key_R) {
            remainingTilesPopup.visible = !remainingTilesPopup.visible
        }
        if (event.key === Qt.Key_L) {
            gameLogPopup.visible = !gameLogPopup.visible
        }
    }

    function createTileItem(x, y, getX) {
        var comp = Qt.createComponent("Tile.qml")
        if (comp.status === Component.Ready) {
            var obj = comp.createObject(root,
                                     {
                                         "tileData": engine.getTile(tiles.length),
                                         "x": getX ? Qt.binding(getX) : x,
                                         "y": y,
                                         "board": board
                                     })
            obj.dragStarted.connect(function() {
                obj.z = 1

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
                obj.z = 0
                tilesInDeck++
                engine.GameState = GameEngine.TileDrawn
            })
            obj.dragFinished.connect(function() {
                obj.z = 0
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
                                            "playerIndex": playerIndex,
                                            "opacity": 0
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

    function spawnAbbeyTiles() {
        for (let zone = 0; zone < zones.length; ++zone)
        {
            if (zones[zone].playerData) {
                abbeyTiles.push(createAbbeyTileItem(
                                    playersSpace.x + playersColumn.x + zones[zone].x + zones[zone].abbeyPositionX,
                                    playersSpace.y + playersColumn.y + zones[zone].y + zones[zone].abbeyPositionY,
                                    zone))
            }
        }


        for (let i = 0; i < abbeyTiles.length; ++i)
            abbeyTiles[i].appeared.connect(function() {
                connectedAbbeyTiles++
                if (connectedAbbeyTiles < abbeyTiles.length)
                    abbeyTiles[connectedAbbeyTiles].appear()
                else
                    initialAnimation.abbeyTilesSpawned()
            })

        var connectedAbbeyTiles = 0
        abbeyTiles[0].appear()
    }

    function createMeepleItem(type, x, y, playerIndex) {
        var comp = Qt.createComponent(type)
        if (comp.status === Component.Ready) {
            var obj = comp.createObject(root,
                                        {
                                            "x": x,
                                            "y": y,
                                            "playerIndex": playerIndex,
                                            "opacity": 0
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

    function spawnMeepleItems() {
        const smallMeepleTotal = 8
        const bigMeepleTotal = 2
        const barnMeepleTotal = 1
        const builderMeepleTotal = 1
        const pigMeepleTotal = 1
        const meepleCountSum = smallMeepleTotal + bigMeepleTotal + barnMeepleTotal + builderMeepleTotal + pigMeepleTotal

        for (var zone = 0; zone < zones.length; ++zone)
        {
            if (zones[zone].playerData)
            {
                for (let i = 0; i < smallMeepleTotal; ++i)
                    meeples.push(createMeepleItem("MeepleSmall.qml",
                                              playersSpace.x + playersColumn.x + zones[zone].x + zones[zone].smallMeeplePositionX,
                                              playersSpace.y + playersColumn.y + zones[zone].y + zones[zone].smallMeeplePositionY,
                                              zone))

                for (let i = 0; i < bigMeepleTotal; ++i) // false positive warnings
                    meeples.push(createMeepleItem("MeepleBig.qml",
                                              playersSpace.x + playersColumn.x + zones[zone].x + zones[zone].bigMeeplePositionX,
                                              playersSpace.y + playersColumn.y + zones[zone].y + zones[zone].bigMeeplePositionY,
                                              zone))

                for (let i = 0; i < barnMeepleTotal; ++i)
                    meeples.push(createMeepleItem("MeepleBarn.qml",
                                                  playersSpace.x + playersColumn.x + zones[zone].x + zones[zone].barnPositionX,
                                                  playersSpace.y + playersColumn.y + zones[zone].y + zones[zone].barnPositionY,
                                                  zone))

                for (let i = 0; i < builderMeepleTotal; ++i)
                    meeples.push(createMeepleItem("MeepleBuilder.qml",
                                                  playersSpace.x + playersColumn.x + zones[zone].x + zones[zone].builderPositionX,
                                                  playersSpace.y + playersColumn.y + zones[zone].y + zones[zone].builderPositionY,
                                                  zone))

                for (let i = 0; i < pigMeepleTotal; ++i)
                    meeples.push(createMeepleItem("MeeplePig.qml",
                                                  playersSpace.x + playersColumn.x + zones[zone].x + zones[zone].pigPositionX,
                                                  playersSpace.y + playersColumn.y + zones[zone].y + zones[zone].pigPositionY,
                                                  zone))
            }
        }

        for (let i = 0; i < meeples.length; ++i)
            meeples[i].appeared.connect(function() {
                let playerIndex = Math.floor(connectedMeeplesCount / meepleCountSum)
                let meepleIndex = connectedMeeplesCount % meepleCountSum
                if (meepleIndex < smallMeepleTotal) {
                    zones[playerIndex].smallMeepleCount++
                }
                else {
                    meepleIndex -= smallMeepleTotal
                    if (meepleIndex < bigMeepleTotal) {
                        zones[playerIndex].bigMeepleCount++
                    }
                    else {
                        meepleIndex -= bigMeepleTotal
                        if (meepleIndex < barnMeepleTotal) {
                            zones[playerIndex].barnCount++
                        }
                        else {
                            meepleIndex -= barnMeepleTotal
                            if (meepleIndex < builderMeepleTotal) {
                                zones[playerIndex].builderCount++
                            }
                            else {
                                meepleIndex -= builderMeepleTotal
                                if (meepleIndex < pigMeepleTotal) {
                                    zones[playerIndex].pigCount++
                                }
                                else
                                    console.log("check me!")
                            }
                        }
                    }
                }

                connectedMeeplesCount++
                if (connectedMeeplesCount < meeples.length)
                    meeples[connectedMeeplesCount].appear()
                else
                    initialAnimation.meeplesSpawned()
            })

        var connectedMeeplesCount = 0
        meeples[0].appear()
    }

    function endTurn() {
        engine.highlight(-1)
        engine.passTurn(tiles.length)
    }

    Component.onCompleted: {
        tilesInDeck = engine.deck.rowCount() - 1
    }

    Image {
        id: background

        source: "qrc:/img/background.png"
        width: boardFinalPosition.x
        height: parent.height
        x: width * (-1 + slideInAnimation.progressPercentage)
        sourceSize.width: 144
        sourceSize.height: 144
        fillMode: Image.Tile
        Keys.onTabPressed: {
            engine.passTurn(tiles.length)
        }
        Component.onCompleted: forceActiveFocus()
    }

    Item {
        id: boardFinalPosition

        width: board.width
        height: board.height
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }

    Board {
        id: board

        height: 990
        width: height
        anchors.bottom: boardFinalPosition.bottom
        anchors.right: boardFinalPosition.right; anchors.rightMargin: width * (-1 + slideInAnimation.progressPercentage)

        Component.onCompleted: {
            // place and fix the starting tile
            engine.mapModel.placeTile(engine.getTile(0), 0, 0)
            engine.fixTile(engine.getTile(0))

            // create an Item for it
            let tile = createTileItem(boardFinalPosition.x + board.getX(0), boardFinalPosition.y + board.getY(0),
                                      function() {
                                          return board.x + board.getX(0)
                                      })
            tile.isInHand = false
            tiles.push(tile)
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
        height: 160
        width: boardFinalPosition.x - 2 * anchors.margins
        anchors.right: background.right
        anchors.margins: 10
        color: "#DDDDDD"

        Row {
            anchors.centerIn: parent
            spacing: 20

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
                        text: engine ? ("x" + engine.UnassignedBarrels) : ""
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
                        text: engine ? ("x" + engine.UnassignedWheat) : ""
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
                        text: engine ? ("x" + engine.UnassignedCloth) : ""
                        font.pixelSize: 20
                    }
                }
            }

            Scoreboard {
                id: scoreboard
            }

            TileViewSwitch {
            }
        }
    }

    function drawTile(zoneColumn, playerZone, playerIndex) {
        var tile = createTileItem(playersSpace.x + zoneColumn.x + playerZone.x + playerZone.regularTilePositionX,
                                  playersSpace.y + zoneColumn.y + playerZone.y + playerZone.regularTilePositionY,
                                  null)
        tile.playerIndex = playerIndex
        board.activeTile = tile
        tiles.push(tile)
        engine.GameState = GameEngine.TileDrawn
    }

    Item {
        id: playersSpace

        anchors.top: generalInfo.bottom
        anchors.bottom: parent.bottom
        anchors.margins: 10
        width: boardFinalPosition.x - 2 * anchors.margins
        anchors.right: background.right

        Column {
            id: playersColumn

            readonly property int availableHeight: root.height - generalInfo.y - generalInfo.height - 2 * 10
            anchors.verticalCenter: parent.verticalCenter
            height: childrenRect.height
            width: parent.width
            spacing: 10

            PlayerZone {
                id: playerZoneNW

                width: parent.width
                height: (playersSpace.height - parent.spacing * 3) / 4
                buttonsOffset: buttonsSpace.width + buttonsSpace.anchors.rightMargin
                playerIndex: 0
                visible: engine && engine.PlayerCount > playerIndex
                tilesInDeck: playerData && playerData.IsActive ? root.tilesInDeck : Math.max(0, root.tilesInDeck - 1)
                onTileClicked: drawTile(playersColumn, playerZoneNW, playerIndex)
            }

            PlayerZone {
                id: playerZoneNE

                width: parent.width
                height: (playersSpace.height - parent.spacing * 3) / 4
                buttonsOffset: buttonsSpace.width + buttonsSpace.anchors.rightMargin
                playerIndex: 1
                visible: engine && engine.PlayerCount > playerIndex
                tilesInDeck: playerData && playerData.IsActive ? root.tilesInDeck : Math.max(0, root.tilesInDeck - 1)
                onTileClicked: drawTile(playersColumn, playerZoneNE, playerIndex)
            }

            PlayerZone {
                id: playerZoneSW

                width: parent.width
                height: (playersSpace.height - parent.spacing * 3) / 4
                buttonsOffset: buttonsSpace.width + buttonsSpace.anchors.rightMargin
                playerIndex: 2
                visible: engine && engine.PlayerCount > playerIndex
                tilesInDeck: playerData && playerData.IsActive ? root.tilesInDeck : Math.max(0, root.tilesInDeck - 1)
                onTileClicked: drawTile(playersColumn, playerZoneSW, playerIndex)
            }

            PlayerZone {
                id: playerZoneSE

                width: parent.width
                height: (playersSpace.height - parent.spacing * 3) / 4
                buttonsOffset: buttonsSpace.width + buttonsSpace.anchors.rightMargin
                playerIndex: 3
                visible: engine && engine.PlayerCount > playerIndex
                tilesInDeck: playerData && playerData.IsActive ? root.tilesInDeck : Math.max(0, root.tilesInDeck - 1)
                onTileClicked: drawTile(playersColumn, playerZoneSE, playerIndex)
            }
        }
    }

    Item {
        id: buttonsSpace

        anchors.top: generalInfo.bottom
        anchors.bottom: parent.bottom
        width: childrenRect.width
        anchors.right: playersSpace.right
        anchors.margins: 10

        Column {
            id: buttonPanel

            visible: engine && engine.ActivePlayer !== -1
            y: engine && (engine.ActivePlayer !== -1) ?
                   playersColumn.y + zones[engine.ActivePlayer].y + zones[engine.ActivePlayer].height - 10 - height :
                   0
            Behavior on y { NumberAnimation { duration: 300 } }

            spacing: 5

            MenuButton {
                id: rotateTileButton
                text: "Повернуть"
                color: "transparent"
                onClicked: tiles[tiles.length - 1].tileData.rotateClockwise()
            }

            MenuButton {
                id: fixTileButton
                text: "Поставить"
                color: "transparent"
                onClicked: {
                    engine.fixTile(board.activeTile.tileData)
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
                color: "transparent"
                onClicked: {
                    lastPlacedTile.fixMeeple()
                    root.activeMeeple = null
                    endTurn()
                }
            }

            MenuButton {
                id: skipMeepleButton
                text: "Передать ход"
                color: "transparent"
                onClicked: {
                    if (root.activeMeeple) {
                        root.activeMeeple.resetPosition()
                        if (engine.GameState === GameEngine.MeeplePlaced)
                            zones[engine.ActivePlayer].addMeeple(root.activeMeeple.type, 1)
                        root.activeMeeple = null
                    }
                    endTurn()
                }
            }
        }
    }

    RemainingTilesPopup {
        id: remainingTilesPopup

        anchors.centerIn: parent
        width: parent.width - 200
        height: parent.height - 200
        visible: false
        modal: true
        closePolicy: Popup.CloseOnReleaseOutside | Popup.CloseOnEscape
    }

    LogPopup {
        id: gameLogPopup

        anchors.centerIn: parent
        width: parent.width - 200
        height: parent.height - 200
        visible: false
        modal: true
        closePolicy: Popup.CloseOnReleaseOutside | Popup.CloseOnEscape
    }

    Popup {
        id: gameEndPopup

        anchors.centerIn: parent
        width: 600
        height: 200
        modal: true
        closePolicy: Popup.CloseOnReleaseOutside | Popup.CloseOnEscape

        Rectangle {
            color: "lightgrey"
            anchors.fill: parent

            Column {
                anchors.centerIn: parent
                spacing: 10

                Text {
                    id: endGamePopupText

                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 25
                }

                MenuButton {
                    id: endGamePopupButton

                    property var gameState
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Ок"
                    onClicked: {
                        engine.GameState = gameState
                        gameEndPopup.close()
                    }
                }
            }
        }
    }

    Connections {
        target: engine
        function onShowMessage(message, state) {
            endGamePopupText.text = message
            endGamePopupButton.gameState = state
            gameEndPopup.visible = true
        }
    }

    Item {
        id: stateItem

        state: engine ? engine.GameState : "undefined"

        states: [
            State {
                name: GameEngine.Initialization
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
            },
            State {
                name: GameEngine.GameEnd
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
            }
        ]
    }
}
