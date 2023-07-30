import QtQuick 2.15
import QtQuick.Shapes 1.15

Item {
    id: root

    required property Component myContent
    property alias title: titleText
    property color color: "black"

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

    Shape {
        smooth: true
        anchors.fill: parent

        ShapePath {
            startX: root.width/2 + titleText.width/2 + 10
            startY: titleText.height/2

            strokeWidth: 1
            strokeColor: root.color
            fillColor: "transparent"

            PathLine {
                x: root.width - 10
                y: titleText.height/2
            }

            PathArc {
                x: root.width
                y: titleText.height/2 + 10
                radiusX: 10
                radiusY: 10
            }

            PathLine {
                x: root.width
                y: root.height - 10
            }

            PathArc {
                x: root.width - 10
                y: root.height
                radiusX: 10
                radiusY: 10
            }

            PathLine {
                x: 10
                y: root.height
            }

            PathArc {
                x: 0
                y: root.height - 10
                radiusX: 10
                radiusY: 10
            }

            PathLine {
                x: 0
                y: titleText.height/2 + 10
            }

            PathArc {
                x: 10
                y: titleText.height/2
                radiusX: 10
                radiusY: 10
            }

            PathLine {
                x: root.width/2 - titleText.width/2 - 10
                y: titleText.height/2
            }
        }
    }
}

