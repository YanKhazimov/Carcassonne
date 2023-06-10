import QtQuick 2.15

Road_T_NorthWestSouth {
    rotation: 90
    currentId: tileData ? tileData.T_EastNorthWestRoadId : invalidId
    visible: tileData && tileData.T_EastNorthWestRoad
}
