#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "TileObject.h"
#include <unordered_map>
#include <memory>
#include <vector>

class ObjectManager
{
    //! initial id -> { object, id of master object, slave objects }
    std::unordered_map<unsigned, std::tuple<std::shared_ptr<TileObject>, unsigned, std::vector<std::shared_ptr<TileObject>>>> mapObjects;
    unsigned objectCounter = 1;
    unsigned voidId;
    std::shared_ptr<TileObject> generateVoid();

    ObjectManager();
    static ObjectManager* m_instance;

public:
    static ObjectManager* instance();
    std::shared_ptr<TileObject> GenerateRoad(unsigned valency, QmlEnums::BonusType bonusType = QmlEnums::BonusType::None);
    std::shared_ptr<TileObject> GenerateTown(unsigned valency, QmlEnums::BonusType bonusType = QmlEnums::BonusType::None);
    std::shared_ptr<TileObject> GenerateField();
    std::shared_ptr<TileObject> GenerateAbbey();
    std::shared_ptr<TileObject> GenerateMonastery();
    unsigned VoidId() const;
    std::shared_ptr<TileObject> GetObject(unsigned id) const;
    std::vector<std::shared_ptr<TileObject>> GetObjectDependencies(unsigned id) const;
    void MergeObjectIds(std::shared_ptr<TileObject> absorbingObject, std::shared_ptr<TileObject> absorbedObject, std::set<Tile *> &updatedTiles);
    std::tuple<int, int, int> getTownResources(unsigned townId);
    int countObjectTiles(unsigned objectId);
    int getPoints(unsigned objectId);
    int countTownsAround(unsigned objectId);
};

#endif // OBJECTMANAGER_H
