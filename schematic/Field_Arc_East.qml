import QtQuick 2.15

Field_Arc_North {
    rotation: 90
    currentId: tileData ? tileData.FieldArcEastId : invalidId
    visible: tileData && tileData.FieldArcEast
}
