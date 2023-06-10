import QtQuick 2.15

Field_JTrapezoid_NorthWest {
    rotation: 180
    currentId: tileData ? tileData.FieldJTrapezoidSouthEastId : invalidId
    visible: tileData && tileData.FieldJTrapezoidSouthEast
}
