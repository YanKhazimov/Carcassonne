#include "DeckBuilder.h"
#include "ObjectManager.h"
#include <QDir>
#include <QDebug>

#define X_(i,n) for(int i = 0; i < n; ++i)

DeckBuilder::DeckBuilder()
{
}

std::list<Tile> DeckBuilder::BuildDeck(ObjectManager &objectManager, const QString& imagesFolder, const QString& imageFormat)
{
    std::list<Tile> tiles;

    auto addTile = [&imagesFolder, &imageFormat, &tiles]
            (const std::vector<std::pair<TileObject, TileData::ObjectLocation>>& objects, const QString& filename, int imageRotation)
    {
        QString imagePath = QString("%1/%2/%3.%4").arg(QDir::currentPath(), imagesFolder, filename, imageFormat);
        if (QFileInfo::exists(imagePath))
        {
            tiles.emplace_back(objects, QUrl::fromLocalFile(imagePath), imageRotation);
        }
        else
        {
            qWarning() << QString("File %1 is missing, excluding from the deck.").arg(imagePath);
        }
    };

    addTile({
                { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
                { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                { objectManager.GenerateTown(1), { {4, 2} } }
            }, "18", 270);
    addTile({
                { objectManager.GenerateMonastery(), { {2, 2} } },
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {0, 4} } },
                { objectManager.GenerateField(), { {4, 4} } },
                { objectManager.GenerateRoad(1), { {0, 2} } },
                { objectManager.GenerateRoad(1), { {2, 0} } },
                { objectManager.GenerateRoad(1), { {2, 4} } },
                { objectManager.GenerateRoad(1), { {4, 2} } }
            }, "0", 0);
    X_(i, 3)
            addTile({
                        { objectManager.GenerateField(), { {0, 0} } },
                        { objectManager.GenerateField(), { {0, 4} } },
                        { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                        { objectManager.GenerateRoad(1), { {0, 2} } },
                        { objectManager.GenerateRoad(1), { {2, 0} } },
                        { objectManager.GenerateRoad(1), { {2, 4} } },
                        { objectManager.GenerateTown(1), { {4, 2} } }
                    }, "1", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {0, 4}, {4, 4} } },
                { objectManager.GenerateTown(1), { {0, 2} } },
                { objectManager.GenerateTown(1), { {2, 4} } },
                { objectManager.GenerateTown(1), { {4, 2} } }
            }, "2", 0);
    X_(i, 2)
            addTile({
                        { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4} } },
                        { objectManager.GenerateField(), { {0, 0} } },
                        { objectManager.GenerateTown(1), { {0, 2} } },
                        { objectManager.GenerateRoad(1), { {2, 0} } }
                    }, "3", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {4, 0}, {0, 4}, {4, 4} } },
                { objectManager.GenerateTown(1), { {2, 0} } },
                { objectManager.GenerateTown(1), { {0, 2} } },
                { objectManager.GenerateTown(1), { {2, 4} } },
                { objectManager.GenerateTown(1), { {4, 2} } }
            }, "4", 0);
    addTile({
                { objectManager.GenerateTown(2, QmlEnums::Cloth), { {0, 0}, {2, 0}, {4, 0}, {0, 2}, {0, 4}, {4, 4} } },
                { objectManager.GenerateRoad(1), { {2, 4} } },
                { objectManager.GenerateRoad(1), { {4, 2} } },
                { objectManager.GenerateField(), { {1, 4} } },
                { objectManager.GenerateField(), { {3, 4} } },
                { objectManager.GenerateField(), { {4, 1} } },
                { objectManager.GenerateField(), { {4, 3} } }
            }, "5", 0);
    X_(i, 2)
            addTile({
                        { objectManager.GenerateTown(2, QmlEnums::Shield), { {0, 0}, {2, 0}, {0, 2} } },
                        { objectManager.GenerateRoad(2), { {2, 4}, {4, 2} } },
                        { objectManager.GenerateField(), { {4, 0}, {0, 4} } },
                        { objectManager.GenerateField(), { {4, 4} } }
                    }, "6", 180);
    X_(i, 5)
            addTile({
                        { objectManager.GenerateTown(1), { {0, 2} } },
                        { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4} } }
                    }, "7", 0);
    X_(i, 9)
            addTile({
                        { objectManager.GenerateRoad(2), { {2, 4}, {4, 2} } },
                        { objectManager.GenerateField(), { {4, 4} } },
                        { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {0, 2}, {0, 4} } }
                    }, "8", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {4, 4} } },
                { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
                { objectManager.GenerateRoad(2), { {2, 0}, {4, 2} } },
                { objectManager.GenerateField(), { {0, 4} } },
                { objectManager.GenerateField(), { {4, 0} } }
            }, "9", 0);
    X_(i, 4)
            addTile({
                        { objectManager.GenerateField(), { {0, 0} } },
                        { objectManager.GenerateField(), { {4, 0} } },
                        { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                        { objectManager.GenerateRoad(1), { {0, 2} } },
                        { objectManager.GenerateRoad(1), { {2, 0} } },
                        { objectManager.GenerateRoad(1), { {4, 2} } }
                    }, "10", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateRoad(1), { {0, 2} } },
                { objectManager.GenerateField(), { {0, 4}, {4, 4} } },
                { objectManager.GenerateTown(2, QmlEnums::Cloth), { {2, 0}, {4, 0}, {4, 2} } },
                { objectManager.GenerateTown(1), { {2, 4} } }
            }, "11", 0);
    X_(i, 4)
            addTile({
                        { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                        { objectManager.GenerateTown(2), { {0, 2}, {0, 4}, {2, 4} } }
                    }, "12", 0);
    addTile({
                { objectManager.GenerateField(), { {4, 0}, {0, 4}, {4, 4} } },
                { objectManager.GenerateTown(2, QmlEnums::Cloth), { {0, 0}, {2, 0}, {0, 2} } },
                { objectManager.GenerateTown(1), { {2, 4} } },
                { objectManager.GenerateTown(1), { {4, 2} } }
            }, "13", 0);
    addTile({
                { objectManager.GenerateTown(2, QmlEnums::Shield), { {0, 2}, {4, 2} } },
                { objectManager.GenerateTown(2), { {2, 0}, {2, 4} } },
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateField(), { {0, 4} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {4, 4} } }
            }, "14", 0);
    X_(i, 3)
            addTile({
                        { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                        { objectManager.GenerateTown(3), { {0, 0}, {2, 0}, {0, 2}, {0, 4}, {2, 4} } }
                    }, "15", 0);
    X_(i, 4)
            addTile({
                        { objectManager.GenerateMonastery(), { {2, 2} } },
                        { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4}, {0, 2} } }
                    }, "16", 0);
    addTile({
                { objectManager.GenerateTown(2, QmlEnums::Cloth), { {0, 0}, {0, 2}, {2, 0} } },
                { objectManager.GenerateRoad(1), { {2, 4} } },
                { objectManager.GenerateField(), { {0, 4} } },
                { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } }
            }, "17", 0);
    X_(i, 3) // 4th is the start one
            addTile({
                        { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                        { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
                        { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                        { objectManager.GenerateTown(1), { {4, 2} } }
                    }, "18", 270);
    addTile({
                { objectManager.GenerateTown(2, QmlEnums::Shield), { {2, 0}, {2, 2}, {2, 4} } },
                { objectManager.GenerateRoad(1), { {0, 2} } },
                { objectManager.GenerateRoad(1), { {4, 2} } },
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {0, 4} } },
                { objectManager.GenerateField(), { {4, 4} } }
            }, "19", 0);
    addTile({
                { objectManager.GenerateTown(2, QmlEnums::Barrel), { {2, 0}, {4, 0}, {2, 2}, {4, 2}, {0, 4}, {4, 4} } },
                { objectManager.GenerateRoad(1), { {0, 2} } },
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateField(), { {0, 3} } },
                { objectManager.GenerateField(), { {2, 4} } }
            }, "20", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateRoad(1), { {0, 2} } },
                { objectManager.GenerateField(), { {0, 4}, {4, 4} } },
                { objectManager.GenerateTown(2, QmlEnums::Wheat), { {2, 0}, {4, 0}, {4, 2} } },
                { objectManager.GenerateTown(1), { {2, 4} } }
            }, "21", 90);
    addTile({
                { objectManager.GenerateTown(4, QmlEnums::Shield), { {0, 0}, {2, 0}, {4, 0}, {0, 2}, {2, 2}, {4, 2}, {0, 4}, {2, 4}, {4, 4} } }
            }, "22", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                { objectManager.GenerateTown(2, QmlEnums::Shield), { {0, 2}, {0, 4}, {2, 4} } }
            }, "23", 0);
    addTile({
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {4, 4} } },
                { objectManager.GenerateRoad(1), { {4, 2} } },
                { objectManager.GenerateTown(3), { {0, 0}, {2, 0}, {0, 2}, {2, 2}, {0, 4}, {2, 4} } }
            }, "24", 180);
    addTile({
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateRoad(1), { {0, 2} } },
                { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                { objectManager.GenerateTown(2), { {2, 0}, {4, 0}, {4, 2} } }
            }, "25", 0);
    X_(i, 2)
            addTile({
                        { objectManager.GenerateField(), { {4, 0} } },
                        { objectManager.GenerateField(), { {4, 4} } },
                        { objectManager.GenerateRoad(1), { {4, 2} } },
                        { objectManager.GenerateTown(3, QmlEnums::Shield), { {0, 0}, {2, 0}, {0, 2}, {2, 2}, {0, 4}, {2, 4} } }
                    }, "26", 270);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                { objectManager.GenerateTown(2), { {2, 0}, {2, 4} } }
            }, "27", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                { objectManager.GenerateTown(2, QmlEnums::Cloth), { {2, 0}, {2, 4} } },
                { objectManager.GenerateTown(1), { {4, 2} } }
            }, "28", 90);
    X_(i, 2)
            addTile({
                        { objectManager.GenerateTown(4, QmlEnums::TownCenter), { {0, 0}, {0, 2}, {0, 4}, {2, 0}, {2, 4}, {4, 0}, {4, 2}, {4, 4} } }
                    }, "29", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                { objectManager.GenerateTown(2, QmlEnums::Barrel), { {2, 0}, {2, 4} } },
                { objectManager.GenerateTown(1), { {4, 2} } }
            }, "30", 270);
    addTile({
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {4, 4} } },
                { objectManager.GenerateRoad(1), { {4, 2} } },
                { objectManager.GenerateTown(3, QmlEnums::Barrel), { {0, 0}, {2, 0}, {0, 2}, {0, 4}, {2, 2}, {2, 4} } }
            }, "31", 90);
    addTile({
                { objectManager.GenerateField(), { {4, 0}, {0, 4} } },
                { objectManager.GenerateTown(2), { {0, 0}, {2, 0}, {0, 2} } },
                { objectManager.GenerateTown(2, QmlEnums::Barrel), { {2, 4}, {4, 4}, {4, 2} } }
            }, "32", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                { objectManager.GenerateTown(2, QmlEnums::Barrel), { {2, 0}, {2, 4} } }
            }, "33", 270);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                { objectManager.GenerateField(), { {0, 4} } },
                { objectManager.GenerateTown(1), { {0, 2} } },
                { objectManager.GenerateRoad(1), { {2, 4} } }
            }, "34", 0);
    addTile({
                { objectManager.GenerateTown(2), { {0, 2}, {4, 2} } },
                { objectManager.GenerateTown(1, QmlEnums::Shield), { {2, 0} } },
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                { objectManager.GenerateField(), { {4, 0} } }
            }, "35", 0);
    addTile({
                { objectManager.GenerateTown(2), { {0, 2}, {4, 2} } },
                { objectManager.GenerateTown(2), { {2, 0}, {2, 4} } },
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateField(), { {0, 4} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {4, 4} } }
            }, "36", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4}, {2, 0}, {4, 0} } },
                { objectManager.GenerateRoad(1), { {4, 2} } },
                { objectManager.GenerateField(), { {4, 4} } },
                { objectManager.GenerateTown(1), { {2, 4} } },
                { objectManager.GenerateRoad(1), { {2, 0} } },
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateTown(1), { {0, 2} } }
            }, "37", 0);
    addTile({
                { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                { objectManager.GenerateTown(3, QmlEnums::Shield), { {0, 0}, {2, 0}, {0, 2}, {0, 4}, {2, 4} } }
            }, "38", 90);
    X_(i, 2)
            addTile({
                        { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                        { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                        { objectManager.GenerateTown(2, QmlEnums::Shield), { {2, 0}, {2, 4} } }
                    }, "39", 90);
    addTile({
                { objectManager.GenerateTown(1), { {0, 2} } },
                { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateRoad(1), { {2, 0} } },
                { objectManager.GenerateRoad(1), { {4, 2} } }
            }, "40", 0);
    addTile({
                { objectManager.GenerateTown(2), { {0, 0}, {2, 0}, {4, 0}, {0, 2}, {0, 4}, {4, 4} } },
                { objectManager.GenerateRoad(1), { {2, 4} } },
                { objectManager.GenerateRoad(1), { {4, 2} } },
                { objectManager.GenerateField(), { {1, 4} } },
                { objectManager.GenerateField(), { {3, 4} } },
                { objectManager.GenerateField(), { {4, 1} } },
                { objectManager.GenerateField(), { {4, 3} } }
            }, "41", 90);
    X_(i, 2)
            addTile({
                        { objectManager.GenerateMonastery(), { {2, 2} } },
                        { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 4}, {2, 4}, {0, 4}, {0, 2} } },
                        { objectManager.GenerateRoad(1), { {4, 2} } }
                    }, "42", 0);
    addTile({
                { objectManager.GenerateRoad(1), { {0, 2} } },
                { objectManager.GenerateField(), { {0, 0}, {0, 4} } },
                { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                { objectManager.GenerateTown(2, QmlEnums::Barrel), { {2, 0}, {2, 4} } }
            }, "43", 0);
    addTile({
                { objectManager.GenerateMonastery(), { {2, 2} } },
                { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                { objectManager.GenerateRoad(1), { {2, 0} } },
                { objectManager.GenerateRoad(1), { {2, 4} } }
            }, "44", 0);
    addTile({
                { objectManager.GenerateRoad(1), { {0, 2} } },
                { objectManager.GenerateField(), { {0, 0}, {0, 4} } },
                { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                { objectManager.GenerateTown(2, QmlEnums::Wheat), { {2, 0}, {2, 4} } }
            }, "45", 270);
    addTile({
                { objectManager.GenerateTown(2, QmlEnums::Barrel), { {2, 0}, {2, 2}, {2, 4} } },
                { objectManager.GenerateRoad(1), { {0, 2} } },
                { objectManager.GenerateRoad(1), { {4, 2} } },
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {0, 4} } },
                { objectManager.GenerateField(), { {4, 4} } }
            }, "46", 0);
    addTile({
                { objectManager.GenerateRoad(2, QmlEnums::RoadLake), { {0, 2}, {4, 2} } },
                { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}  } }
            }, "47", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {0, 4} } },
                { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {4, 4} } },
                { objectManager.GenerateTown(2, QmlEnums::Shield), { {2, 0}, {2, 4} } }
            }, "48", 180);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4} } },
                { objectManager.GenerateRoad(1), { {0, 2} } }
            }, "49", 0);
    X_(i, 8)
            addTile({
                        { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
                        { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                        { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}  } }
                    }, "50", 90);
    X_(i, 3)
            addTile({
                        { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 4} } },
                        { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
                        { objectManager.GenerateField(), { {0, 4} } },
                        { objectManager.GenerateTown(1), { {4, 2} } }
                    }, "51", 0);
    X_(i, 3)
            addTile({
                        { objectManager.GenerateTown(2), { {0, 0}, {2, 0}, {0, 2} } },
                        { objectManager.GenerateRoad(2), { {2, 4}, {4, 2} } },
                        { objectManager.GenerateField(), { {4, 0}, {0, 4} } },
                        { objectManager.GenerateField(), { {4, 4} } }
                    }, "52", 180);
    addTile({
                { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                { objectManager.GenerateTown(3, QmlEnums::Wheat), { {0, 0}, {2, 0}, {0, 2}, {0, 4}, {2, 4} } }
            }, "53", 0);
    addTile({
                { objectManager.GenerateField(), { {2, 4} } },
                { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2} } },
                { objectManager.GenerateTown(1), { {0, 2}, {0, 4}, {4, 4} } }
            }, "54", 270);
    addTile({
                { objectManager.GenerateTown(1), { {4, 2} } },
                { objectManager.GenerateRoad(2), { {0, 2}, {2, 0} } },
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } }
            }, "55", 0);
    X_(i, 3)
            addTile({
                        { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4}, {4, 0}, {4, 2}, {4, 4} } },
                        { objectManager.GenerateTown(1), { {2, 0} } },
                        { objectManager.GenerateTown(1), { {2, 4} } }
                    }, "56", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                { objectManager.GenerateTown(2, QmlEnums::Wheat), { {0, 2}, {0, 4}, {2, 4} } }
            }, "57", 180);
    addTile({
                { objectManager.GenerateTown(4, QmlEnums::DoubleShield), { {0, 0}, {2, 0}, {4, 0}, {2, 4}, {0, 2}, {4, 2}, {0, 4}, {4, 4} } }
            }, "58", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {4, 4} } },
                { objectManager.GenerateRoad(1), { {2, 0} } },
                { objectManager.GenerateRoad(1), { {4, 2} } },
                { objectManager.GenerateTown(2, QmlEnums::Barrel), { {0, 2}, {0, 4}, {2, 4} } }
            }, "59", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateRoad(3), { {0, 2}, {2, 0}, {4, 2} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } }
            }, "60", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                { objectManager.GenerateRoad(1), { {4, 2} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateTown(2, QmlEnums::Wheat), { {0, 0}, {0, 2}, {2, 0} } }
            }, "61", 0);
    addTile({
                { objectManager.GenerateTown(2, QmlEnums::Shield), { {0, 0}, {2, 0}, {0, 2} } },
                { objectManager.GenerateRoad(2, QmlEnums::RoadLake), { {2, 4}, {4, 2} } },
                { objectManager.GenerateField(), { {4, 0}, {0, 4} } },
                { objectManager.GenerateField(), { {4, 4} } }
            }, "62", 0);
    addTile({
                { objectManager.GenerateTown(1), { {0, 2} } },
                { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0} } },
                { objectManager.GenerateRoad(1), { {4, 2} } }
            }, "63", 180);
    addTile({
                { objectManager.GenerateTown(2, QmlEnums::Wheat), { {0, 0}, {2, 0}, {4, 0}, {0, 2}, {0, 4}, {4, 4} } },
                { objectManager.GenerateRoad(1), { {4, 2} } },
                { objectManager.GenerateField(), { {2, 4} } },
                { objectManager.GenerateField(), { {4, 1} } },
                { objectManager.GenerateField(), { {4, 3} } }
            }, "64", 180);
    X_(i, 2)
            addTile({
                        { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } },
                        { objectManager.GenerateTown(1), { {2, 0} } },
                        { objectManager.GenerateTown(1), { {4, 2} } }
                    }, "65", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {0, 4}, {2, 0}, {2, 4}, {4, 0}, {4, 2}, {4, 4} } },
                { objectManager.GenerateMonastery(), { {2, 2} } },
                { objectManager.GenerateTown(1), { {0, 2} } }
            }, "66", 0);
    addTile({
                { objectManager.GenerateRoad(2, QmlEnums::RoadLake), { {2, 4}, {4, 2} } },
                { objectManager.GenerateField(), { {4, 4} } },
                { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {0, 2}, {0, 4} } }
            }, "67", 270);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                { objectManager.GenerateTown(2, QmlEnums::Barrel), { {0, 2}, {0, 4}, {2, 4} } }
            }, "68", 180);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {4, 0}, {4, 2}, {4, 4} } },
                { objectManager.GenerateTown(2, QmlEnums::Shield), { {0, 2}, {0, 4}, {2, 4} } },
                { objectManager.GenerateTown(1), { {2, 0} } }
            }, "69", 180);
    addTile({
                { objectManager.GenerateMonastery(), { {2, 2} } },
                { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {4, 4} } },
                { objectManager.GenerateRoad(1), { {2, 0} } },
                { objectManager.GenerateRoad(1), { {2, 4} } },
                { objectManager.GenerateRoad(1), { {4, 2} } }
            }, "70", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0} } },
                { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
                { objectManager.GenerateField(), { {0, 4} } },
                { objectManager.GenerateField(), { {4, 4} } },
                { objectManager.GenerateTown(1), { {4, 2} } }
            }, "71", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 2} } },
                { objectManager.GenerateField(), { {2, 0} } },
                { objectManager.GenerateField(), { {4, 2} } },
                { objectManager.GenerateTown(1, QmlEnums::Shield), { {0, 0}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } }
            }, "72", 0);
    addTile({
                { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
                { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateField(), { {0, 4} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {4, 4} } }
            }, "73", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                { objectManager.GenerateRoad(1, QmlEnums::RoadLake), { {4, 2} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateTown(2), { {0, 0}, {0, 2}, {2, 0} } }
            }, "74", 270);
    addTile({
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateRoad(2), { {0, 2}, {2, 0} } },
                { objectManager.GenerateField(), { {0, 4}, {4, 0} } },
                { objectManager.GenerateRoad(1), { {2, 4} } },
                { objectManager.GenerateField(), { {4, 4} } },
                { objectManager.GenerateTown(1), { {4, 2} } }
            }, "75", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 4} } },
                { objectManager.GenerateRoad(2, QmlEnums::RoadLake), { {0, 2}, {2, 4} } },
                { objectManager.GenerateField(), { {0, 4} } },
                { objectManager.GenerateTown(1), { {4, 2} } }
            }, "76", 180);
    X_(i, 3)
            addTile({
                        { objectManager.GenerateField(), { {4, 0}, {0, 4}, {2, 4}, {4, 4} } },
                        { objectManager.GenerateRoad(2), { {0, 2}, {2, 0} } },
                        { objectManager.GenerateField(), { {0, 0} } },
                        { objectManager.GenerateTown(1), { {4, 2} } }
                    }, "77", 270);
    addTile({
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {0, 4} } },
                { objectManager.GenerateField(), { {4, 4} } },
                { objectManager.GenerateRoad(1), { {0, 2} } },
                { objectManager.GenerateRoad(1), { {2, 0} } },
                { objectManager.GenerateRoad(1), { {2, 4} } },
                { objectManager.GenerateRoad(1), { {4, 2} } }
            }, "78", 0);
    addTile({
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                { objectManager.GenerateRoad(1), { {0, 2} } },
                { objectManager.GenerateRoad(1), { {2, 0} } },
                { objectManager.GenerateRoad(1, QmlEnums::RoadLake), { {4, 2} } }
            }, "79", 90);
    addTile({
                { objectManager.GenerateField(), { {0, 0} } },
                { objectManager.GenerateField(), { {4, 0} } },
                { objectManager.GenerateField(), { {0, 4} } },
                { objectManager.GenerateField(), { {4, 4} } },
                { objectManager.GenerateRoad(1), { {0, 2} } },
                { objectManager.GenerateTown(1), { {2, 0} } },
                { objectManager.GenerateTown(1), { {2, 4} } },
                { objectManager.GenerateRoad(1), { {4, 2} } }
            }, "80", 0);

    return tiles;
}

std::shared_ptr<Tile> DeckBuilder::createAbbeyTile(ObjectManager &objectManager, const QString &imagesFolder, const QString &imageFormat)
{
    QString imagePath = QString("%1/%2/%3.%4").arg(QDir::currentPath(), imagesFolder, "abbey", imageFormat);
    if (!QFileInfo::exists(imagePath))
    {
        qWarning() << QString("File %1 is missing, excluding from the deck.").arg(imagePath);
    }

    return std::shared_ptr<Tile>(new Tile({
                                      { objectManager.GenerateAbbey(),
                                        { {0, 0}, {0, 2}, {0, 4}, {2, 0}, {2, 2}, {2, 4}, {4, 0}, {4, 2}, {4, 4} } }
                                  },
                                  QUrl::fromLocalFile(imagePath), 0));
}
