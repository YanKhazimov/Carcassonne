import QtQuick 2.15

Field_LTrapezoid_NorthEast {
    rotation: 90
    currentId: tileData ? tileData.FieldLTrapezoidSouthEastId : invalidId
    visible: tileData && tileData.FieldLTrapezoidSouthEast
}
