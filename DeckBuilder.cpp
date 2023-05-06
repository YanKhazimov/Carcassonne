#include "DeckBuilder.h"
#include "ObjectManager.h"

#define X_(i,n) for(int i = 0; i < n; ++i)

DeckBuilder::DeckBuilder()
{
}

void DeckBuilder::BuildStandardDeck(ObjectManager &objectManager, std::list<Tile> &tiles)
{
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "18.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateMonastery(), { {2, 2} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } }
                       }, "0.jpg", 0);
    X_(i, 3)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "1.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {0, 4}, {4, 4} } },
                           { objectManager.GenerateTown(1), { {0, 2} } },
                           { objectManager.GenerateTown(1), { {2, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "2.jpg", 0);
    X_(i, 2)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateTown(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } }
                       }, "3.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {4, 0}, {0, 4}, {4, 4} } },
                           { objectManager.GenerateTown(1), { {2, 0} } },
                           { objectManager.GenerateTown(1), { {0, 2} } },
                           { objectManager.GenerateTown(1), { {2, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "4.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::Cloth), { {0, 0}, {2, 0}, {4, 0}, {0, 2}, {0, 4}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateField(), { {1, 4} } },
                           { objectManager.GenerateField(), { {3, 4} } },
                           { objectManager.GenerateField(), { {4, 1} } },
                           { objectManager.GenerateField(), { {4, 3} } }
                       }, "5.jpg", 0);
    X_(i, 2)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::Shield), { {0, 0}, {2, 0}, {0, 2} } },
                           { objectManager.GenerateRoad(2), { {2, 4}, {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       }, "6.jpg", 180);
    X_(i, 5)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(1), { {0, 2} } },
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4} } }
                       }, "7.jpg", 0);
    X_(i, 9)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateRoad(2), { {2, 4}, {4, 2} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {0, 2}, {0, 4} } }
                       }, "8.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {4, 4} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
                           { objectManager.GenerateRoad(2), { {2, 0}, {4, 2} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } }
                       }, "9.jpg", 0);
    X_(i, 4)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } }
                       }, "10.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateField(), { {0, 4}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Cloth), { {2, 0}, {4, 0}, {4, 2} } },
                           { objectManager.GenerateTown(1), { {2, 4} } }
                       }, "11.jpg", 0);
    X_(i, 4)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2), { {0, 2}, {0, 4}, {2, 4} } }
                       }, "12.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0}, {0, 4}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Cloth), { {0, 0}, {2, 0}, {0, 2} } },
                           { objectManager.GenerateTown(1), { {2, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "13.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::Shield), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateTown(2), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       }, "14.jpg", 0);
    X_(i, 3)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(3), { {0, 0}, {2, 0}, {0, 2}, {0, 4}, {2, 4} } }
                       }, "15.jpg", 0);
    X_(i, 4)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateMonastery(), { {2, 2} } },
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4}, {0, 2} } }
                       }, "16.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::Cloth), { {0, 0}, {0, 2}, {2, 0} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } }
                       }, "17.jpg", 0);
    X_(i, 3) // 4th is the start one
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "18.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::Shield), { {2, 0}, {2, 2}, {2, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       }, "19.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::Barrel), { {2, 0}, {4, 0}, {2, 2}, {4, 2}, {0, 4}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 3} } },
                           { objectManager.GenerateField(), { {2, 4} } }
                       }, "20.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateField(), { {0, 4}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Wheat), { {2, 0}, {4, 0}, {4, 2} } },
                           { objectManager.GenerateTown(1), { {2, 4} } }
                       }, "21.jpg", 90);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(4, QmlEnums::Shield), { {0, 0}, {2, 0}, {4, 0}, {0, 2}, {2, 2}, {4, 2}, {0, 4}, {2, 4}, {4, 4} } }
                       }, "22.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Shield), { {0, 2}, {0, 4}, {2, 4} } }
                       }, "23.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateTown(3), { {0, 0}, {2, 0}, {0, 2}, {2, 2}, {0, 4}, {2, 4} } }
                       }, "24.jpg", 180);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateTown(2), { {2, 0}, {4, 0}, {4, 2} } }
                       }, "25.jpg", 0);
    X_(i, 2)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateTown(3, QmlEnums::Shield), { {0, 0}, {2, 0}, {0, 2}, {2, 2}, {0, 4}, {2, 4} } }
                       }, "26.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2), { {2, 0}, {2, 4} } }
                       }, "27.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Cloth), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "28.jpg", 90);
    X_(i, 2)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(4, QmlEnums::TownCenter), { {0, 0}, {0, 2}, {0, 4}, {2, 0}, {2, 4}, {4, 0}, {4, 2}, {4, 4} } }
                       }, "29.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Barrel), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "30.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateTown(3, QmlEnums::Barrel), { {0, 0}, {2, 0}, {0, 2}, {0, 4}, {2, 2}, {2, 4} } }
                       }, "31.jpg", 90);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0}, {0, 4} } },
                           { objectManager.GenerateTown(2), { {0, 0}, {2, 0}, {0, 2} } },
                           { objectManager.GenerateTown(2, QmlEnums::Barrel), { {2, 4}, {4, 4}, {4, 2} } }
                       }, "32.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Barrel), { {2, 0}, {2, 4} } }
                       }, "33.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateTown(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } }
                       }, "34.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateTown(1, QmlEnums::Shield), { {2, 0} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } }
                       }, "35.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateTown(2), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       }, "36.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4}, {2, 0}, {4, 0} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateTown(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateTown(1), { {0, 2} } }
                       }, "37.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(3, QmlEnums::Shield), { {0, 0}, {2, 0}, {0, 2}, {0, 4}, {2, 4} } }
                       }, "38.jpg", 90);
    X_(i, 2)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Shield), { {2, 0}, {2, 4} } }
                       }, "39.jpg", 90);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(1), { {0, 2} } },
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } }
                       }, "40.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2), { {0, 0}, {2, 0}, {4, 0}, {0, 2}, {0, 4}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateField(), { {1, 4} } },
                           { objectManager.GenerateField(), { {3, 4} } },
                           { objectManager.GenerateField(), { {4, 1} } },
                           { objectManager.GenerateField(), { {4, 3} } }
                       }, "41.jpg", 90);
    X_(i, 2)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateMonastery(), { {2, 2} } },
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 4}, {2, 4}, {0, 4}, {0, 2} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } }
                       }, "42.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateField(), { {0, 0}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Barrel), { {2, 0}, {2, 4} } }
                       }, "43.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateMonastery(), { {2, 2} } },
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } }
                       }, "44.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateField(), { {0, 0}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Wheat), { {2, 0}, {2, 4} } }
                       }, "45.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::Barrel), { {2, 0}, {2, 2}, {2, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       }, "46.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateRoad(2, QmlEnums::RoadLake), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}  } }
                       }, "47.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 4} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Shield), { {2, 0}, {2, 4} } }
                       }, "48.jpg", 180);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } }
                       }, "49.jpg", 0);
    X_(i, 8)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}  } }
                       }, "50.jpg", 0);
    X_(i, 3)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 4} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "51.jpg", 0);
    X_(i, 3)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2), { {0, 0}, {2, 0}, {0, 2} } },
                           { objectManager.GenerateRoad(2), { {2, 4}, {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       }, "52.jpg", 180);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(3, QmlEnums::Wheat), { {0, 0}, {2, 0}, {0, 2}, {0, 4}, {2, 4} } }
                       }, "53.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {2, 4} } },
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2} } },
                           { objectManager.GenerateTown(1), { {0, 2}, {0, 4}, {4, 4} } }
                       }, "54.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(1), { {4, 2} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {2, 0} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } }
                       }, "55.jpg", 0);
    X_(i, 3)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4}, {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(1), { {2, 0} } },
                           { objectManager.GenerateTown(1), { {2, 4} } }
                       }, "56.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Wheat), { {0, 2}, {0, 4}, {2, 4} } }
                       }, "57.jpg", 180);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(4, QmlEnums::DoubleShield), { {0, 0}, {2, 0}, {4, 0}, {2, 4}, {0, 2}, {4, 2}, {0, 4}, {4, 4} } }
                       }, "58.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateTown(2, QmlEnums::Barrel), { {0, 2}, {0, 4}, {2, 4} } }
                       }, "59.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateRoad(3), { {0, 2}, {2, 0}, {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } }
                       }, "60.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateTown(2, QmlEnums::Wheat), { {0, 0}, {0, 2}, {2, 0} } }
                       }, "61.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::Shield), { {0, 0}, {2, 0}, {0, 2} } },
                           { objectManager.GenerateRoad(2, QmlEnums::RoadLake), { {2, 4}, {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       }, "62.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(1), { {0, 2} } },
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } }
                       }, "63.jpg", 180);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::Wheat), { {0, 0}, {2, 0}, {4, 0}, {0, 2}, {0, 4}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateField(), { {2, 4} } },
                           { objectManager.GenerateField(), { {4, 1} } },
                           { objectManager.GenerateField(), { {4, 3} } }
                       }, "64.jpg", 180);
    X_(i, 2)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } },
                           { objectManager.GenerateTown(1), { {2, 0} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "65.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 4}, {2, 0}, {2, 4}, {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateMonastery(), { {2, 2} } },
                           { objectManager.GenerateTown(1), { {0, 2} } }
                       }, "66.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateRoad(2, QmlEnums::RoadLake), { {2, 4}, {4, 2} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {0, 2}, {0, 4} } }
                       }, "67.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Barrel), { {0, 2}, {0, 4}, {2, 4} } }
                       }, "68.jpg", 180);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Shield), { {0, 2}, {0, 4}, {2, 4} } },
                           { objectManager.GenerateTown(1), { {2, 0} } }
                       }, "69.jpg", 180);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateMonastery(), { {2, 2} } },
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } }
                       }, "70.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "71.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 2} } },
                           { objectManager.GenerateField(), { {2, 0} } },
                           { objectManager.GenerateField(), { {4, 2} } },
                           { objectManager.GenerateTown(1, QmlEnums::Shield), { {0, 0}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } }
                       }, "72.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       }, "73.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateRoad(1, QmlEnums::RoadLake), { {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateTown(2), { {0, 0}, {0, 2}, {2, 0} } }
                       }, "74.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {2, 0} } },
                           { objectManager.GenerateField(), { {0, 4}, {4, 0} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "75.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 4} } },
                           { objectManager.GenerateRoad(2, QmlEnums::RoadLake), { {0, 2}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "76.jpg", 180);
    X_(i, 3)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0}, {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {2, 0} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "77.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } }
                       }, "78.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1, QmlEnums::RoadLake), { {4, 2} } }
                       }, "79.jpg", 90);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateTown(1), { {2, 0} } },
                           { objectManager.GenerateTown(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } }
                       }, "80.jpg", 0);
}

