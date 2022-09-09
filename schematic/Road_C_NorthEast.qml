import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData.C_NorthEastRoadId
    visible: tileData.C_NorthEastRoad

    ShapePath {
        startX: side/2 + halfRoadWidth
        startY: -1
        strokeColor: "darkslategrey"
        strokeWidth: 2
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : "grey"

        PathLine {
            x: side/2 + halfRoadWidth
            y: side/2 - 3 * halfRoadWidth
        }

        PathArc {
            x: side/2 + 3 * halfRoadWidth
            y: side/2 - halfRoadWidth
            radiusX: 2 * halfRoadWidth
            radiusY: 2 * halfRoadWidth
            direction: PathArc.Counterclockwise
        }

        PathLine {
            x: side + 1
            y: side/2 - halfRoadWidth
        }

        PathLine {
            x: side + 1
            y: side/2 + halfRoadWidth
        }

        PathLine {
            x: side/2 + 3 * halfRoadWidth
            y: side/2 + halfRoadWidth
        }

        PathArc {
            x: side/2 - halfRoadWidth
            y: side/2 - 3 * halfRoadWidth
            radiusX: 4 * halfRoadWidth
            radiusY: 4 * halfRoadWidth
        }

        PathLine {
            x: side/2 - halfRoadWidth
            y: -1
        }
    }

    idLabel.anchors.horizontalCenter: horizontalCenter
    idLabel.y: 0
}
