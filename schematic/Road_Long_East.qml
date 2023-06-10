import QtQuick 2.15

Road_Long_North {
    rotation: 90
    currentId: tileData ? tileData.RoadLongEastId : invalidId
    visible: tileData && tileData.RoadLongEast
}
