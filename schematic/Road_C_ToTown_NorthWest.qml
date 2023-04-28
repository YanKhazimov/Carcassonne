import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData.C_ToTown_NorthWestRoadId
    visible: tileData.C_ToTown_NorthWestRoad

    ShapePath {
        startX: side/2 - halfRoadWidth
        startY: -1
        strokeColor: Constants.color.schematic.roadBorder
        strokeWidth: 2
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.road

        PathArc {
            x: 0
            y: side/2 - halfRoadWidth
            radiusX: side/2 - halfRoadWidth
            radiusY: side/2 - halfRoadWidth
        }

        PathLine {
            x: 0
            y: side/2 + halfRoadWidth
        }

        PathArc {
            direction: PathArc.Counterclockwise
            x: side/2 + halfRoadWidth
            y: -1
            radiusX: side/2 + halfRoadWidth
            radiusY: side/2 + halfRoadWidth
        }
    }

    idLabel.anchors.horizontalCenter: horizontalCenter
    idLabel.y: 0
}
