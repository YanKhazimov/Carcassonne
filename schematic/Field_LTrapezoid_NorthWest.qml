import QtQuick 2.15

Field_LTrapezoid_NorthEast {
    rotation: 270
    currentId: tileData ? tileData.FieldLTrapezoidNorthWestId : invalidId
    visible: tileData && tileData.FieldLTrapezoidNorthWest
}
