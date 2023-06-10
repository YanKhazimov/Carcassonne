import QtQuick 2.15

Field_Quarter_NorthEast {
    rotation: 90
    currentId: tileData ? tileData.FieldSouthEastId : invalidId
    visible: tileData && tileData.FieldSouthEast
}
