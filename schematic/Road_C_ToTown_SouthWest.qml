import QtQuick 2.15

Road_C_ToTown_NorthEast {
    rotation: 180
    currentId: tileData ? tileData.C_ToTown_SouthWestRoadId : invalidId
    visible: tileData && tileData.C_ToTown_SouthWestRoad
}
