import QtQuick 2.15

Road_J_NorthWest {
    rotation: 180
    currentId: tileData ? tileData.J_SouthEastRoadId : invalidId
    visible: tileData && tileData.J_SouthEastRoad
}
