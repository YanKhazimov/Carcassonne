import QtQuick 2.15
import "qrc:/"

Item {
    id: root

    clip: true
    width: 90
    height: 90

    Rectangle {
        id: townShape

        color: "chocolate"

        anchors.fill: parent
        layer.enabled: true
        layer.smooth: true
        layer.effect: InvertedOpacityMaskShader {
            maskSource: backgroudMask
            anchors.fill: townShape
        }
    }

    ShaderEffectSource {
        id: backgroudMask

        property real maskSize: 90

        visible: false
        live: true
        sourceItem: Item {
            width: backgroudMask.maskSize
            height: backgroudMask.maskSize
            opacity: 0
            clip: true

            Rectangle {
                width: 2 * 90
                height: 2 * 90
                radius: height / 2
                //y: -90
            }
        }
    }

    Rectangle {
        id: border

        width: 2 * 90 + 2 * 2
        height: 2 * 90 + 2 * 2
        radius: height / 2
        color: "transparent"
        x: -2
        y: /*-90*/-2
        border.width: 2
        border.color: "brown"
    }
}
