import QtQuick 2.15

Field_JTrapezoid_NorthWest {
    rotation: 270
    currentId: tileData ? tileData.FieldJTrapezoidSouthWestId : invalidId
    visible: tileData && tileData.FieldJTrapezoidSouthWest
}
