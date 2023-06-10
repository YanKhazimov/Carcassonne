import QtQuick 2.15

Field_JTriangle_NorthWest {
    rotation: 270
    currentId: tileData ? tileData.FieldJTriangleSouthWestId : invalidId
    visible: tileData && tileData.FieldJTriangleSouthWest
}
