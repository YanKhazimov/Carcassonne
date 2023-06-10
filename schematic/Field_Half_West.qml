import QtQuick 2.15

Field_Half_North {
    rotation: 270
    currentId: tileData ? tileData.FieldWestId : invalidId
    visible: tileData && tileData.FieldWest
}
