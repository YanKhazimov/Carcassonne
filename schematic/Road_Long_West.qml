import QtQuick 2.15

Road_Long_North {
    rotation: 270
    currentId: tileData ? tileData.RoadLongWestId : invalidId
    visible: tileData && tileData.RoadLongWest
}
