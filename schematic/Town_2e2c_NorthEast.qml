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
        strokeColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.town

        PathArc {
            x: side
            y: side
            radiusX: 2*side
            radiusY: 2*side
        }

        PathLine {
            x: side
            y: 0
        }
    }

    ShapePath {
        id: border

        startX: 0
        startY: 0
        fillColor: Constants.color.schematic.townBorder
        strokeColor: Constants.color.schematic.townBorder
        strokeWidth: 2

        PathArc {
            x: side
            y: side
            radiusX: 2*side
            radiusY: 2*side
        }

        PathArc {
            x: 0
            y: 0
            radiusX: 2*side
            radiusY: 2*side
            direction: PathArc.Counterclockwise
        }
    }

//    Rectangle {
//        id: border

//        x: side/2
//        y: -side/2
//        width: 2
//        height: 2*side
//        rotation: -45
//        color: Constants.color.schematic.townBorder
//    }

//    Rectangle {
//        id: border

//        x: -side
//        y: 0
//        width: 2*side
//        height: 2*side
//        radius: height/2
//        color: "transparent"
//        border.width: 5
//        border.color: Constants.color.schematic.townBorder
//    }

    TileBonuses {
        mapObject: root
        primaryPoint: Qt.point(root.side/2, 10)
    }

    idLabel.x: side - idLabel.width - idLabel.width
    idLabel.y: idLabel.height
}
