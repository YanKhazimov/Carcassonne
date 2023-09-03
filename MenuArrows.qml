import QtQuick 2.15
import QtGraphicalEffects 1.15

Item {
    id: root

    property alias leftActive: leftMouseArea.visible
    property alias rightActive: rightMouseArea.visible

    property color leftColor: "white"
    property color rightColor: "white"

    function leftClickCallback() {}
    function rightClickCallback() {}

    anchors.fill: parent

    MouseArea {
        id: leftMouseArea

        property bool lastClicked: containsMouse

        width: 40
        height: 40
        anchors.right: parent.left
        anchors.verticalCenter: parent.verticalCenter
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            lastClicked = true
            rightMouseArea.lastClicked = false

            leftClickCallback()
        }
    }

    RadialGradient {
        anchors.fill: leftMouseArea
        visible: leftMouseArea.containsMouse && leftMouseArea.visible
        gradient: Gradient {
            GradientStop { position: 0.0; color: root.leftColor }
            GradientStop { position: 0.5; color: "transparent" }
        }
    }

    Image {
        anchors.centerIn: leftMouseArea
        source: "qrc:/img/right.png"
        rotation: 180
        width: 24
        height: 24
        opacity: leftMouseArea.visible ? 1.0 : 0.3
    }

    MouseArea {
        id: rightMouseArea

        property bool lastClicked: containsMouse

        width: 40
        height: 40
        anchors.left: parent.right
        anchors.verticalCenter: parent.verticalCenter
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            lastClicked = true
            leftMouseArea.lastClicked = false

            rightClickCallback()
        }
    }

    RadialGradient {
        anchors.fill: rightMouseArea
        visible: rightMouseArea.containsMouse && rightMouseArea.visible
        gradient: Gradient {
            GradientStop { position: 0.0; color: root.rightColor }
            GradientStop { position: 0.5; color: "transparent" }
        }
    }

    Image {
        anchors.centerIn: rightMouseArea
        source: "qrc:/img/right.png"
        width: 24
        height: 24
        opacity: rightMouseArea.visible ? 1.0 : 0.3
    }
}
