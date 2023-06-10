import QtQuick 2.15

Road_J_NorthWest {
    rotation: 270
    currentId: tileData ? tileData.J_SouthWestRoadId : invalidId
    visible: tileData && tileData.J_SouthWestRoad
}
