import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData.Field3qNoNorthEastId
    visible: tileData.Field3qNoNorthEast

    ShapePath {
        startX: side
        startY: side/2
        strokeColor: fillColor
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.field

        PathLine {
            x: side
            y: side
        }

        PathLine {
            x: 0
            y: side
        }

        PathLine {
            x: 0
            y: 0
        }

        PathLine {
            x: side/2
            y: 0
        }

        PathLine {
            x: side/2
            y: side/2
        }
    }

    idLabel.x: side/2 - halfRoadWidth - idLabel.width
    idLabel.y: side/2 + halfRoadWidth
}
