import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    objectData: tileData ? tileData.RoadNorth : null

    ShapePath {
        startX: side/2 + halfRoadWidth
        startY: -1
        strokeColor: Constants.color.schematic.roadBorder
        strokeWidth: 2
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.road

        PathLine {
            x: side/2 + halfRoadWidth
            y: town2eOffset
        }

        PathArc {
            x: side/2 - halfRoadWidth
            y: town2eOffset
            radiusX: halfRoadWidth
            radiusY: halfRoadWidth
        }

        PathLine {
            x: side/2 - halfRoadWidth
            y: -1
        }
    }

    TileBonuses {
        mapObject: root
        primaryPoint: Qt.point(side/2 - 4 * halfRoadWidth, side/6)
    }

    idLabel.anchors.horizontalCenter: horizontalCenter
    idLabel.y: 0
}
