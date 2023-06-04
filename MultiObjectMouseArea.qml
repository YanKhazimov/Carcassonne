import QtQuick 2.15
import QmlPresenter 1.0

MouseArea {
    id: root

    required property var objectList

    QtObject {
        id: internal

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

        function objectIndexAt(x, y) {
            var result = -1
            var resultZ = -1
            for (var i = 0; i < objectList.length; ++i)
            {
                var obj = objectList[i]
                if (!obj.visible)
                    continue

                var rotatedPoint = rotate(Qt.point(x, y), obj.rotation)
                if (obj.contains(rotatedPoint) && obj.z >= resultZ)
                {
                    result = i
                    resultZ = obj.z
                }
            }

            return result
        }
    }

    function objectAt(x, y) {
        var idx = internal.objectIndexAt(x, y)
        return idx !== -1 ? objectList[idx] : null
    }

    hoverEnabled: true
    cursorShape: Qt.PointingHandCursor
    onClicked: {
        if (engine.GameState === GameEngine.GameEnd)
        {
            engine.scoreField(objectAt(mouseX, mouseY).currentId)
        }
        else
        {
            engine.highlight(objectAt(mouseX, mouseY).currentId)
        }
    }
}
