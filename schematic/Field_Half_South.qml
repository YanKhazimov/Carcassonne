import QtQuick 2.15

Field_Half_North {
    rotation: 180
    currentId: tileData ? tileData.FieldSouthId : invalidId
    visible: tileData && tileData.FieldSouth
}
