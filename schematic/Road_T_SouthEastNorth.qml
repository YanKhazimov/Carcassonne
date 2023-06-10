import QtQuick 2.15

Road_T_NorthWestSouth {
    rotation: 180
    currentId: tileData ? tileData.T_SouthEastNorthRoadId : invalidId
    visible: tileData && tileData.T_SouthEastNorthRoad
}
