import QtQuick 2.15
import QtQuick.Shapes 1.15
import "qrc:/"

BaseMapObject {
    id: root

    currentId: tileData ? tileData.Town1e3cNorthToSouthEastId : invalidId
    visible: tileData && tileData.Town1e3cNorthToSouthEast

    ShapePath {
        startX: 0
        startY: 0
        fillColor: strokeColor
        strokeColor: root.highlighted ? Constants.color.schematic.highlighter : Constants.color.schematic.town

        PathArc {
            x: side
            y: side
            radiusX: side
            radiusY: side
            direction: PathArc.Counterclockwise
        }

        PathArc {
            x: side
            y: 0
            radiusX: town1eRadius
            radiusY: town1eRadius
        }
    }

    Rectangle {
        id: westBorder

        x: 0
        y: -side
        width: 2*side
        height: 2*side
        radius: height/2
        color: "transparent"
        border.width: 2
        border.color: Constants.color.schematic.townBorder
    }

    Rectangle {
        id: eastBorder

        x: side - town1eOffset
        y: side / 2 - width / 2
        width: 2*town1eRadius
        height: 2*town1eRadius
        radius: height/2
        color: "transparent"
        border.width: 2
        border.color: Constants.color.schematic.townBorder
    }

    TileBonuses {
        mapObject: root
        primaryPoint: Qt.point(50, 20)
    }

    idLabel.anchors.horizontalCenter: horizontalCenter
    idLabel.anchors.verticalCenter: verticalCenter
}
