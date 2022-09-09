import QtQuick 2.15

Rectangle {
    id: root

    width: 20
    height: 20
    color: "white"
    radius: 5
    border.color: "black"
    property alias tint: image.color
    property alias source: image.source
    property alias margin: image.anchors.margins

    ColoredImage {
        id: image
        anchors.fill: parent
    }
}
