import QtQuick 2.15

Road_North {
    rotation: 180
    currentId: tileData ? tileData.RoadSouthId : invalidId
    visible: tileData && tileData.RoadSouth
}
