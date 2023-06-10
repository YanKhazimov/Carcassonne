import QtQuick 2.15

Field_3quarters_noNorthEast {
    rotation: 270
    currentId: tileData ? tileData.Field3qNoNorthWestId : invalidId
    visible: tileData && tileData.Field3qNoNorthWest
}
