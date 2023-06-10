import QtQuick 2.15

Town_1e4c_North {
    rotation: 180
    currentId: tileData ? tileData.Town1e4cSouthId : invalidId
    visible: tileData && tileData.Town1e4cSouth
}
