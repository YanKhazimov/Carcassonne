import QtQuick 2.15
import EngineEnums 1.0

Item {
    property int score
    property color playerColor
    property int objectSize
    property string imagePath
    property string playerName
    property int meepleType
    property string objectType
    property int objectId
    property var tile
    property var meeples

    width: childrenRect.width
    height: childrenRect.height
}
