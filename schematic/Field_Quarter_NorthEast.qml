import QtQuick 2.15
import QtQuick.Shapes 1.12
import "qrc:/"

BaseMapObject {
    id: root

    ShapePath {
        startX: side
        startY: side/2
        strokeColor: fillColor
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : "lightgreen"

        PathLine {
            x: side/2
            y: side/2
        }

        PathLine {
            x: side/2
            y: 0
        }

        PathLine {
            x: side
            y: 0
        }
    }

    idLabel.x: side*3/4
    idLabel.y: side/4
}
