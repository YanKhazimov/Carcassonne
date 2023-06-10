import QtQuick 2.15

Road_DownThroughTown_NorthSouth {
    rotation: 270
    currentId: tileData ? tileData.RoadDownThroughTownWestEastId : invalidId
    visible: tileData && tileData.RoadDownThroughTownWestEast
}
