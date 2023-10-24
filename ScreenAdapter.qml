import QtQuick 2.15

Item {
    id: root

    implicitWidth: 1920
    implicitHeight: 1080

    transform: Scale {
        xScale: Constants.screenScale
        yScale: Constants.screenScale
        origin.x: root.width/2
        origin.y: root.height/2
    }
}
