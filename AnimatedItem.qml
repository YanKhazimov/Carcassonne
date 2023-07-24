import QtQuick 2.15

Item {
    id: root

    property int animationDuration: 100
    property int pauseDuration: 0

    function appear() {
        appearanceAnimation.start()
    }

    signal appeared()

    SequentialAnimation {
        id: appearanceAnimation

        onStopped: root.appeared()

        ParallelAnimation {
            NumberAnimation {
                target: root
                property: "opacity"
                from: 0.0
                to: 1.0
                duration: root.animationDuration
            }

            NumberAnimation {
                target: root
                property: "width"
                from: root.width * 3
                to: root.width
                duration: root.animationDuration
            }

            NumberAnimation {
                target: root
                property: "height"
                from: root.height * 3
                to: root.height
                duration: root.animationDuration
            }

            NumberAnimation {
                target: root
                property: "x"
                from: root.x - root.width
                to: root.x
                duration: root.animationDuration
            }

            NumberAnimation {
                target: root
                property: "y"
                from: root.y - root.height
                to: root.y
                duration: root.animationDuration
            }
        }

        PauseAnimation {
            duration: root.pauseDuration
        }
    }
}

