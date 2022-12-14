import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData.FieldNorthEastId
    visible: tileData.FieldNorthEast

    ShapePath {
        startX: side
        startY: side/2
        strokeColor: fillColor
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.field

        PathLine {
            x: side/2
            y: side/2
        }

        PathLine {
            x: side/2
            y: 0
        }

        PathLine {
            x: side
            y: 0
        }
    }

    idLabel.anchors.centerIn: root
    idLabel.anchors.horizontalCenterOffset: 3 * halfRoadWidth
    idLabel.anchors.verticalCenterOffset: -3 * halfRoadWidth
}
