import QtQuick 2.15

Field_Arc3c_NorthEast {
    rotation: 270
    currentId: tileData ? tileData.FieldArc3cNorthWestId : invalidId
    visible: tileData && tileData.FieldArc3cNorthWest
}
