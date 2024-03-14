import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    objectData: tileData ? tileData.Town1e4cNorth : null

    ShapePath {
        startX: 0
        startY: 0
        fillColor: strokeColor
        strokeColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.town

        PathArc {
            x: 0
            y: side
            radiusX: town1eRadius
            radiusY: town1eRadius
        }

        PathArc {
            x: side
            y: side
            radiusX: town1eRadius
            radiusY: town1eRadius
        }

        PathArc {
            x: side
            y: 0
            radiusX: town1eRadius
            radiusY: town1eRadius
        }
    }

    Rectangle {
        id: westBorder

        x: town1eOffset - 2*town1eRadius
        y: side / 2 - width / 2
        width: 2*town1eRadius
        height: 2*town1eRadius
        radius: height/2
        color: "transparent"
        border.width: 2
        border.color: Constants.color.schematic.townBorder
    }

    Rectangle {
        id: southBorder

        x: side / 2 - width / 2
        y: side -town1eOffset
        width: 2*town1eRadius
        height: 2*town1eRadius
        radius: height/2
        color: "transparent"
        border.width: 2
        border.color: Constants.color.schematic.townBorder
    }

    Rectangle {
        id: eastBorder

        x: side - town1eOffset
        y: side / 2 - width / 2
        width: 2*town1eRadius
        height: 2*town1eRadius
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
    idLabel.anchors.verticalCenter: verticalCenter
}
