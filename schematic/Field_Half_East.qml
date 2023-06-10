import QtQuick 2.15

Field_Half_North {
    rotation: 90
    currentId: tileData ? tileData.FieldEastId : invalidId
    visible: tileData && tileData.FieldEast
}
