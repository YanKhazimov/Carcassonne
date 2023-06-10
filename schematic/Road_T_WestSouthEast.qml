import QtQuick 2.15

Road_T_NorthWestSouth {
    rotation: 270
    currentId: tileData ? tileData.T_WestSouthEastRoadId : invalidId
    visible: tileData && tileData.T_WestSouthEastRoad
}
