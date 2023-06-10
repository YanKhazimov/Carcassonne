import QtQuick 2.15

Road_L_NorthEast {
    rotation: 180
    currentId: tileData ? tileData.L_SouthWestRoadId : invalidId
    visible: tileData && tileData.L_SouthWestRoad
}
