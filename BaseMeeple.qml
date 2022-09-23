import QtQuick 2.15
import QmlPresenter 1.0

Item {
    id: root

    z: 2

    property real xRatio
    property real yRatio
    property bool draggable
    property var type
    required property int playerIndex
    readonly property color playerColor: engine.getPlayer(playerIndex).Color

    QtObject {
        id: internal

        property int defaultX
        property int defaultY

        Component.onCompleted: {
            defaultX = root.x
            defaultY = root.y
        }
    }

    function resetPosition() {
        x = internal.defaultX
        y = internal.defaultY
    }

    Component.onCompleted: {
        draggable = true
    }

    MouseArea {
        id: dragArea

        anchors.fill: parent
        drag.target: parent
        cursorShape: Qt.SizeAllCursor
        propagateComposedEvents: true
        visible: root.draggable &&
                 (engine.GameState === GameEngine.TileFixed || engine.GameState === GameEngine.MeeplePlaced) &&
                 playerIndex === engine.ActivePlayer
    }

    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: width/2
    Drag.hotSpot.y: height/2
    Drag.keys: ["meeple"]

    property alias dragActive: dragArea.drag.active

    Behavior on x { NumberAnimation { duration: 400 } }
    Behavior on y { NumberAnimation { duration: 400 } }

    signal dragStarted()
    signal dragFinished()
    signal reset()

    onDragActiveChanged:
    {
        if (dragActive)
        {
            engine.highlight(-1)
            dragStarted()
        }
        else
        {
            if (Drag.target != null && Drag.target.acceptsActiveMeeple())
            {
                Drag.drop()
                engine.GameState = GameEngine.MeeplePlaced
                dragFinished()
            }
            else
            {
                Drag.cancel()
                engine.GameState = GameEngine.TileFixed
                resetPosition()
                dragFinished()
                //TODO indicate an unsuccessful drag
            }
        }
    }

    ElementActionIndicator {
        target: parent
        visible: dragArea.visible
    }
}
