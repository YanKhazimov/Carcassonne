#include "DeckBuilder.h"
#include "ObjectManager.h"

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
                       },
                       "18.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } }
                       },
                       "78.jpg", 0);
}

void DeckBuilder::BuildExampleDeck(ObjectManager& objectManager, std::list<Tile>& tiles)
{
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       },
                       "18.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } }
                       },
                       "78.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateTown(1), { {2, 0} } },
                           { objectManager.GenerateTown(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } }
                       },
                       "80.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       },
                       "1.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateMonastery(), { {2, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } },
                           { objectManager.GenerateRoad(1), { {2, 4} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } }
                       },
                       "70.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4}, {2, 0}, {4, 0} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateTown(1), { {2, 4} } },
                           { objectManager.GenerateRoad(1), { {2, 0} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateTown(1), { {0, 2} } }
                       },
                       "37.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2, BonusType::Shield), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateTown(2, BonusType::Cloth), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       },
                       "14.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
                           { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       },
                       "18.jpg", 270);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {0, 4} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateTown(2, BonusType::Shield), { {2, 0}, {2, 4} } }
                       },
                       "48.jpg", 180);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(4, BonusType::DoubleShield), { {0, 0}, {2, 0}, {4, 0}, {2, 4}, {0, 2}, {4, 2}, {0, 4}, {4, 4} } }
                       },
                       "58.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
                           { objectManager.GenerateRoad(1), { {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateTown(2, BonusType::Wheat), { {0, 0}, {0, 2}, {2, 0} } }
                       },
                       "61.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2), { {0, 2}, {0, 4}, {2, 4} } }
                       },
                       "12.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateRoad(3), { {0, 2}, {2, 0}, {4, 2} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } }
                       },
                       "60.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } }
                       },
                       "81.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 2} } },
                           { objectManager.GenerateField(), { {2, 0} } },
                           { objectManager.GenerateField(), { {4, 2} } },
                           { objectManager.GenerateTown(1, BonusType::Shield), { {0, 0}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } }
                       },
                       "72.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 2} } },
                           { objectManager.GenerateField(), { {2, 0} } },
                           { objectManager.GenerateField(), { {4, 2} } },
                           { objectManager.GenerateTown(1, BonusType::Shield), { {0, 0}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } }
                       },
                       "72.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       },
                       "71.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 4} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateTown(1), { {4, 2} } }
                       },
                       "51.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4} } },
                           { objectManager.GenerateRoad(1), { {0, 2} } }
                       },
                       "81.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {4, 4} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
                           { objectManager.GenerateRoad(2), { {2, 0}, {4, 2} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } }
                       },
                       "9.jpg", 0);
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       },
                       "73.jpg", 0);
}
