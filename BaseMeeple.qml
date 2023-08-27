import QtQuick 2.15
import QmlPresenter 1.0
import QtGraphicalEffects 1.15

AnimatedItem {
    id: root

    z: 2

    property real xRatio
    property real yRatio
    property bool draggable
    property var type
    required property int playerIndex
    readonly property color playerColor: engine && playerIndex < engine.PlayerCount
                                         ? engine.getPlayer(playerIndex).Color
                                         : "white"
    required property var imageSource
    required property real typeWidthModifier
    required property real typeHeightModifier

    property bool isInHand: true

    width: typeWidthModifier * (isInHand ? Constants.smallMeeplePreviewSize : Constants.smallMeepleSize)
    height: typeHeightModifier * (isInHand ? Constants.smallMeeplePreviewSize : Constants.smallMeepleSize)

    QtObject {
        id: internal

        property int defaultX
        property int defaultY

        Component.onCompleted: {
            defaultX = root.x
            defaultY = root.y
        }
    }

    function resetPosition() {
        x = internal.defaultX
        y = internal.defaultY
        rotation = 0
        isInHand = true
    }

    Component.onCompleted: {
        draggable = true
    }

    MouseArea {
        id: dragArea

        anchors.fill: parent
        drag.target: parent
        cursorShape: Qt.SizeAllCursor
        propagateComposedEvents: true
        visible: root.draggable &&
                 engine &&
                 (engine.GameState === GameEngine.TileFixed || engine.GameState === GameEngine.MeeplePlaced) &&
                 playerIndex === engine.ActivePlayer
    }

    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: width/2
    Drag.hotSpot.y: height/2
    Drag.keys: ["meeple"]

    property alias dragActive: dragArea.drag.active

    Behavior on x { NumberAnimation { duration: 400 } }
    Behavior on y { NumberAnimation { duration: 400 } }

    signal dragStarted()
    signal dragFinished()
    signal reset()

    onDragActiveChanged:
    {
        if (dragActive)
        {
            engine.highlight(-1)
            dragStarted()
            isInHand = false
        }
        else
        {
            if (Drag.target != null && Drag.target.acceptsActiveMeeple())
            {
                Drag.drop()
                engine.GameState = GameEngine.MeeplePlaced
                dragFinished()
            }
            else
            {
                Drag.cancel()
                engine.GameState = GameEngine.TileFixed
                resetPosition()
                dragFinished()
                //TODO indicate an unsuccessful drag
            }
        }
    }

    ColoredImage {
        id: image

        source: imageSource
        color: playerColor
        anchors.fill: root
    }

    Item {
        id: shineGradient
        anchors.fill: image

        LinearGradient {
            property real center: shineGradient.width * 0.5
            NumberAnimation on center {
                id: centerAnimation

                from: -shineGradient.width * 0.5
                to: shineGradient.width * 1.5
                duration: 1000
                loops: Animation.Infinite
                running: true
            }

            anchors.fill: parent
            start: root.rotation === 90 ?
                       Qt.point(center - shineGradient.width * 0.5, centerAnimation.to - centerAnimation.from - center + shineGradient.height * 0.5) :
                       Qt.point(center - shineGradient.width * 0.5, center - shineGradient.height * 0.5)
            end: root.rotation === 90 ?
                     Qt.point(center + shineGradient.width * 0.5, 2 - center - shineGradient.height * 0.5) :
                     Qt.point(center + shineGradient.width * 0.5, center + shineGradient.height * 0.5)
            gradient: Gradient {
                GradientStop { position: 0.0; color: "transparent" }
                GradientStop { position: 0.5; color: "white" }
                GradientStop { position: 1.0; color: "black" }
            }
        }
        visible: false
    }

    OpacityMask {
        source: shineGradient
        anchors.fill: shineGradient
        maskSource: image
        visible: !draggable && !isInHand
    }

    ElementActionIndicator {
        target: parent
        visible: dragArea.visible
    }
}
