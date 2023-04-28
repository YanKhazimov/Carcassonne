#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "MapObjectData.h"
#include <unordered_map>
#include <memory>
#include <vector>

class ObjectManager
{
    //! initial id -> { object, id of master object, slave objects }
    std::unordered_map<unsigned, std::tuple<std::shared_ptr<MapObjectData>, unsigned, std::vector<std::shared_ptr<MapObjectData>>>> mapObjects;
    unsigned objectCounter = 1;
    unsigned voidId;
    std::shared_ptr<MapObjectData> generateVoid();

public:
    ObjectManager();
    std::shared_ptr<MapObjectData> GenerateRoad(unsigned valency, QmlEnums::BonusType bonusType = QmlEnums::BonusType::None);
    std::shared_ptr<MapObjectData> GenerateTown(unsigned valency, QmlEnums::BonusType bonusType = QmlEnums::BonusType::None);
    std::shared_ptr<MapObjectData> GenerateField();
    std::shared_ptr<MapObjectData> GenerateAbbey();
    std::shared_ptr<MapObjectData> GenerateMonastery();
    unsigned VoidId() const;
    std::shared_ptr<MapObjectData> GetObject(unsigned id) const;
    std::vector<std::shared_ptr<MapObjectData>> GetObjectDependencies(unsigned id) const;
    void MergeObjectIds(std::shared_ptr<MapObjectData> absorbingObject, std::shared_ptr<MapObjectData> absorbedObject, std::set<Tile *> &updatedTiles);
    std::tuple<int, int, int> getTownResources(unsigned townId);
    int countObjectTiles(unsigned objectId);
    int getPoints(unsigned objectId);
    int countTownsAround(unsigned objectId);
};

#endif // OBJECTMANAGER_H
