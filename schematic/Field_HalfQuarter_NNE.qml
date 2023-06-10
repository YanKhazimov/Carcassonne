import QtQuick 2.15

Field_HalfQuarter_SEE {
    rotation: 270
    currentId: tileData ? tileData.FieldHalfQuarterNNEId : invalidId
    visible: tileData && tileData.FieldHalfQuarterNNE
}
