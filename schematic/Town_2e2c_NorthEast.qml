import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData.Town2e2cNorthEastId
    visible: tileData.Town2e2cNorthEast

    ShapePath {
        startX: 0
        startY: 0
        fillColor: strokeColor
        strokeColor: root.highlighted ? Constants.color.schematic.highlighter : "chocolate"

        PathLine {
            x: side
            y: side
//            radiusX: side
//            radiusY: side
        }

        PathLine {
            x: side
            y: 0
        }
    }

    clip: true

    Rectangle {
        id: border

        x: side/2
        y: -side/2
        width: 2
        height: 2*side
        rotation: -45
        color: "brown"
    }

//    Rectangle {
//        id: border

//        x: -side
//        y: 0
//        width: 2*side
//        height: 2*side
//        radius: height/2
//        color: "transparent"
//        border.width: 2
//        border.color: "brown"
//    }

    TileBonuses {
        mapObject: root
        primaryPoint: Qt.point(50, 20)
    }

    idLabel.x: side - idLabel.width - idLabel.width
    idLabel.y: idLabel.height
}
