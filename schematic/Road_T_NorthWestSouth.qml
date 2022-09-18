import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData.T_NorthWestSouthRoadId
    visible: tileData.T_NorthWestSouthRoad

    ShapePath {
        startX: side/2 + halfRoadWidth
        startY: -1
        strokeColor: Constants.color.schematic.roadBorder
        strokeWidth: 2
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.road

        PathLine {
            x: side/2 + halfRoadWidth
            y: side + 1
        }

        PathLine {
            x: side/2 - halfRoadWidth
            y: side + 1
        }

        PathLine {
            x: side/2 - halfRoadWidth
            y: side/2 + halfRoadWidth
        }

        PathLine {
            x: -1
            y: side/2 + halfRoadWidth
        }

        PathLine {
            x: -1
            y: side/2 - halfRoadWidth
        }

        PathLine {
            x: side/2 - halfRoadWidth
            y: side/2 - halfRoadWidth
        }

        PathLine {
            x: side/2 - halfRoadWidth
            y: -1
        }
    }

    idLabel.anchors.horizontalCenter: horizontalCenter
    idLabel.y: 0
}
