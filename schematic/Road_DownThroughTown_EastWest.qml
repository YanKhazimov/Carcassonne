import QtQuick 2.15

Road_DownThroughTown_NorthSouth {
    rotation: 90
    currentId: tileData ? tileData.RoadDownThroughTownEastWestId : invalidId
    visible: tileData && tileData.RoadDownThroughTownEastWest
}
