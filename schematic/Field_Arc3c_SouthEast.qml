import QtQuick 2.15

Field_Arc3c_NorthEast {
    rotation: 90
    currentId: tileData ? tileData.FieldArc3cSouthEastId : invalidId
    visible: tileData && tileData.FieldArc3cSouthEast
}
