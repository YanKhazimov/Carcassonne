import QtQuick 2.15

Field_Quarter_NorthEast {
    rotation: 270
    currentId: tileData ? tileData.FieldNorthWestId : invalidId
    visible: tileData && tileData.FieldNorthWest
}
