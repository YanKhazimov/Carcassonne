import QtQuick 2.15

Town_1eArc_North {
    rotation: 270
    currentId: tileData ? tileData.Town1eArcWestId : invalidId
    visible: tileData && tileData.Town1eArcWest
}
