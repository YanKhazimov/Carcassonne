import QtQuick 2.15

Rectangle {
    required property Item target
    property int margin: 5

    anchors.fill: target
    anchors.margins: -margin
    radius: margin
    color: "grey"
    z: -1

    SequentialAnimation on opacity {
        loops: Animation.Infinite

        NumberAnimation  {
            from: 0
            to: 0.5
            duration: 500
        }
        NumberAnimation  {
            from: 0.5
            to: 0
            duration: 500
        }
    }
}
