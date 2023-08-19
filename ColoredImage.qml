import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root

    property alias source: img.source
    property alias fillMode: img.fillMode
    property alias color: overlay.color

    width: img.sourceSize.width
    height: img.sourceSize.height

    Image {
        id: img

        anchors.fill: parent
    }

    ColorOverlay {
        id: overlay

        source: img
        anchors.fill: img
        color: root.color
    }
}
