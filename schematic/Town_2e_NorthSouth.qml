import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    objectData: tileData ? tileData.Town2eNorthSouth : null

    ShapePath {
        startX: 0
        startY: 0
        fillColor: strokeColor
        strokeColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.town

        PathArc {
            x: 0
            y: side
            radiusX: town2eRadius
            radiusY: town2eRadius
        }

        PathLine {
            x: side
            y: side
        }

        PathArc {
            x: side
            y: 0
            radiusX: town2eRadius
            radiusY: town2eRadius
        }

        PathLine {
            x: 0
            y: 0
        }
    }

    Rectangle {
        id: eastBorder

        x: side - town2eOffset
        y: side / 2 - width / 2
        width: 2*town2eRadius
        height: 2*town2eRadius
        radius: height/2
        color: "transparent"
        border.width: 2
        border.color: Constants.color.schematic.townBorder
    }

    Rectangle {
        id: westBorder

        x: town2eOffset - 2*town2eRadius
        y: side / 2 - width / 2
        width: 2*town2eRadius
        height: 2*town2eRadius
        radius: height/2
        color: "transparent"
        border.width: 2
        border.color: Constants.color.schematic.townBorder
    }

    TileBonuses {
        mapObject: root
        primaryPoint: Qt.point(50, 20)
    }

    idLabel.anchors.horizontalCenter: horizontalCenter
    idLabel.y: 0
}
