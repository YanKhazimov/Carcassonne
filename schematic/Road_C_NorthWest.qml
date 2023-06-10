import QtQuick 2.15

Road_C_NorthEast {
    rotation: 270
    currentId: tileData ? tileData.C_NorthWestRoadId : invalidId
    visible: tileData && tileData.C_NorthWestRoad
}
