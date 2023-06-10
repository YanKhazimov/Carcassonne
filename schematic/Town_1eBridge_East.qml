import QtQuick 2.15

Town_1eBridge_North {
    rotation: 90
    currentId: tileData ? tileData.Town1eBridgeEastId : invalidId
    visible: tileData && tileData.Town1eBridgeEast
}
