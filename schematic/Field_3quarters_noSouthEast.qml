import QtQuick 2.15

Field_3quarters_noNorthEast {
    rotation: 90
    currentId: tileData ? tileData.Field3qNoSouthEastId : invalidId
    visible: tileData && tileData.Field3qNoSouthEast
}
