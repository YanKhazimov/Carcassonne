import QtQuick 2.15

Item {
    id: root

    property alias leftOption: leftText.text
    property alias rightOption: rightText.text
    required property var callback
    required property bool on

    width: childrenRect.width
    height: childrenRect.height

    Row {
        spacing: 5

        MyText {
            id: leftText

            font.pixelSize: 20
            color: "white"
            font.family: Fonts.font4
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea {
            onPressed: root.callback()
            width: switchBackground.width
            height: switchBackground.height
            anchors.verticalCenter: parent.verticalCenter
            cursorShape: Qt.PointingHandCursor

            Row {
                id: switchBackground

                spacing: -10

                Rectangle {
                    color: "white"
                    height: 20
                    width: 20
                    radius: 10
                }
                Rectangle {
                    color: "white"
                    height: 20
                    width: 20
                }
                Rectangle {
                    color: "white"
                    height: 20
                    width: 20
                    radius: 10
                }
            }

            Rectangle {
                readonly property int margin: 2
                color: "grey"
                height: 20 - 2 * margin
                width: 20 - 2 * margin
                radius: width / 2
                x: root.on ? (parent.width - width - margin) : margin
                y: margin

                Behavior on x {
                    NumberAnimation {
                        duration: 200
                    }
                }
            }
        }

        MyText {
            id: rightText

            font.pixelSize: 20
            color: "white"
            font.family: Fonts.font4
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
