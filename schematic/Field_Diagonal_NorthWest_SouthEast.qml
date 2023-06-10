import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData ? tileData.FieldDiagonalNWSEId : invalidId
    visible: tileData && tileData.FieldDiagonalNWSE

    ShapePath {
        startX: side
        startY: side
        strokeColor: fillColor
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : fieldColor

        PathLine {
            x: side
            y: side/2
        }

        PathArc {
            x: side/2
            y: 0
            radiusX: side/2
            radiusY: side/2
        }

        PathLine {
            x: 0
            y: 0
        }

        PathLine {
            x: 0
            y: side/2
        }

        PathArc {
            x: side/2
            y: side
            radiusX: side
            radiusY: side/2
        }
    }

    idLabel.x: side/4
    idLabel.y: side/4
}
