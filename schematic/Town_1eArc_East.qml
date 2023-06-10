import QtQuick 2.15

Town_1eArc_North {
    rotation: 90
    currentId: tileData ? tileData.Town1eArcEastId : invalidId
    visible: tileData && tileData.Town1eArcEast
}
