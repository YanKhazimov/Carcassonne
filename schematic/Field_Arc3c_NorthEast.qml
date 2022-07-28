import QtQuick 2.15
import QtQuick.Shapes 1.12
import "qrc:/"

BaseMapObject {
    id: root

    ShapePath {
        startX: side
        startY: 0
        fillColor: strokeColor
        strokeColor: root.highlighted ? Constants.color.schematic.highlighter : "lightgreen"

        PathLine {
            x: side
            y: side
        }

        PathArc {
            x: 0
            y: 0
            radiusX: side
            radiusY: side
        }
    }
}
