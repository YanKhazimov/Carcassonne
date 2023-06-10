import QtQuick 2.15

Field_HalfQuarter_SEE {
    rotation: 90
    currentId: tileData ? tileData.FieldHalfQuarterSSWId : invalidId
    visible: tileData && tileData.FieldHalfQuarterSSW
}
