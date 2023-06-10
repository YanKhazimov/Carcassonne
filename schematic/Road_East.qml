import QtQuick 2.15

Road_North {
    rotation: 90
    currentId: tileData ? tileData.RoadEastId : invalidId
    visible:  tileData && tileData.RoadEast
}
