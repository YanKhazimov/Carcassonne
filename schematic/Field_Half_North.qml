import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    objectData: tileData ? tileData.FieldNorth : null

    ShapePath {
        startX: side
        startY: side/2
        strokeColor: fillColor
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : fieldColor

        PathLine {
            x: 0
            y: side/2
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

    idLabel.anchors.horizontalCenter: horizontalCenter
    idLabel.y: side * 0.2 // between town1eOffset and town2eOffset
}
