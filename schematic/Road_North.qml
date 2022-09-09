import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    visible: tileData.RoadNorth
    currentId: tileData.RoadNorthId

    ShapePath {
        startX: side/2 + halfRoadWidth
        startY: -1
        strokeColor: "darkslategrey"
        strokeWidth: 2
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : "grey"

        PathLine {
            x: side/2 + halfRoadWidth
            y: side/4
        }

        PathArc {
            x: side/2 - halfRoadWidth
            y: side/4
            radiusX: halfRoadWidth
            radiusY: halfRoadWidth
        }

        PathLine {
            x: side/2 - halfRoadWidth
            y: -1
        }
    }

    idLabel.anchors.horizontalCenter: horizontalCenter
    idLabel.y: 0
}
