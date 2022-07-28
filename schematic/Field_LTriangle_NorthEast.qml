import QtQuick 2.15
import QtQuick.Shapes 1.12
import "qrc:/"

BaseMapObject {
    id: root

    ShapePath {
        startX: side/2
        startY: 0
        strokeColor: fillColor
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : "lightgreen"

        PathLine {
            x: side - town1eOffset - halfRoadWidth
            y: side/2
        }

        PathLine {
            x: side
            y: 0
        }
    }
}
