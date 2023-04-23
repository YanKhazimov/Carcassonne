import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData.Town3e4cNorthEastWestId
    visible: tileData.Town3e4cNorthEastWest

    ShapePath {
        startX: 0
        startY: width
        fillColor: strokeColor
        strokeColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.town

        PathArc {
            x: side
            y: side
            radiusX: town1eRadius
            radiusY: town1eRadius
        }

        PathLine {
            x: side
            y: 0
        }

        PathLine {
            x: 0
            y: 0
        }
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

    TileBonuses {
        mapObject: root
        primaryPoint: Qt.point(50, 20)
    }

    idLabel.x: side - idLabel.width - idLabel.width
    idLabel.y: idLabel.height
}
