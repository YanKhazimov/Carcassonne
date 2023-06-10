import QtQuick 2.15

Road_North {
    rotation: 270
    currentId: tileData ? tileData.RoadWestId : invalidId
    visible: tileData && tileData.RoadWest
}
