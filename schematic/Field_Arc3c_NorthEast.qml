import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData ? tileData.FieldArc3cNorthEastId : invalidId
    visible: tileData && tileData.FieldArc3cNorthEast

    ShapePath {
        startX: side
        startY: 0
        fillColor: strokeColor
        strokeColor: root.highlighted ? Constants.color.schematic.highlighter : fieldColor

        PathLine {
            x: side
            y: side
        }

        PathArc {
            x: 0
            y: 0
            radiusX: side
            radiusY: side
        }
    }

    idLabel.x: side/2
    idLabel.y: side/2
}
