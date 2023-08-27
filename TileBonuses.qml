import QtQuick 2.15
import EngineEnums 1.0

Item {
    id: root

    required property Item mapObject
    property int xOffset: 0
    property int yOffset: 0
    property point primaryPoint
    property point secondaryPoint

    TileBonusIndicator {
        source: "qrc:/img/shield.png"
        visible: mapObject.tileData &&
                 (mapObject.tileData.BonusTypes[mapObject.bonusSideIndex] === EngineEnums.Shield ||
                  mapObject.tileData.BonusTypes[mapObject.bonusSideIndex] === EngineEnums.DoubleShield)
        x: primaryPoint.x - width/2
        y: primaryPoint.y - height/2
        rotation: -mapObject.rotation
    }

    TileBonusIndicator {
        source: "qrc:/img/shield.png"
        visible: mapObject.tileData && mapObject.tileData.BonusTypes[mapObject.bonusSideIndex] === EngineEnums.DoubleShield
        x: secondaryPoint.x - width/2
        y: secondaryPoint.y - height/2
        rotation: -mapObject.rotation
    }

    TileBonusIndicator {
        source: "qrc:/img/wheat.png"
        visible: mapObject.tileData && mapObject.tileData.BonusTypes[mapObject.bonusSideIndex] === EngineEnums.Wheat
        x: primaryPoint.x - width/2
        y: primaryPoint.y - height/2
        rotation: -mapObject.rotation
    }

    TileBonusIndicator {
        source: "qrc:/img/barrel.png"
        visible: mapObject.tileData && mapObject.tileData.BonusTypes[mapObject.bonusSideIndex] === EngineEnums.Barrel
        x: primaryPoint.x - width/2
        y: primaryPoint.y - height/2
        rotation: -mapObject.rotation
    }

    TileBonusIndicator {
        source: "qrc:/img/cloth.png"
        visible: mapObject.tileData && mapObject.tileData.BonusTypes[mapObject.bonusSideIndex] === EngineEnums.Cloth
        x: primaryPoint.x - width/2
        y: primaryPoint.y - height/2
        rotation: -mapObject.rotation
    }

    Rectangle {
        width: 20
        height: 40
        radius: 10
        x: primaryPoint.x - width/2
        y: primaryPoint.y - height/2
        visible: mapObject.tileData && mapObject.tileData.BonusTypes[mapObject.bonusSideIndex] === EngineEnums.RoadLake
        color: "lightblue"
        border.width: 2
        border.color: "blue"
    }

    Rectangle {
        width: 20
        height: 20
        color: "white"
        x: primaryPoint.x - width/2
        y: primaryPoint.y - height/2
        visible: mapObject.tileData && mapObject.tileData.BonusTypes[mapObject.bonusSideIndex] === EngineEnums.TownCenter

        Text {
            anchors.centerIn: parent
            text: "Ц"
        }
    }
}
