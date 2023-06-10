import QtQuick 2.15

Town_1eBridge_North {
    rotation: 180
    currentId: tileData ? tileData.Town1eBridgeSouthId : invalidId
    visible: tileData && tileData.Town1eBridgeSouth
}
