import QtQuick 2.15

Field_LTriangle_NorthEast {
    rotation: 90
    currentId: tileData ? tileData.FieldLTriangleSouthEastId : invalidId
    visible: tileData && tileData.FieldLTriangleSouthEast
}
