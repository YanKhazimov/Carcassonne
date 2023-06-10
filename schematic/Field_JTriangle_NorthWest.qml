import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData ? tileData.FieldJTriangleNorthWestId : invalidId
    visible: tileData && tileData.FieldJTriangleNorthWest

    ShapePath {
        startX: side/2
        startY: 0
        strokeColor: fillColor
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : fieldColor

        PathLine {
            x: town1eOffset + halfRoadWidth
            y: side/2
        }

        PathLine {
            x: 0
            y: 0
        }
    }

    idLabel.x: side/4
    idLabel.y: 0
}
