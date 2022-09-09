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

    function idAt(x, y)
    {
        var idx = objectIndexAt(x, y)
        return objectList[idx].currentId
    }

    function selectObjectAt(x, y)
    {
        var idx = objectIndexAt(x, y)
        engine.highlight(idx !== -1 ? objectList[idx].currentId : -1)
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

    hoverEnabled: true
    cursorShape: Qt.PointingHandCursor
    onClicked: selectObjectAt(mouseX, mouseY)
}
