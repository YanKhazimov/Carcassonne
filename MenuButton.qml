import QtQuick 2.15
import QtGraphicalEffects 1.15

Rectangle {
    id: root

    property alias text: text.text
    property alias font: text.font
    property alias actionIndicated: elementActionIndicator.visible
    property alias hotkeyText: hotkey.text
    property bool activeIndicator: enabled

    signal clicked()

    width: 130
    height: 30
    radius: 8
    color: "white"
    border.color: enabled ? "black" : "grey"
    border.width: 2

    RadialGradient {
        anchors.fill: parent
        anchors.topMargin: -10
        anchors.bottomMargin: -10
        anchors.leftMargin: -20
        anchors.rightMargin: -20
        visible: mouseArea.containsMouse
        gradient: Gradient {
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 0.5; color: "transparent" }
        }
    }

    Text {
        id: text
        color: enabled ? "black" : "lightgrey"
        font.pixelSize: 15
        anchors.centerIn: parent
    }

    Rectangle {
        anchors.right: parent.right; anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        radius: 3
        width: hotkey.contentWidth + 6
        height: root.height - 12
        color: "#333333"
        visible: hotkey.text !== ""

        Text {
            id: hotkey
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: 15
        }
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
        visible: activeIndicator
    }
}
