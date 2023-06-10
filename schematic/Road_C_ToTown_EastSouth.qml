import QtQuick 2.15

Road_C_ToTown_NorthEast {
    rotation: 90
    currentId: tileData ? tileData.C_ToTown_EastSouthRoadId : invalidId
    visible: tileData && tileData.C_ToTown_EastSouthRoad
}
