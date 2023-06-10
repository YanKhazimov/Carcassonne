import QtQuick 2.15

Town_1eBridge_North {
    rotation: 270
    currentId: tileData ? tileData.Town1eBridgeWestId : invalidId
    visible: tileData && tileData.Town1eBridgeWest
}
