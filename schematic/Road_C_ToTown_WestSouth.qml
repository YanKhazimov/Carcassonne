import QtQuick 2.15

Road_C_ToTown_NorthWest {
    rotation: 270
    currentId: tileData ? tileData.C_ToTown_WestSouthRoadId : invalidId
    visible: tileData && tileData.C_ToTown_WestSouthRoad
}
