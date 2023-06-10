import QtQuick 2.15

Town_1eArc_North {
    rotation: 180
    currentId: tileData ? tileData.Town1eArcSouthId : invalidId
    visible: tileData && tileData.Town1eArcSouth
}
