import QtQuick 2.15

Field_HalfQuarter_NEE {
    rotation: 90
    currentId: tileData ? tileData.FieldHalfQuarterSSEId : invalidId
    visible: tileData && tileData.FieldHalfQuarterSSE
}
