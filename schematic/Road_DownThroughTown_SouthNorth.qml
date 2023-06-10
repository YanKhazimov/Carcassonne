import QtQuick 2.15

Road_DownThroughTown_NorthSouth {
    rotation: 180
    currentId: tileData ? tileData.RoadDownThroughTownSouthNorthId : invalidId
    visible: tileData && tileData.RoadDownThroughTownSouthNorth
}
