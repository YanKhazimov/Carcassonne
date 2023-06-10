import QtQuick 2.15

Field_Diagonal_NorthWest_SouthEast {
    rotation: 90
    currentId: tileData ? tileData.FieldDiagonalNESWId : invalidId
    visible: tileData && tileData.FieldDiagonalNESW
}
