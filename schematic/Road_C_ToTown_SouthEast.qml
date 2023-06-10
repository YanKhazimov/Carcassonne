import QtQuick 2.15

Road_C_ToTown_NorthWest {
    rotation: 180
    currentId: tileData ? tileData.C_ToTown_SouthEastRoadId : invalidId
    visible: tileData && tileData.C_ToTown_SouthEastRoad
}
