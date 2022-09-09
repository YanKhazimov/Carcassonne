import QtQuick 2.15

Item {
    id: root

    property Board board
    property bool runAnimations

    Component.onCompleted: runAnimations = false
    anchors.fill: board

    function dimAround(x, y) {
        runAnimations = true

        spotlight.x = board.getX(x)
        spotlight.y = board.getY(y)
        spotlight.width = Constants.tileSize
        spotlight.height = Constants.tileSize
    }

    function undim() {
        spotlight.x = 0
        spotlight.y = 0
        spotlight.width = root.width
        spotlight.height = root.height
    }

    Item {
        id: spotlight

        Component.onCompleted: undim()

        Behavior on width {
            enabled: runAnimations
            NumberAnimation { duration: 200 }
        }
        Behavior on height {
            enabled: runAnimations
            NumberAnimation { duration: 200 }
        }
        Behavior on x {
            enabled: runAnimations
            NumberAnimation { duration: 200 }
        }
        Behavior on y {
            enabled: runAnimations
            NumberAnimation { duration: 200 }
        }
    }

    Rectangle {
        anchors.top: parent.top
        anchors.bottom: spotlight.top
        width: parent.width
        color: Qt.rgba(0.1, 0.1, 0.1, 0.6)
    }

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.top: spotlight.bottom
        width: parent.width
        color: Qt.rgba(0.1, 0.1, 0.1, 0.6)
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: spotlight.left
        anchors.top: spotlight.top
        anchors.bottom: spotlight.bottom
        color: Qt.rgba(0.1, 0.1, 0.1, 0.6)
    }

    Rectangle {
        anchors.right: parent.right
        anchors.left: spotlight.right
        anchors.top: spotlight.top
        anchors.bottom: spotlight.bottom
        color: Qt.rgba(0.1, 0.1, 0.1, 0.6)
    }
}
