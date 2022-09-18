import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData.AbbeyId
    visible: tileData.Abbey

    ShapePath {
        startX: 0
        startY: 0
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : "crimson"
        strokeColor: Constants.color.schematic.townBorder
        strokeWidth: 2 * 2 // half will be visible

        PathLine {
            x: 0
            y: side
        }

        PathLine {
            x: side
            y: side
        }

        PathLine {
            x: side
            y: 0
        }

        PathLine {
            x: 0
            y: 0
        }
    }

    idLabel.anchors.horizontalCenter: horizontalCenter
    idLabel.anchors.verticalCenter: verticalCenter
}
