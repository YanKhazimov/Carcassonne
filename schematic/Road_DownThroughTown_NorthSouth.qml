import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData ? tileData.RoadDownThroughTownNorthSouthId : invalidId
    visible: tileData && tileData.RoadDownThroughTownNorthSouth

    ShapePath {
        startX: side/2 + halfRoadWidth
        startY: -1
        strokeColor: Constants.color.schematic.roadBorder
        strokeWidth: 2
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.road

        PathLine {
            x: side/2 + halfRoadWidth
            y: town1eOffset
        }

        PathArc {
            x: side/2 - halfRoadWidth
            y: town1eOffset
            radiusX: halfRoadWidth
            radiusY: halfRoadWidth
        }

        PathLine {
            x: side/2 - halfRoadWidth
            y: -1
        }
    }

    ShapePath {
        startX: side/2 - halfRoadWidth
        startY: side + 1
        strokeColor: Constants.color.schematic.roadBorder
        strokeWidth: 2
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.road

        PathLine {
            x: side/2 - halfRoadWidth
            y: side/2
        }

        PathArc {
            x: side/2 + halfRoadWidth
            y: side/2
            radiusX: halfRoadWidth
            radiusY: halfRoadWidth
        }

        PathLine {
            x: side/2 + halfRoadWidth
            y: side + 1
        }
    }

    Rectangle {
        width: 2 * halfRoadWidth + 8
        height: 2 * halfRoadWidth + 8
        radius: width/2
        y: town1eOffset - height/2
        x: side/2 - width/2
        z: -1
        color: "black"
    }

    Rectangle {
        width: 2 * halfRoadWidth + 8
        height: 2 * halfRoadWidth + 8
        radius: width/2
        anchors.centerIn: parent
        z: -1
        color: "black"
    }

    idLabel.anchors.horizontalCenter: horizontalCenter
    idLabel.y: 0
}
