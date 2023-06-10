import QtQuick 2.15

Road_L_NorthEast {
    rotation: 90
    currentId: tileData ? tileData.L_SouthEastRoadId : invalidId
    visible: tileData && tileData.L_SouthEastRoad
}
