import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData.FieldArcNorthId
    visible: tileData.FieldArcNorth

    ShapePath {
        startX: side
        startY: 0
        strokeColor: fillColor
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.field

        PathArc {
            x: 0
            y: 0
            radiusX: town1eRadius
            radiusY: town1eRadius
        }
    }

    idLabel.x: side/2
    idLabel.y: 0
}
