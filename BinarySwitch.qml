import QtQuick 2.15

Item {
    id: root

    enum SwitchState {
        LEFT,
        RIGHT
    }

    property alias leftOption: leftText.text
    property alias rightOption: rightText.text
    required property var defaultState
    signal stateChanged(bool state)

    QtObject {
        id: internal
        property var state
    }

    Component.onCompleted: internal.state = defaultState

    width: childrenRect.width
    height: childrenRect.height

    Row {
        spacing: 5

        Text {
            id: leftText

            font.pixelSize: 15
        }

        MouseArea {
            onPressed: {
                if (internal.state === BinarySwitch.SwitchState.RIGHT)
                    internal.state = BinarySwitch.SwitchState.LEFFT
                else
                    internal.state = BinarySwitch.SwitchState.RIGHT

                root.stateChanged(internal.state)
            }

            width: childrenRect.width
            height: childrenRect.height

            Row {
                id: switchBackground

                spacing: -10

                Rectangle {
                    color: "#444444"
                    height: 20
                    width: 20
                    radius: 10
                }
                Rectangle {
                    color: "#444444"
                    height: 20
                    width: 20
                }
                Rectangle {
                    color: "#444444"
                    height: 20
                    width: 20
                    radius: 10
                }
            }

            Rectangle {
                readonly property int margin: 2
                color: "lightgrey"
                height: 20 - 2 * margin
                width: 20 - 2 * margin
                radius: width / 2
                x: internal.state === BinarySwitch.SwitchState.RIGHT ? (parent.width - width - margin) : margin
                y: margin

                Behavior on x {
                    NumberAnimation {
                        duration: 200
                    }
                }
            }
        }

        Text {
            id: rightText

            font.pixelSize: 15
        }
    }
}
