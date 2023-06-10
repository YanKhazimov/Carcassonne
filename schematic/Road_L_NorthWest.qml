import QtQuick 2.15

Road_L_NorthEast {
    rotation: 270
    currentId: tileData ? tileData.L_NorthWestRoadId : invalidId
    visible: tileData && tileData.L_NorthWestRoad
}
