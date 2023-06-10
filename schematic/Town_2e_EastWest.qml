import QtQuick 2.15

Town_2e_NorthSouth {
    rotation: 90
    currentId: tileData ? tileData.Town2eEastWestId : invalidId
    visible: tileData && tileData.Town2eEastWest
}
