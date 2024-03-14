import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

Road_NorthSouth {
    objectData: tileData ? tileData.RoadLongNorth : null

    ShapePath {
        startX: side/2 + halfRoadWidth
        startY: -1
        strokeColor: Constants.color.schematic.roadBorder
        strokeWidth: 2
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.road

        PathLine {
            x: side/2 + halfRoadWidth
            y: side - town1eOffset
        }

        PathArc {
            x: side/2 - halfRoadWidth
            y: side - town1eOffset
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
