import QtQuick 2.15

Road_C_NorthEast {
    rotation: 180
    currentId: tileData ? tileData.C_SouthWestRoadId : invalidId
    visible: tileData && tileData.C_SouthWestRoad
}
