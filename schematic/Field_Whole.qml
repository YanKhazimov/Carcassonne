import QtQuick 2.15
import QtQuick.Shapes 1.12
import "qrc:/"

BaseMapObject {
    id: root

    ShapePath {
        startX: side
        startY: side
        strokeColor: fillColor
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : "lightgreen"

        PathLine {
            x: 0
            y: side
        }

        PathLine {
            x: 0
            y: 0
        }

        PathLine {
            x: side
            y: 0
        }
    }
}
