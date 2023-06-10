import QtQuick 2.15

Field_Arc_North {
    rotation: 180
    currentId: tileData ? tileData.FieldArcSouthId : invalidId
    visible: tileData && tileData.FieldArcSouth
}
