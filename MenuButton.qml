import QtQuick 2.15

Rectangle {
    id: root

    property alias text: text.text
    signal clicked()

    width: 120
    height: 30
    radius: 8
    color: "lightgrey"
    border.color: enabled ? "black" : "grey"

    Text {
        id: text
        anchors.centerIn: parent
        color: enabled ? "black" : "grey"
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
