import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData.FieldHalfQuarterSEEId
    visible: tileData.FieldHalfQuarterSEE

    ShapePath {
        startX: side
        startY: side
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
    idLabel.y: side*3/4
}
