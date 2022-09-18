import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData.TownWholeId
    visible: tileData.TownWhole

    ShapePath {
        startX: side
        startY: side
        strokeColor: fillColor
        fillColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.town

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

    idLabel.x: side/2
    idLabel.y: side/2

    TileBonuses {
        mapObject: root
        primaryPoint: Qt.point(20, 20)
        secondaryPoint: Qt.point(40, 40)
    }
}
