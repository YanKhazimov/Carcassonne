import QtQuick 2.15

Field_JTriangle_NorthWest {
    rotation: 90
    currentId: tileData ? tileData.FieldJTriangleNorthEastId : invalidId
    visible: tileData && tileData.FieldJTriangleNorthEast
}
