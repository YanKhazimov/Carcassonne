import QtQuick 2.15

Field_HalfQuarter_NEE {
    rotation: 270
    currentId: tileData ? tileData.FieldHalfQuarterNNWId : invalidId
    visible: tileData && tileData.FieldHalfQuarterNNW
}
