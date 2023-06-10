import QtQuick 2.15

Field_JTriangle_NorthWest {
    rotation: 180
    currentId: tileData ? tileData.FieldJTriangleSouthEastId : invalidId
    visible: tileData && tileData.FieldJTriangleSouthEast
}
