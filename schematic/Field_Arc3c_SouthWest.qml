import QtQuick 2.15

Field_Arc3c_NorthEast {
    rotation: 180
    currentId: tileData ? tileData.FieldArc3cSouthWestId : invalidId
    visible: tileData && tileData.FieldArc3cSouthWest
}
