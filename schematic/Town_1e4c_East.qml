import QtQuick 2.15

Town_1e4c_North {
    rotation: 90
    currentId: tileData ? tileData.Town1e4cEastId : invalidId
    visible: tileData && tileData.Town1e4cEast
}
