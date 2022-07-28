import QtQuick 2.15
import QtQuick.Shapes 1.12
import "qrc:/"

BaseMapObject {
    id: root

    ShapePath {
        startX: 0
        startY: 0
        fillColor: strokeColor
        strokeColor: root.highlighted ? Constants.color.schematic.highlighter : "chocolate"

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

        PathLine {
            x: side
            y: 0
        }
    }

    clip: true

    Rectangle {
        id: westBorder

        x: town1eOffset - 2*town1eRadius
        y: side / 2 - width / 2
        width: 2*town1eRadius
        height: 2*town1eRadius
        radius: height/2
        color: "transparent"
        border.width: 2
        border.color: "brown"
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
        border.color: "brown"
    }

    idLabel.x: side - idLabel.width - idLabel.width
    idLabel.y: idLabel.height
}
