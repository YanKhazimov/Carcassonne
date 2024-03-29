import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    objectData: tileData ? tileData.FieldJTrapezoidNorthWest : null

    ShapePath {
        startX: 0
        startY: side/2
        strokeColor: fillColor
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : fieldColor

        PathLine {
            x: side/2
            y: side - town1eOffset - halfRoadWidth
        }

        PathLine {
            x: side/2
            y: 0
        }

        PathLine {
            x: 0
            y: 0
        }
    }

    idLabel.x: side/4
    idLabel.y: side/4
}
