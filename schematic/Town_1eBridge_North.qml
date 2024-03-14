import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    objectData: tileData ? tileData.Town1eBridgeNorth : null

    ShapePath {
        startX: 0
        startY: 0
        fillColor: strokeColor
        strokeColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.town

        PathArc {
            x: side/2
            y: side/2
            radiusX: side/2
            radiusY: side/2
        }

        PathArc {
            x: side
            y: 0
            radiusX: side/2
            radiusY: side/2
        }
    }

    ShapePath {
        startX: 0
        startY: 0
        fillColor: "transparent"
        strokeColor: Constants.color.schematic.townBorder
        strokeWidth: 2

        PathArc {
            x: side/2
            y: side/2
            radiusX: side/2
            radiusY: side/2
        }

        PathArc {
            x: side
            y: 0
            radiusX: side/2
            radiusY: side/2
        }
    }

    TileBonuses {
        mapObject: root
        primaryPoint: Qt.point(side/2, 30)
    }

    idLabel.anchors.horizontalCenter: horizontalCenter
    idLabel.y: 0
}
