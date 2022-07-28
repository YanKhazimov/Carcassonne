import QtQuick 2.15

MouseArea {
    id: root

    required property var objectList

    function rotate(p, objectRotation) {
        while (objectRotation > 0)
        {
            // rotateCounterClockwise90
            p = Qt.point(p.y, root.width - p.x)
            objectRotation -= 90
        }

        if (objectRotation !== 0) {
            console.error("Unsupported rotation", obj.rotation)
        }

        return p
    }

    hoverEnabled: true
    cursorShape: Qt.PointingHandCursor
    onClicked: {
        var currentId
        for (var i = 0; i < objectList.length; ++i)
        {
            var obj = objectList[i]
            if (!obj.visible)
                continue

            var rotatedPoint = rotate(Qt.point(mouseX, mouseY), obj.rotation)
            if (obj.contains(rotatedPoint))
                currentId = obj.currentId
        }

        engine.highlight(currentId !== undefined ? currentId : -1)
    }
}
