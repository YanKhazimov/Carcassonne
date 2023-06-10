import QtQuick 2.15

Field_Arc_North {
    rotation: 270
    currentId: tileData ? tileData.FieldArcWestId : invalidId
    visible: tileData && tileData.FieldArcWest
}
