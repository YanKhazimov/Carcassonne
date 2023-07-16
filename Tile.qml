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
    readonly property bool isPreview: board == null
    property int playerIndex: -1

    readonly property alias dragActive: dragArea.drag.active
    readonly property bool acceptsActiveMeeple: dropArea.accepts

    property bool isInHand: true

    width: isPreview || isInHand ? Constants.tilePreviewSize : Constants.tileSize
    height: isPreview || isInHand ? Constants.tilePreviewSize : Constants.tileSize

    QtObject {
        id: internal

        property int defaultX
        property int defaultY

        Component.onCompleted: {
            setDefaultPosition(root.x, root.y)
        }
    }

    Component.onCompleted: {
        if (!isPreview)
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

            engine.placeMeeple(meeple.type, meeple.playerIndex, dropArea.selectedObject.currentId, tileData)
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
        enabled: !isPreview
        function onIndexChanged() {
            updateXY()
        }
        function onMeepleReset() {
            resetMeeple()
        }
    }

    TileObjects {
        id: mapObjects
        anchors.fill: parent
        visible: !rotationAnimation.running
        opacity: Preferences.schematicView ? 1 : 0
        isPreview: root.isPreview
    }

    MultiObjectMouseArea {
        id: objectsArea
        anchors.fill: root
        objectList: mapObjects.children
        visible: tileData && tileData.IsPlaced
    }

    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.target: parent
        visible: tileData && !tileData.IsFixed && engine && (playerIndex === engine.ActivePlayer) &&
                 (!tileData.Abbey || engine.GameState < GameEngine.TileDrawn)
        cursorShape: Qt.SizeAllCursor
    }

    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: width/2
    Drag.hotSpot.y: height/2
    Drag.keys: ["tile"]

    signal dragStarted()
    signal dragFinished()
    signal dragCancelled()

    onDragActiveChanged:
    {
        if (!dragActive)
        {
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
                root.isInHand = true

                dragCancelled()

                Drag.cancel()
                //TODO indicate an unsuccessful drag
            }
            board.activeDrag = false

            dragFinished()
        }
        else
        {
            root.isInHand = false
            board.activeTile = root
            board.activeDrag = true

            dragStarted()
        }
    }

    DropArea {
        id: dropArea

        property Item selectedObject
        property bool accepts

        anchors.fill: parent
        keys: ["meeple"]
        enabled: engine && (engine.mapModel.LatestTile === tileData)

        function acceptsActiveMeeple() {
            // operating meeple, selectedObject, tileData
            return selectedObject && meeple &&
                    engine.canPlaceMeeple(selectedObject.currentId, meeple.playerIndex, meeple.type, selectedObject.tileData)
        }

        function processSelectedObject(obj) {
            if (selectedObject !== obj) {
                selectedObject = obj
                meeple.rotation = (selectedObject && engine.isFieldObject(selectedObject.currentId) &&
                                   (meeple.type === EngineEnums.MeepleSmall || meeple.type === EngineEnums.MeepleBig))
                        ? 90 : 0
                accepts = acceptsActiveMeeple()
            }
            engine.highlight(selectedObject ? selectedObject.currentId : -1)
        }

        Component.onCompleted: accepts = false

        onPositionChanged: {
            processSelectedObject(objectsArea.objectAt(drag.x, drag.y))
        }
        onEntered: {
            meeple = drag.source
            processSelectedObject(objectsArea.objectAt(drag.x, drag.y))
        }
        onExited: {
            processSelectedObject(null)
            meeple = null
        }
        onDropped: {
            if (!selectedObject || selectedObject.currentId === -1) {
                resetMeeple()
            }
            engine.highlight(-1)
        }
    }

    Image {
        id: picture

        source: tileData ? tileData.Picture : ""
        anchors.fill: parent
        rotation: tileData ? tileData.ImageRotation : 0
        opacity: Preferences.schematicView ? 0 : 1//tileData.Abbey ? 1 : 0.8//engine.TilePictureOpacity

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
            visible: tileData && !tileData.IsFixed
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
