import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData.FieldHalfQuarterNEEId
    visible: tileData.FieldHalfQuarterNEE

    ShapePath {
        startX: side
        startY: 0
        strokeColor: fillColor
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : fieldColor

        PathLine {
            x: side/2
            y: side/2
        }

        PathLine {
            x: side
            y: side/2
        }
    }

    idLabel.x: side - idLabel.width
    idLabel.y: side/4
}
