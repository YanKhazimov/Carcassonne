import QtQuick 2.15

Field_3quarters_noNorthEast {
    rotation: 180
    currentId: tileData ? tileData.Field3qNoSouthWestId : invalidId
    visible: tileData && tileData.Field3qNoSouthWest
}
