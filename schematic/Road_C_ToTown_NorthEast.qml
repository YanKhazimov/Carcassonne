import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData.C_ToTown_NorthEastRoadId
    visible: tileData.C_ToTown_NorthEastRoad

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
            x: side - town1eOffset + 1
            y: side/2 - halfRoadWidth
        }

        PathLine {
            x: side - town1eOffset + 1
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
