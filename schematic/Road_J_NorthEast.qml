import QtQuick 2.15

Road_J_NorthWest {
    rotation: 90
    currentId: tileData ? tileData.J_NorthEastRoadId : invalidId
    visible: tileData && tileData.J_NorthEastRoad
}
