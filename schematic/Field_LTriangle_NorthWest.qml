import QtQuick 2.15

Field_LTriangle_NorthEast {
    rotation: 270
    currentId: tileData ? tileData.FieldLTriangleNorthWestId : invalidId
    visible: tileData && tileData.FieldLTriangleNorthWest
}
