import QtQuick 2.15

MyText {
    id: root

    property point startPos
    property int hDelta: 500

    function run() {
        animation.start()
    }

    x: startPos.x
    y: startPos.y + hDelta * 0.02 * Math.sin(x * 5.0 / hDelta * 3)
    text: "sample"

    ParallelAnimation {
        id: animation

        onFinished: {
            root.destroy()
        }

        NumberAnimation {
            target: root
            property: "x"
            duration: 2000
            to: startPos.x + hDelta
        }

        NumberAnimation {
            target: root
            property: "opacity"
            duration: 2000
            to: 0.0
        }
    }
}
