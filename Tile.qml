import QtQuick 2.15
import "qrc:/"
import "schematic"

Rectangle {
    id: root

    property alias tileData: mapObjects.tileData
    property bool properlyRotated: false

    required property Board board

    width: Constants.tileSize
    height: Constants.tileSize
    color: "#EEEEEE"
    clip: true

    Component.onCompleted: {
        board.boardRepositioned.connect(updateXY)
    }

    function updateXY() {
        if (tileData.IsPlaced) {
            x = board.x + board.getX(tileData.X)
            y = board.y + board.getY(tileData.Y)
        }
    }

    Connections {
        target: tileData
        function onIndexChanged() {
            updateXY()
        }
    }

    TileObjects {
        id: mapObjects
    }

    MultiObjectMouseArea {
        anchors.fill: root
        objectList: mapObjects.children
    }

    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.target: parent
        visible: !tileData.IsFixed
        cursorShape: Qt.SizeAllCursor
    }

    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: width/2
    Drag.hotSpot.y: height/2

    property alias dragActive: dragArea.drag.active
    onDragActiveChanged:
    {
        if (!dragActive)
        {
            if (Drag.target != null && Drag.target.acceptsActiveTile())
            {
                Drag.drop()
                root.properlyRotated = engine.mapModel.isAdjacent(tileData.X, tileData.Y) &&
                        engine.mapModel.canMergeAsIs(tileData.X, tileData.Y, tileData)
            }
            else
            {
                tileData.displace()
                x = 1040
                y = 20

                Drag.cancel()
                //TODO indicate an unsuccessful drag
            }
            board.activeDrag = false
        }
        else
        {
            board.activeTile = root
            board.activeDrag = true
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

    Behavior on x {
        NumberAnimation {
            duration: 200
        }
    }
    Behavior on y {
        NumberAnimation {
            duration: 200
        }
    }

//    Behavior on rotation {
//        NumberAnimation {
//            duration: 300
//        }
//    }
}
