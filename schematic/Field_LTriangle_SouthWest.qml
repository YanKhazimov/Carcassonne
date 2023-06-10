import QtQuick 2.15

Field_LTriangle_NorthEast {
    rotation: 180
    currentId: tileData ? tileData.FieldLTriangleSouthWestId : invalidId
    visible: tileData && tileData.FieldLTriangleSouthWest
}
