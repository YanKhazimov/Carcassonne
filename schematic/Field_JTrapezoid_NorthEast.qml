import QtQuick 2.15

Field_JTrapezoid_NorthWest {
    rotation: 90
    currentId: tileData ? tileData.FieldJTrapezoidNorthEastId : invalidId
    visible: tileData && tileData.FieldJTrapezoidNorthEast
}
