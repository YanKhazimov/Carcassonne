import QtQuick 2.15

Rectangle {
    id: root

    property alias text: text.text
    property alias font: text.font

    signal clicked()

    width: 130
    height: 30
    radius: 8
    color: "white"
    border.color: enabled ? "black" : "grey"

    Text {
        id: text
        anchors.centerIn: parent
        color: enabled ? "black" : "lightgrey"
        font.pixelSize: 15
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }

    ElementActionIndicator {
        target: parent
        visible: root.enabled
    }
}
