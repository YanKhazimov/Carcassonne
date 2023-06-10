import QtQuick 2.15

Field_HalfQuarter_SEE {
    rotation: 180
    currentId: tileData ? tileData.FieldHalfQuarterNWWId : invalidId
    visible: tileData && tileData.FieldHalfQuarterNWW
}
