import QtQuick 2.15

Road_C_ToTown_NorthWest {
    rotation: 90
    currentId: tileData ? tileData.C_ToTown_EastNorthRoadId : invalidId
    visible: tileData && tileData.C_ToTown_EastNorthRoad
}
