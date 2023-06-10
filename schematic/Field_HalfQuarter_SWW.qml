import QtQuick 2.15

Field_HalfQuarter_NEE {
    rotation: 180
    currentId: tileData ? tileData.FieldHalfQuarterSWWId : invalidId
    visible: tileData && tileData.FieldHalfQuarterSWW
}
