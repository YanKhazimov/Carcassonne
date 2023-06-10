import QtQuick 2.15

Road_Long_North {
    rotation: 180
    currentId: tileData ? tileData.RoadLongSouthId : invalidId
    visible: tileData && tileData.RoadLongSouth
}
