import QtQuick 2.15

Rectangle {
    id: root

    property alias tintColor: tintRectangle.color
    property alias tintOpacity: tintRectangle.opacity

    Rectangle {
        id: tintRectangle

        anchors.fill: parent
    }
}
