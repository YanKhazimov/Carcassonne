import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: -1
    visible: tileData.RoadBlock

    ShapePath {
        startX: side/2 - 2 * halfRoadWidth
        startY: side/2 - 4 * halfRoadWidth
        fillColor: Constants.color.schematic.field
        strokeColor: Constants.color.schematic.roadBorder
        strokeWidth: 2

        PathLine {
            x: side/2 + 2 * halfRoadWidth
            y: side/2 - 4 * halfRoadWidth
        }

        PathLine {
            x: side/2 + 2 * halfRoadWidth
            y: side/2 - 2 * halfRoadWidth
        }

        PathLine {
            x: side/2 + 4 * halfRoadWidth
            y: side/2 - 2 * halfRoadWidth
        }

        PathLine {
            x: side/2 + 4 * halfRoadWidth
            y: side/2 + 2 * halfRoadWidth
        }

        PathLine {
            x: side/2 + 2 * halfRoadWidth
            y: side/2 + 2 * halfRoadWidth
        }

        PathLine {
            x: side/2 + 2 * halfRoadWidth
            y: side/2 + 4 * halfRoadWidth
        }

        PathLine {
            x: side/2 - 2 * halfRoadWidth
            y: side/2 + 4 * halfRoadWidth
        }

        PathLine {
            x: side/2 - 2 * halfRoadWidth
            y: side/2 + 2 * halfRoadWidth
        }

        PathLine {
            x: side/2 - 4 * halfRoadWidth
            y: side/2 + 2 * halfRoadWidth
        }

        PathLine {
            x: side/2 - 4 * halfRoadWidth
            y: side/2 - 2 * halfRoadWidth
        }

        PathLine {
            x: side/2 - 2 * halfRoadWidth
            y: side/2 - 2 * halfRoadWidth
        }

        PathLine {
            x: side/2 - 2 * halfRoadWidth
            y: side/2 - 4 * halfRoadWidth
        }
    }

    idLabel.anchors.horizontalCenter: horizontalCenter
    idLabel.anchors.verticalCenter: verticalCenter
}
