import QtQuick 2.15

Rectangle {
    id: root

    property alias text: text.text
    signal clicked()

    width: 100
    height: 30
    radius: 8
    color: "lightgrey"
    border.color: enabled ? "black" : "grey"

    Text {
        id: text
        anchors.centerIn: parent
        color: enabled ? "black" : "grey"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
