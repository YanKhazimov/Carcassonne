import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQml 2.15
import QmlPresenter 1.0
import QtGraphicalEffects 1.15
import QtQuick.Window 2.15
import EngineEnums 1.0
import "schematic"

Item {
    id: root

    property var regularTiles: []
    property var abbeyTiles: []
    property var meeples: []
    property var activeMeeple: null
    readonly property var zones: [playerZone0, playerZone1, playerZone2, playerZone3]
    property int tilesInDeck
    property Item lastPlacedTile: null
    property var scoresByTile: ({})
    property var lastKeyPressed
    readonly property bool isLoading: pauseAnimation.running || unpauseAnimation.running || initialAnimation.running

    function onNewGameLoaded() {
        createOpenRegularTileItems()
        initialAnimation.start()
    }

    function onOldGameLoaded() {
        board.resetViewport()
        createOpenRegularTileItems()
        createAbbeyTileItems()
        createMeepleItems()
        unpauseGame()
    }

    function tryPauseGame() {
        if (engine.GameState !== GameEngine.Initialization && internal.gameViewLoadProgress === 1.0) {
            engine.getPlayer(engine.ActivePlayer).setTimerRunning(false)
            pauseAnimation.start()
        }
    }

    function unpauseGame() {
        engine.getPlayer(engine.ActivePlayer).setTimerRunning(true)
        unpauseAnimation.start()
    }

    function createOpenRegularTileItems() {
        regularTiles = []
        // create refular tile Items
        for (let i = 0; i < engine.deck.rowCount(); ++i)
        {
            let tile = engine.getTile(i)
            if (tile.IsPlaced) {
                let tileItem = createRegularTileItem(boardFinalPosition.x + board.getX(tile.X),
                                                     boardFinalPosition.y + board.getY(tile.Y),
                                                     false)
                regularTiles.push(tileItem)
            }
            else {
                if (engine.GameState == GameEngine.TileDrawn)
                {
                    let globalPosition = common.animatedPosition
                    globalPosition.x += boardFinalPosition.x

                    let tileItem = createRegularTileItem(globalPosition.x,
                                                         globalPosition.y,
                                                         true)
                    regularTiles.push(tileItem)
                    console.log("TileDrawn " + i)
                }
                break
            }
        }
    }

    function createAbbeyTileItems() {
        abbeyTiles = []
        // create abbey tile Items
        for (let j = 0; j < engine.Players.rowCount(); ++j) {
            let abbeyTile = engine.getAbbeyTile(j)

            let globalPosition
            if (!abbeyTile.IsPlaced) {
                let positionInZone = zones[j].getAbbeyTilePosition()
                globalPosition = zones[j].mapToItem(screenAdapter, positionInZone)
                globalPosition.x += boardFinalPosition.x
            }
            else {
                globalPosition = Qt.point(boardFinalPosition.x + board.getX(abbeyTile.X),
                                          boardFinalPosition.y + board.getY(abbeyTile.Y))
            }

            let tileItem = createAbbeyTileItem(globalPosition, j, false)
            abbeyTiles.push(tileItem)
        }

        // lastPlacedTile = engine.mapModel.LatestTile
    }

    function createMeepleItems() {
        meeples = []

        let freeMeeples = []
        let i
        for (i = 0; i < engine.Players.rowCount(); ++i) {
            freeMeeples.push([0, // MeepleNone
                              Constants.smallMeepleTotal,
                              Constants.bigMeepleTotal,
                              Constants.barnTotal,
                              Constants.builderTotal,
                              Constants.pigTotal
                             ])
        }

        // create meeple Items for placed meeples
        let activeMeeples = engine.activeMeeples()
        for (i = 0; i < activeMeeples.length; ++i) {
            let meepleData = activeMeeples[i]
            let position = Qt.point(boardFinalPosition.x + board.getX(meepleData.TileX) + Constants.tileSize * meepleData.TileXRatio,
                                    boardFinalPosition.y + board.getY(meepleData.TileY) + Constants.tileSize * meepleData.TileYRatio)
            let meeple = createMeepleItem(meepleData.MeepleType, position, meepleData.PlayerIndex, false, false)
            meeple.x -= meeple.width/2
            meeple.y -= meeple.height/2
            meeples.push(meeple)

            freeMeeples[meepleData.PlayerIndex][meepleData.MeepleType]--
        }

        // create meeple Items for free meeples
        for (let playerIndex = 0; playerIndex < freeMeeples.length; ++playerIndex) {
            for (let meepleType = EngineEnums.MeepleSmall; meepleType < freeMeeples[playerIndex].length; ++meepleType) {
                let count = freeMeeples[playerIndex][meepleType]
                for (i = 0; i < count; ++i) {
                    let positionInZone = zones[playerIndex].getMeeplePosition(meepleType)
                    let globalPosition = zones[playerIndex].mapToItem(screenAdapter, positionInZone)
                    globalPosition.x += boardFinalPosition.x
                    meeples.push(createMeepleItem(meepleType, globalPosition, playerIndex, false, true))
                }
                zones[playerIndex].addMeeple(meepleType, count)
            }
        }
    }

    width: Screen.width
    height: Screen.height

    Keys.onPressed: {
        if (lastKeyPressed !== event.key) {
            lastKeyPressed = event.key

            if (event.key === Qt.Key_G) {
                Preferences.greyoutView = !Preferences.greyoutView
            }
            if (event.key === Qt.Key_Tab) {
                engine.passTurn(regularTiles.length)
            }
            if (event.key === Qt.Key_S) {
                Preferences.schematicView = !Preferences.schematicView
            }
            if (event.key === Qt.Key_Escape) {
                tryPauseGame()
            }
        }
    }

    Keys.onReleased: {
        lastKeyPressed = undefined
    }

    Component.onCompleted: {
        tilesInDeck = engine.deck.rowCount() - 1
        forceActiveFocus()
    }

    Connections {
        target: engine
        function onShowMessage(message, state) {
            endGamePopupText.text = message
            endGamePopupButton.gameState = state
            gameEndPopup.visible = true
        }

        // function onGameObjectsLoaded() {
        //     resetTileItems()
        //     initialAnimation.start()
        // }
    }

    QtObject {
        id: internal

        property real gameViewLoadProgress: 0.0
    }

    NumberAnimation {
        id: pauseAnimation

        duration: 500
        from: 1.0
        to: 0.0
        target: internal
        property: "gameViewLoadProgress"
    }

    NumberAnimation {
        id: unpauseAnimation

        duration: 1500//500
        from: slideInAnimation.from
        to: slideInAnimation.to
        target: slideInAnimation.target
        property: slideInAnimation.property
    }

    SequentialAnimation {
        id: initialAnimation

        signal meeplesSpawned()
        signal abbeyTilesSpawned()

        NumberAnimation {
            id: slideInAnimation

            duration: 1500
            from: 0.0
            to: 1.0
            target: internal
            property: "gameViewLoadProgress"
        }

        ScriptAction {
            script: {
                initialAnimation.meeplesSpawned.connect(spawnAbbeyTiles)
                initialAnimation.abbeyTilesSpawned.connect(function() {
                    // game start
                    engine.passTurn(regularTiles.length)
                })

                spawnMeepleItems()
            }
        }
    }

    Binding {
        target: Constants.color.schematic
        property: "highlighter"
        value: (lastPlacedTile && lastPlacedTile.acceptsActiveMeeple) ? Constants.color.schematic.highlighterRight : Constants.color.schematic.highlighterWrong
        when: lastPlacedTile && activeMeeple && activeMeeple.dragActive
        restoreMode: Binding.RestoreBindingOrValue
    }

    function createRegularTileItem(x, y, inHand) {
        var comp = Qt.createComponent("Tile.qml")
        if (comp.status === Component.Ready) {
            var obj = comp.createObject(screenAdapter,
                                     {
                                            "tileData": engine.getTile(regularTiles.length),
                                            "x": x,
                                            "y": y,
                                            "isInHand": inHand,
                                            "gameView": Qt.binding(isGameView),
                                            "board": board,
                                            "tabs": menuTabs
                                     })

            if (engine.ActivePlayer !== -1 && abbeyTiles[engine.ActivePlayer] !== undefined &&
                    abbeyTiles[engine.ActivePlayer].tileData.IsPlaced && !abbeyTiles[engine.ActivePlayer].tileData.IsFixed)
            {
                abbeyTiles[engine.ActivePlayer].tileData.displace()
                abbeyTiles[engine.ActivePlayer].resetPosition()
                abbeyTiles[engine.ActivePlayer].z = 0
                engine.GameState = GameEngine.NewTurn // GameEngine.TileDrawn ?
            }

            obj.dragStarted.connect(function() {
                obj.z = 1
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

    function isGameView() {
        return internal.gameViewLoadProgress === 1.0
    }

    function createAbbeyTileItem(position, playerIndex, animate) {
        var comp = Qt.createComponent("Tile.qml")
        if (comp.status === Component.Ready) {
            var obj = comp.createObject(screenAdapter,
                                        {
                                            "tileData": engine.getAbbeyTile(playerIndex),
                                            "x": position.x,
                                            "y": position.y,
                                            "isInHand": !engine.getAbbeyTile(playerIndex).IsPlaced,
                                            "board": board,
                                            "playerIndex": playerIndex,
                                            "opacity": animate ? 0 : 1,
                                            "gameView": Qt.binding(isGameView),
                                            "tabs": menuTabs
                                        })
            obj.dragStarted.connect(function() {
                obj.z = 1
                if (regularTiles[regularTiles.length - 1].tileData.IsPlaced &&
                        !regularTiles[regularTiles.length - 1].tileData.IsFixed) {
                    regularTiles[regularTiles.length - 1].tileData.displace()
                    regularTiles[regularTiles.length - 1].resetPosition()
                    tilesInDeck++
                    engine.GameState = GameEngine.TileDrawn
                }
            })
            obj.dragCancelled.connect(function() {
                obj.z = 0
                engine.GameState = engine.deck.rowCount() - regularTiles.length === tilesInDeck ?
                            GameEngine.NewTurn : GameEngine.TileDrawn
            })
            // not setting z=0 on dragFinished for abbey tiles so that their active element indicator
            // could be visible above regular tiles until they are either fixed or reset
            return obj
        }
        console.error("Abbey tile component status:", comp.status, comp.errorString())
        return null
    }

    function spawnAbbeyTiles() {
        for (let zone = 0; zone < zones.length; ++zone)
        {
            if (zones[zone].playerData) {
                let positionInZone = zones[zone].getAbbeyTilePosition()
                let globalPosition = zones[zone].mapToItem(screenAdapter, positionInZone)
                abbeyTiles.push(createAbbeyTileItem(globalPosition, zone, true))
            }
        }

        var connectedAbbeyTiles = 0
        for (let i = 0; i < abbeyTiles.length; ++i)
            abbeyTiles[i].appeared.connect(function() {
                connectedAbbeyTiles++
                if (connectedAbbeyTiles < abbeyTiles.length)
                    abbeyTiles[connectedAbbeyTiles].appear()
                else
                    initialAnimation.abbeyTilesSpawned()
            })

        abbeyTiles[0].appear()
    }

    function createMeepleItem(type, position, playerIndex, animate, inHand) {
        let qmls = [ "", "MeepleSmall.qml", "MeepleBig.qml", "MeepleBarn.qml", "MeepleBuilder.qml", "MeeplePig.qml" ]
        let comp = Qt.createComponent(qmls[type])
        if (comp.status === Component.Ready) {
            var obj = comp.createObject(screenAdapter,
                                        {
                                            "x": position.x,
                                            "y": position.y,
                                            "playerIndex": playerIndex,
                                            "opacity": animate ? 0 : 1,
                                            "isInHand": inHand,
                                            "gameView": Qt.binding(isGameView),
                                            "tabs": menuTabs,
                                            "board": board
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
        for (let zone = 0; zone < zones.length; ++zone)
        {
            if (zones[zone].playerData)
            {
                let i
                // in the order of the layout
                for (i = 0; i < Constants.smallMeepleTotal; ++i) {
                    let positionInZone = zones[zone].getMeeplePosition(EngineEnums.MeepleSmall)
                    let globalPosition = zones[zone].mapToItem(screenAdapter, positionInZone)
                    meeples.push(createMeepleItem(EngineEnums.MeepleSmall, globalPosition, zone, true, true))
                }

                for (i = 0; i < Constants.bigMeepleTotal; ++i) {
                    let positionInZone = zones[zone].getMeeplePosition(EngineEnums.MeepleBig)
                    let globalPosition = zones[zone].mapToItem(screenAdapter, positionInZone)
                    meeples.push(createMeepleItem(EngineEnums.MeepleBig, globalPosition, zone, true, true))
                }

                for (i = 0; i < Constants.builderTotal; ++i) {
                    let positionInZone = zones[zone].getMeeplePosition(EngineEnums.MeepleBuilder)
                    let globalPosition = zones[zone].mapToItem(screenAdapter, positionInZone)
                    meeples.push(createMeepleItem(EngineEnums.MeepleBuilder, globalPosition, zone, true, true))
                }

                for (i = 0; i < Constants.pigTotal; ++i) {
                    let positionInZone = zones[zone].getMeeplePosition(EngineEnums.MeeplePig)
                    let globalPosition = zones[zone].mapToItem(screenAdapter, positionInZone)
                    meeples.push(createMeepleItem(EngineEnums.MeeplePig, globalPosition, zone, true, true))
                }

                for (i = 0; i < Constants.barnTotal; ++i) {
                    let positionInZone = zones[zone].getMeeplePosition(EngineEnums.MeepleBarn)
                    let globalPosition = zones[zone].mapToItem(screenAdapter, positionInZone)
                    meeples.push(createMeepleItem(EngineEnums.MeepleBarn, globalPosition, zone, true, true))
                }
            }
        }

        const meepleCountSum = Constants.smallMeepleTotal + Constants.bigMeepleTotal + Constants.barnTotal + Constants.builderTotal + Constants.pigTotal

        var connectedMeeplesCount = 0
        for (let i = 0; i < meeples.length; ++i)
            meeples[i].appeared.connect(function() {
                let playerIndex = Math.floor(connectedMeeplesCount / meepleCountSum)
                let meepleIndex = connectedMeeplesCount % meepleCountSum
                if (meepleIndex < Constants.smallMeepleTotal) {
                    zones[playerIndex].smallMeepleCount++
                }
                else {
                    meepleIndex -= Constants.smallMeepleTotal
                    if (meepleIndex < Constants.bigMeepleTotal) {
                        zones[playerIndex].bigMeepleCount++
                    }
                    else {
                        meepleIndex -= Constants.bigMeepleTotal
                        if (meepleIndex < Constants.builderTotal) {
                            zones[playerIndex].builderCount++
                        }
                        else {
                            meepleIndex -= Constants.builderTotal
                            if (meepleIndex < Constants.pigTotal) {
                                zones[playerIndex].pigCount++
                            }
                            else {
                                meepleIndex -= Constants.pigTotal
                                if (meepleIndex < Constants.barnTotal) {
                                    zones[playerIndex].barnCount++
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

        meeples[0].appear()
    }

    function drawTile() {
        let globalPosition = common.mapToItem(screenAdapter, regularTilePlaceholder.x, regularTilePlaceholder.y)
        var tile = createRegularTileItem(globalPosition.x, globalPosition.y, true)
        tile.playerIndex = engine.ActivePlayer
        board.activeTile = tile
        regularTiles.push(tile)
        engine.GameState = GameEngine.TileDrawn
    }

    function endTurn() {
        engine.highlight(-1)
        engine.passTurn(regularTiles.length)
    }

    Rectangle {
        id: backgroundLeft

        color: "black"
        width: boardFinalPosition.x * Constants.screenScale
        height: parent.height
        x: width * (-1 + internal.gameViewLoadProgress)

        Image {
            opacity: 0.3
            source: "qrc:/img/background.png"
            sourceSize.width: 144
            sourceSize.height: 144
            anchors.fill: parent
            fillMode: Image.Tile
        }
    }

    Rectangle {
        id: backgroundRight

        color: "black"
        x: board.x * Constants.screenScale
        height: parent.height
        width: board.width * Constants.screenScale

        Image {
            opacity: 0.3
            source: "qrc:/img/background.png"
            sourceSize.width: 144
            sourceSize.height: 144
            anchors.fill: parent
            fillMode: Image.Tile
        }
    }

    ScreenAdapter {
        id: screenAdapter

        width: 1920
        height: 1080
        anchors.centerIn: parent

        Item {
            id: boardFinalPosition

            width: board.width
            height: board.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
        }

        Board {
            id: board

            height: 990
            width: height
            y: boardFinalPosition.y
            anchors.right: boardFinalPosition.right; anchors.rightMargin: width * (-1 + internal.gameViewLoadProgress)

            // Component.onCompleted: {
            //     // place and fix the starting tile
            //     engine.mapModel.placeTile(engine.getTile(0), 0, 0)
            //     engine.fixTile(engine.getTile(0))

            //     // create an Item for it
            //     let tile = createTileItem(boardFinalPosition.x + board.getX(0), boardFinalPosition.y + board.getY(0))
            //     tile.isInHand = false
            //     regularTiles.push(tile)
            // }

            Connections {
                target: engine
                function onPointsScored(points, playerColor, tile) {
                    let scoreComponent = Qt.createComponent("HFadeawayText.qml")
                    if (scoreComponent.status === Component.Ready) {
                        if (tile in scoresByTile) {
                            scoresByTile[tile]++
                        }
                        else {
                            scoresByTile[tile] = 0
                        }

                        let coeff = tile.Y > 0 ? -100 : 100
                        let startPos = board.mapToItem(root,
                                                       board.getX(tile.X),
                                                       board.getY(tile.Y) + coeff * scoresByTile[tile])
                        var obj = scoreComponent.createObject(root,
                                                              {
                                                                  "startPos": startPos,
                                                                  "hDelta": -500,
                                                                  "opacity": 1.0,
                                                                  "color": playerColor,
                                                                  "text": "+" + points,
                                                                  "z": 1,
                                                                  "font.pixelSize": 100,
                                                                  "font.family": Fonts.funny
                                                              })
                        obj.run()
                    }
                    else {
                        console.error("AnimatedScore component status:", scoreComponent.status, scoreComponent.errorString())
                    }
                }
            }
        }

        Dimmer {
            id: dimmer

            board: board
            z: 1
        }

        Row {
            anchors.horizontalCenter: board.horizontalCenter
            anchors.bottom: board.top
            anchors.top: parent.top
            spacing: 50

            MenuButton {
                color: root.lastKeyPressed === Qt.Key_Escape ? "grey" : "white"
                hotkeyText: "Esc"
                text: "Меню"
                activeIndicator: false
                onClicked: tryPauseGame()
            }

            MenuButton {
                color: root.lastKeyPressed === Qt.Key_G ? "grey" : "white"
                hotkeyText: "G"
                text: "Ч/б"
                activeIndicator: false
                onClicked: Preferences.greyoutView = !Preferences.greyoutView
            }

            MenuButton {
                color: root.lastKeyPressed === Qt.Key_S ? "grey" : "white"
                hotkeyText: "S"
                text: "Схемы"
                activeIndicator: false
                onClicked: Preferences.schematicView = !Preferences.schematicView
            }
        }

        MenuTabs {
            id: menuTabs

            x: width * (-1 + internal.gameViewLoadProgress)
            width: boardFinalPosition.x
            anchors.top: scoreboardSpace.bottom; anchors.topMargin: 20
        }

        Item {
            id: tabsSpace

            width: boardFinalPosition.x
            x: width * (-1 + internal.gameViewLoadProgress)
            anchors.top: menuTabs.bottom
            anchors.bottom: board.bottom

            LinearGradient {
                anchors.fill: parent
                start: Qt.point(width/2, 0)
                end: Qt.point(width/2, height)

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#bb000000" }
                    GradientStop { position: 1.0; color: "transparent" }
                }
            }

            RemainingContent {
                anchors.fill: parent
                visible: menuTabs.activeTab === 1
            }

            GameLog {
                anchors.fill: parent
                visible: menuTabs.activeTab === 2

                onHighlightedTileChanged: {
                    if (highlightedTile)
                        dimmer.dimAround(highlightedTile.X, highlightedTile.Y)
                    else
                        dimmer.undim()
                }
            }

            Image {
                visible: menuTabs.activeTab === 0
                width: parent.width
                height: sourceSize.height
                source: "qrc:/img/pattern.png"
                fillMode: Image.TileHorizontally
            }

            Row {
                id: playersRow

                visible: menuTabs.activeTab === 0
                anchors.horizontalCenter: parent.horizontalCenter
                height: parent.height
                width: childrenRect.width
                spacing: 10

                PlayerZone {
                    id: playerZone0

                    height: parent.height
                    playerIndex: 0
                    visible: engine && engine.PlayerCount > playerIndex
                }

                PlayerZone {
                    id: playerZone1

                    height: parent.height
                    playerIndex: 1
                    visible: engine && engine.PlayerCount > playerIndex
                }

                PlayerZone {
                    id: playerZone2

                    height: parent.height
                    playerIndex: 2
                    visible: engine && engine.PlayerCount > playerIndex
                }

                PlayerZone {
                    id: playerZone3

                    height: parent.height
                    playerIndex: 3
                    visible: engine && engine.PlayerCount > playerIndex
                }
            }
        }

        Column {
            id: common

            // startPosition has to depend on internal.gameViewLoadProgress to send update calls to mapToItem
            readonly property point position: engine && engine.ActivePlayer !== -1 && internal.gameViewLoadProgress > 0.0 ?
                                                            zones[engine.ActivePlayer].mapToItem(screenAdapter,
                                                                                                 zones[engine.ActivePlayer].width/2 - width/2,
                                                                                                 zones[engine.ActivePlayer].bannerEnd) :
                                                       Qt.point(-width, 0)

            spacing: 10
            visible: engine && engine.ActivePlayer !== -1 && zones[engine.ActivePlayer].ready && menuTabs.activeTab === 0
            x: position.x
            y: position.y

            Row {
                id: regularTilePlaceholder

                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10

                Rectangle {
                    width: Constants.tilePreviewSize
                    height: Constants.tilePreviewSize
                    color: "transparent"
                    border.width: 2
                    border.color: "grey"

                    Image {
                        anchors.centerIn: parent
                        source: "qrc:/img/x_icon.png"
                    }

                    Image {
                        id: tileBack

                        source: "qrc:/img/tileBack.png"
                        anchors.fill: parent
                        visible: tilesInDeck > 0

                        Rectangle {
                            id: border

                            anchors.fill: parent
                            color: "transparent"
                            border.width: 2
                            border.color: "black"
                        }
                    }

                    MouseArea {
                        id: deckBackMouseArea
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        visible: engine && tilesInDeck > 0 && !engine.AllFttingTilesPlayed &&
                                 (engine.GameState === GameEngine.NewTurn ||
                                  engine.GameState === GameEngine.TilePlaced &&
                                  engine.getAbbeyTile(engine.ActivePlayer).IsPlaced &&
                                  !engine.getAbbeyTile(engine.ActivePlayer).IsFixed)
                        onClicked: drawTile()
                    }

                    ElementActionIndicator {
                        target: parent
                        visible: deckBackMouseArea.visible
                    }
                }

                MyText {
                    id: tilesLeft

                    anchors.verticalCenter: regularTilePlaceholder.verticalCenter
                    text: "x" + tilesInDeck
                    font.pixelSize: 20
                    color: "white"
                }
            }

            MenuButton {
                id: rotateTileButton
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Повернуть"
                font.family: Fonts.font4
                onClicked: regularTiles[regularTiles.length - 1].tileData.rotateClockwise()
            }

            MenuButton {
                id: fixTileButton
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Поставить"
                font.family: Fonts.font4
                onClicked: {
                    engine.fixTile(board.activeTile.tileData)
                    lastPlacedTile = board.activeTile
                    if (board.activeTile.tileData.Abbey) {
                        board.activeTile.z = 0
                    }
                    engine.updateHighlight()
                    board.activeTile.tileData.layoutChanged.disconnect(board.updateActiveTileRotation)
                    board.activeTile = null
                    engine.GameState = GameEngine.TileFixed
                }
            }

            MenuButton {
                id: fixMeepleButton
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Занять"
                font.family: Fonts.font4
                onClicked: {
                    lastPlacedTile.fixMeeple()
                    root.activeMeeple = null
                    endTurn()
                }
            }

            MenuButton {
                id: skipMeepleButton
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Передать ход"
                font.family: Fonts.font4
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

        Item {
            id: scoreboardSpace

            anchors.top: parent.top; anchors.topMargin: 10
            height: 160
            width: boardFinalPosition.x - 2 * 10
            x: width * (-1 + internal.gameViewLoadProgress) + 10

            Scoreboard {
                anchors.centerIn: parent
            }
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
                    target: rotateTileButton
                    enabled: board.activeTile && !board.activeTile.tileData.Abbey
                }
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
