import QtQuick 2.15

Item {
    id: root

    required property Item mapObject
    property int xOffset: 0
    property int yOffset: 0
    property point primaryPoint
    property point secondaryPoint

    TileBonusIndicator {
        source: "qrc:/img/shield.png"
        visible: mapObject.tileData.BonusTypes[mapObject.bonusSideIndex] > 3
        x: primaryPoint.x - width/2
        y: primaryPoint.y - height/2
        rotation: -mapObject.rotation
    }

    TileBonusIndicator {
        source: "qrc:/img/shield.png"
        visible: mapObject.tileData.BonusTypes[mapObject.bonusSideIndex] === 5
        x: secondaryPoint.x - width/2
        y: secondaryPoint.y - height/2
        rotation: -mapObject.rotation
    }

    TileBonusIndicator {
        source: "qrc:/img/wheat.png"
        visible: mapObject.tileData.BonusTypes[mapObject.bonusSideIndex] === 1
        x: primaryPoint.x - width/2
        y: primaryPoint.y - height/2
        rotation: -mapObject.rotation
    }

    TileBonusIndicator {
        source: "qrc:/img/barrel.png"
        visible: mapObject.tileData.BonusTypes[mapObject.bonusSideIndex] === 2
        x: primaryPoint.x - width/2
        y: primaryPoint.y - height/2
        rotation: -mapObject.rotation
    }

    TileBonusIndicator {
        source: "qrc:/img/cloth.png"
        visible: mapObject.tileData.BonusTypes[mapObject.bonusSideIndex] === 3
        x: primaryPoint.x - width/2
        y: primaryPoint.y - height/2
        rotation: -mapObject.rotation
    }
}
