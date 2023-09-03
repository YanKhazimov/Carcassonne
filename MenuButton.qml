import QtQuick 2.15
import QtGraphicalEffects 1.15

Rectangle {
    id: root

    property alias text: text.text
    property alias font: text.font
    property alias actionIndicated: elementActionIndicator.visible

    signal clicked()

    width: 130
    height: 30
    radius: 8
    color: "white"
    border.color: enabled ? "black" : "grey"

    RadialGradient {
        anchors.fill: parent
        anchors.margins: -20
        visible: mouseArea.containsMouse
        gradient: Gradient {
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 0.5; color: "transparent" }
        }
    }

    Text {
        id: text
        anchors.centerIn: parent
        color: enabled ? "black" : "lightgrey"
        font.pixelSize: 15
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: root.clicked()
    }

    ElementActionIndicator {
        id: elementActionIndicator
        target: parent
        visible: root.enabled
    }
}
