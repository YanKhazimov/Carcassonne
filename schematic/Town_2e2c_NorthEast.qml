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
            x: side
            y: side
            radiusX: side
            radiusY: side
        }

        PathLine {
            x: side
            y: 0
        }
    }

    clip: true

    Rectangle {
        id: border

        x: -side
        y: 0
        width: 2*side
        height: 2*side
        radius: height/2
        color: "transparent"
        border.width: 2
        border.color: "brown"
    }
}
