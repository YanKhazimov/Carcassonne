import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData ? tileData.FieldWholeId : invalidId
    visible: tileData && tileData.FieldWhole

    ShapePath {
        startX: side
        startY: side
        strokeColor: fillColor
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : fieldColor

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

    idLabel.x: side/4
    idLabel.y: side/4
}
