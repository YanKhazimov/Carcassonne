import QtQuick 2.15
import QmlPresenter 1.0
import EngineEnums 1.0
import "qrc:/"
import "schematic"

Item {
    id: root

    property alias tileData: mapObjects.tileData
    property bool properlyRotated: false
    property BaseMeeple meeple

    required property Board board
    property int playerIndex: -1

    width: Constants.tileSize
    height: Constants.tileSize

    QtObject {
        id: internal

        property int defaultX
        property int defaultY

        Component.onCompleted: {
            setDefaultPosition(root.x, root.y)
        }
    }

    Component.onCompleted: {
        board.boardRepositioned.connect(updateXY)
        meeple = null
    }

    function setDefaultPosition(newX, newY) {
        internal.defaultX = newX
        internal.defaultY = newY
    }

    function resetPosition() {
        x = internal.defaultX
        y = internal.defaultY
    }

    function updateXY() {
        if (tileData.IsPlaced) {
            var targetX = board.x + board.getX(tileData.X)
            var targetY = board.y + board.getY(tileData.Y)

            root.x = targetX
            root.y = targetY

            if (meeple) {
                // have to take target coords instead of root coords which are mid-animation
                meeple.x = targetX + Constants.tileSize * meeple.xRatio - meeple.width/2
                meeple.y = targetY + Constants.tileSize * meeple.yRatio - meeple.height/2
            }
        }
    }

    function fixMeeple() {
        if (meeple) {
            meeple.xRatio = (meeple.x + meeple.width/2 - root.x) / Constants.tileSize
            meeple.yRatio = (meeple.y + meeple.height/2 - root.y) / Constants.tileSize
            meeple.draggable = false

            engine.placeMeeple(meeple.type, meeple.playerIndex, dropArea.meepleObjectId, tileData)
        }
    }

    function resetMeeple() {
        if (meeple) {
            meeple.resetPosition()
            meeple.reset()
            meeple.draggable = true
            meeple = null
        }
    }

    Connections {
        target: tileData
        function onIndexChanged() {
            updateXY()
        }
        function onMeepleReset() {
            resetMeeple()
        }
    }

    TileObjects {
        id: mapObjects
        anchors.fill: picture
        visible: !rotationAnimation.running
    }

    MultiObjectMouseArea {
        id: objectsArea
        anchors.fill: root
        objectList: mapObjects.children
        visible: tileData.IsPlaced
    }

    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.target: parent
        visible: (!tileData.IsFixed) && (playerIndex === engine.ActivePlayer) && (!tileData.Abbey ||
                                                                              engine.GameState < GameEngine.TileFixed)
        cursorShape: Qt.SizeAllCursor
    }

    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: width/2
    Drag.hotSpot.y: height/2
    Drag.keys: ["tile"]

    signal dragStarted()
    signal dragFinished()
    signal dragCancelled()

    property alias dragActive: dragArea.drag.active
    onDragActiveChanged:
    {
        //console.log("dragActive", dragActive)
        if (!dragActive)
        {
//            console.log("Drag.target", Drag.target)
//            if (Drag.target)
//                console.log("accepts", Drag.target.acceptsActiveTile())
            if (Drag.target != null && Drag.target.acceptsActiveTile())
            {
                Drag.drop()
                root.properlyRotated = engine.mapModel.isFreeAdjacent(tileData.X, tileData.Y) &&
                        engine.mapModel.canMergeAsIs(tileData.X, tileData.Y, tileData)
            }
            else
            {
                tileData.displace()
                resetPosition()

                dragCancelled()

                Drag.cancel()
                //TODO indicate an unsuccessful drag
            }
            board.activeDrag = false

            dragFinished()
        }
        else
        {
            board.activeTile = root
            board.activeDrag = true

            dragStarted()
        }
    }

    DropArea {
        id: dropArea

        property var meepleObjectId
        anchors.fill: parent
        keys: ["meeple"]
        enabled: engine.mapModel.LatestTile === tileData
        onPositionChanged: objectsArea.selectObjectAt(drag.x, drag.y)
        onEntered: {
            meeple = drag.source
        }
        onExited: {
            meeple = null
            engine.highlight(-1)
        }
        onDropped: {
            meepleObjectId = objectsArea.idAt(drag.x, drag.y)
        }
    }

    Image {
        id: picture

        source: tileData.Picture
        anchors.fill: parent
        rotation: tileData.ImageRotation
        opacity: 0//tileData.Abbey ? 1 : 0.8//engine.TilePictureOpacity

        Behavior on rotation {
            NumberAnimation {
                id: rotationAnimation
                duration: 300
            }
        }

        Rectangle {
            id: border

            anchors.fill: parent
            color: "transparent"
            border.width: 2
            border.color: "black"
            visible: !tileData.IsFixed
        }
    }

    Behavior on x { NumberAnimation { duration: 200 } }
    Behavior on y { NumberAnimation { duration: 200 } }

    ElementActionIndicator {
        target: parent
        visible: dragArea.visible
        rotation: picture.rotation
    }
}
