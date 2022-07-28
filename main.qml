import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import "schematic"

Window {
    id: root

    width: 1280
    height: 760
    visible: true
    title: qsTr("Carcassonne")
    color: "#DDDDDD"
    property var tiles: []

    function createTileItem(x, y) {
        var comp = Qt.createComponent("Tile.qml")
        if (comp.status === Component.Ready) {
            return comp.createObject(root,
                                     {
                                         "tileData": engine.getTile(tiles.length),
                                         "x": x,
                                         "y": y,
                                         "board": board
                                     })
        }
        return null
    }

    Board {
        id: board

        height: parent.height
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

    Column {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.margins: 20
        spacing: 20
/*
        MenuButton {
            text: "Slide W"
            onClicked: board.slideWest()
            //enabled: !board.maxCapacityReached
        }

        MenuButton {
            text: "Slide E"
            onClicked: board.slideEast()
            //enabled: !board.maxCapacityReached
        }

        MenuButton {
            text: "Slide N"
            onClicked: board.slideNorth()
            //enabled: !board.maxCapacityReached
        }

        MenuButton {
            text: "Slide S"
            onClicked: board.slideSouth()
            //enabled: !board.maxCapacityReached
        }

        MenuButton {
            text: "Expand NW"
            onClicked: board.expandNorthWest()
            enabled: !board.maxCapacityReached
        }

        MenuButton {
            text: "Expand NE"
            onClicked: board.expandNorthEast()
            enabled: !board.maxCapacityReached
        }

        MenuButton {
            text: "Expand SE"
            onClicked: board.expandSouthEast()
            enabled: !board.maxCapacityReached
        }

        MenuButton {
            text: "Expand SW"
            onClicked: board.expandSouthWest()
            enabled: !board.maxCapacityReached
        }
*/
        MenuButton {
            text: "По ч/с"
            enabled: board.activeTile
            onClicked: tiles[tiles.length - 1].tileData.rotateClockwise()
        }

        MenuButton {
            text: "Против ч/с"
            enabled: board.activeTile
            onClicked: tiles[tiles.length - 1].tileData.rotateCounterclockwise()
        }

        MenuButton {
            id: drawButton
            text: "Взять фишку"
            onClicked: {
                var tile = createTileItem(1040, 20)
                board.activeTile = tile
                tiles.push(tile)
                enabled = false
            }
        }

        MenuButton {
            id: fixButton
            text: "Поставить"
            enabled: board.activeTile && board.activeTile.properlyRotated
            onClicked: {
                engine.mapModel.fixTile(engine.getTile(tiles.length - 1))
                engine.updateHighlight()
                board.activeTile.tileData.layoutChanged.disconnect(board.updateActiveTileRotation)
                board.activeTile = null
                drawButton.enabled = tiles.length < engine.deck.rowCount()
            }
        }
    }
}
