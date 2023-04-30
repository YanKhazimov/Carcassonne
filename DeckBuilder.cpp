#include "DeckBuilder.h"
#include "ObjectManager.h"

#define _X_(i,n) for(int i = 0; i < n; ++i)

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
    _X_(i, 3)
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
    _X_(i, 2)
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
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Cloth), { {0, 0}, {2, 0}, {4, 0}, {0, 2}, {0, 4}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateField(), { {1, 4} } },
                           { objectManager.GenerateField(), { {3, 4} } },
                           { objectManager.GenerateField(), { {4, 1} } },
                           { objectManager.GenerateField(), { {4, 3} } }
                       }, "5.jpg", 0);
    _X_(i, 2)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Shield), { {0, 0}, {2, 0}, {0, 2} } },
                           { objectManager.GenerateRoad(2), { {2, 4}, {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       }, "6.jpg", 180);
    _X_(i, 5)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(1), { {0, 2} } },
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4} } }
                       }, "7.jpg", 0);
    _X_(i, 9)
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
    _X_(i, 4)
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
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Cloth), { {2, 0}, {4, 0}, {4, 2} } },
                           { objectManager.GenerateTown(1), { {2, 4} } }
                       }, "11.jpg", 0);
    _X_(i, 4)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2), { {0, 2}, {0, 4}, {2, 4} } }
                       }, "12.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0}, {0, 4}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Cloth), { {0, 0}, {2, 0}, {0, 2} } },
                           { objectManager.GenerateTown(1), { {2, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "13.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Shield), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Cloth), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       }, "14.jpg", 0);
    _X_(i, 3)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(3), { {0, 0}, {2, 0}, {0, 2}, {0, 4}, {2, 4} } }
                       }, "15.jpg", 0);
    _X_(i, 4)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateMonastery(), { {2, 2} } },
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4}, {0, 2} } }
                       }, "16.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Cloth), { {0, 0}, {0, 2}, {2, 0} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } }
                       }, "17.jpg", 0);
    _X_(i, 3) // 4th is the start one
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "18.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Shield), { {2, 0}, {2, 2}, {2, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       }, "19.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Barrel), { {2, 0}, {4, 0}, {4, 2}, {0, 4}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 3} } },
                           { objectManager.GenerateField(), { {2, 4} } }
                       }, "20.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateField(), { {0, 4}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Wheat), { {2, 0}, {4, 0}, {4, 2} } },
                           { objectManager.GenerateTown(1), { {2, 4} } }
                       }, "21.jpg", 90);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(4, QmlEnums::BonusType::Shield), { {0, 0}, {2, 0}, {4, 0}, {0, 2}, {2, 2}, {4, 2}, {0, 4}, {2, 4}, {4, 4} } }
                       }, "22.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Shield), { {0, 2}, {0, 4}, {2, 4} } }
                       }, "23.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateTown(3), { {0, 0}, {2, 0}, {0, 2}, {0, 4}, {2, 4} } }
                       }, "24.jpg", 180);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateTown(2), { {2, 0}, {4, 0}, {4, 2} } }
                       }, "25.jpg", 0);
    _X_(i, 2)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateTown(3, QmlEnums::BonusType::Shield), { {0, 0}, {2, 0}, {0, 2}, {0, 4}, {2, 4} } }
                       }, "26.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2), { {2, 0}, {2, 4} } }
                       }, "27.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Cloth), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "28.jpg", 90);
    _X_(i, 2)
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(4, QmlEnums::BonusType::TownCenter), { {0, 0}, {0, 2}, {0, 4}, {2, 0}, {2, 4}, {4, 0}, {4, 2}, {4, 4} } }
                       }, "29.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Barrel), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "30.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateTown(3, QmlEnums::BonusType::Barrel), { {0, 0}, {2, 0}, {0, 2}, {0, 4}, {2, 4} } }
                       }, "31.jpg", 90);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0}, {0, 4} } },
                           { objectManager.GenerateTown(2), { {0, 0}, {2, 0}, {0, 2} } },
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Barrel), { {2, 4}, {4, 4}, {4, 2} } }
                       }, "32.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Barrel), { {2, 0}, {2, 4} } }
                       }, "33.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {4, 0}, {0, 4} } },
                           { objectManager.GenerateTown(2), { {0, 0}, {2, 0}, {0, 2} } },
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Barrel), { {2, 4}, {4, 4}, {4, 2} } }
                       }, "32.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateTown(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } }
                       }, "34.jpg", 0);
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
                           { objectManager.GenerateField(), { {0, 0}, {0, 4} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Shield), { {2, 0}, {2, 4} } }
                       }, "48.jpg", 180);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } }
                       }, "49.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 4} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       }, "51.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(4, QmlEnums::BonusType::DoubleShield), { {0, 0}, {2, 0}, {4, 0}, {2, 4}, {0, 2}, {4, 2}, {0, 4}, {4, 4} } }
                       }, "58.jpg", 0);
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
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Wheat), { {0, 0}, {0, 2}, {2, 0} } }
                       }, "61.jpg", 0);
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
                           { objectManager.GenerateTown(1, QmlEnums::BonusType::Shield), { {0, 0}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } }
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
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Shield), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Cloth), { {2, 0}, {2, 4} } },
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
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Shield), { {2, 0}, {2, 4} } }
                       }, "48.jpg", 180);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(4, QmlEnums::BonusType::DoubleShield), { {0, 0}, {2, 0}, {4, 0}, {2, 4}, {0, 2}, {4, 2}, {0, 4}, {4, 4} } }
                       }, "58.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateTown(2, QmlEnums::BonusType::Wheat), { {0, 0}, {0, 2}, {2, 0} } }
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
                           { objectManager.GenerateTown(1, QmlEnums::BonusType::Shield), { {0, 0}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } }
                       }, "72.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 2} } },
                           { objectManager.GenerateField(), { {2, 0} } },
                           { objectManager.GenerateField(), { {4, 2} } },
                           { objectManager.GenerateTown(1, QmlEnums::BonusType::Shield), { {0, 0}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } }
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
