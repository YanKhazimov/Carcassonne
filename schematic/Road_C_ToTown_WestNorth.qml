import QtQuick 2.15

Road_C_ToTown_NorthEast {
    rotation: 270
    currentId: tileData ? tileData.C_ToTown_WestNorthRoadId : invalidId
    visible: tileData && tileData.C_ToTown_WestNorthRoad
}
