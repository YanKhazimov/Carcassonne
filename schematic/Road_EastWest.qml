import QtQuick 2.15

Road_NorthSouth {
    rotation: 90
    currentId: tileData ? tileData.RoadEastWestId : invalidId
    visible: tileData && tileData.RoadEastWest
}
