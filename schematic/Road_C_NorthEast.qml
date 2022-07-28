import QtQuick 2.15
import QtQuick.Shapes 1.12
import "qrc:/"

BaseMapObject {
    id: root

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

        PathLine {
            x: side/2 + 3 * halfRoadWidth
            y: side/2 - halfRoadWidth
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
            x: side/2 + 2 * halfRoadWidth
            y: side/2 + halfRoadWidth
        }

        PathLine {
            x: side/2 - halfRoadWidth
            y: side/2 - 2 * halfRoadWidth
        }

        PathLine {
            x: side/2 - halfRoadWidth
            y: -1
        }
    }

    idLabel.anchors.horizontalCenter: horizontalCenter
    idLabel.y: 0
}
