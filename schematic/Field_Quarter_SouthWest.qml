import QtQuick 2.15

Field_Quarter_NorthEast {
    rotation: 180
    currentId: tileData ? tileData.FieldSouthWestId : invalidId
    visible: tileData && tileData.FieldSouthWest
}