void DeckBuilder::BuildExampleDeck(ObjectManager& objectManager, std::list<Tile>& tiles)
{
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "18.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } }
                       }, "78.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateTown(1), { {2, 0} } },
                           { objectManager.GenerateTown(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } }
                       }, "80.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "1.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateMonastery(), { {2, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } }
                       }, "70.jpg", 180);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4}, {2, 0}, {4, 0} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateTown(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateTown(1), { {0, 2} } }
                       }, "37.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::Shield), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateTown(2, QmlEnums::Cloth), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       }, "14.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "18.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 4} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::Shield), { {2, 0}, {2, 4} } }
                       }, "48.jpg", 180);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(4, QmlEnums::DoubleShield), { {0, 0}, {2, 0}, {4, 0}, {2, 4}, {0, 2}, {4, 2}, {0, 4}, {4, 4} } }
                       }, "58.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateTown(2, QmlEnums::Wheat), { {0, 0}, {0, 2}, {2, 0} } }
                       }, "61.jpg", 0);

    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2), { {0, 2}, {0, 4}, {2, 4} } }
                       }, "12.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateRoad(3), { {0, 2}, {2, 0}, {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } }
                       }, "60.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } }
                       }, "49.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 2} } },
                           { objectManager.GenerateField(), { {2, 0} } },
                           { objectManager.GenerateField(), { {4, 2} } },
                           { objectManager.GenerateTown(1, QmlEnums::Shield), { {0, 0}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } }
                       }, "72.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 2} } },
                           { objectManager.GenerateField(), { {2, 0} } },
                           { objectManager.GenerateField(), { {4, 2} } },
                           { objectManager.GenerateTown(1, QmlEnums::Shield), { {0, 0}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } }
                       }, "72.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "71.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 4} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "51.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } }
                       }, "49.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {4, 4} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
                           { objectManager.GenerateRoad(2), { {2, 0}, {4, 2} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } }
                       }, "9.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       }, "73.jpg", 0);
}
