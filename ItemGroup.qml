import QtQuick 2.15
import QtGraphicalEffects 1.15

Item {
    id: root

    required property Component myContent
    property alias title: titleText
    property color color: "black"
    readonly property Item item: loader.item

    function getItemPosition() {
        return Qt.point(loader.x, loader.y)
    }

    width: loader.width + 2 * 10
    height: titleText.height + loader.height + 10

    Loader {
        id: loader
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom; anchors.bottomMargin: 10
        sourceComponent: myContent
    }

    Text {
        id: titleText
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 20
    }

    Rectangle {
        id: imgSource

        color: "transparent"
        border.width: 1
        border.color: "black"
        anchors.top: titleText.verticalCenter
        anchors.bottom: parent.bottom
        width: parent.width
        radius: 10
        visible: false
    }

    Item {
        id: mask

        anchors.fill: parent
        visible: false

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: titleText.width + 2 * 10
            height: titleText.height
        }
    }

    OpacityMask {
        source: imgSource
        anchors.fill: imgSource
        maskSource: mask
        invert: true
    }
}

