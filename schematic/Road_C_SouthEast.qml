import QtQuick 2.15

Road_C_NorthEast {
    rotation: 90
    currentId: tileData ? tileData.C_SouthEastRoadId : invalidId
    visible: tileData && tileData.C_SouthEastRoad
}
