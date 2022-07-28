import QtQuick 2.15
import QtQuick.Shapes 1.12
import "qrc:/"

BaseMapObject {
    id: root

    ShapePath {
        startX: side
        startY: 0
        fillColor: strokeColor
        strokeColor: root.highlighted ? Constants.color.schematic.highlighter : "chocolate"

        PathArc {
            x: 0
            y: 0
            radiusX: town1eRadius
            radiusY: town1eRadius
        }
    }

    clip: true

    Rectangle {
        id: border

        x: side/2 - width/2
        y: town1eOffset - 2*town1eRadius
        width: 2*town1eRadius + 2 // +2 for antialiasing effect
        height: 2*town1eRadius + 2 // +2 for antialiasing effect
        radius: height/2
        color: "transparent"
        border.width: 2
        border.color: "brown"
    }
}
