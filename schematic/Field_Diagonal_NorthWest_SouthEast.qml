import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData.FieldDiagonalNWSEId
    visible: tileData.FieldDiagonalNWSE

    ShapePath {
        startX: side
        startY: side/2
        strokeColor: fillColor
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.field

        PathLine {
            x: side
            y: side
        }

        PathLine {
            x: side/2
            y: side
        }

        PathLine {
            x: side/2
            y: 0
        }

        PathLine {
            x: 0
            y: 0
        }

        PathLine {
            x: 0
            y: side/2
        }

        PathLine {
            x: side
            y: side/2
        }
    }

    idLabel.x: side/4
    idLabel.y: side/4
}
