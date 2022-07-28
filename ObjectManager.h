#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "MapObjectData.h"
#include <unordered_map>
#include <memory>

class ObjectManager
{
    //! id -> { object, id of merger object }
    std::unordered_map<unsigned, std::pair<std::shared_ptr<MapObjectData>, unsigned>> mapObjects;
    unsigned objectCounter = 1;
    unsigned voidId;
    std::shared_ptr<MapObjectData> generateVoid();

public:
    ObjectManager();
    std::shared_ptr<MapObjectData> GenerateRoad(unsigned valency);
    std::shared_ptr<MapObjectData> GenerateTown(unsigned valency);
    std::shared_ptr<MapObjectData> GenerateField();
    unsigned VoidId() const;
    std::shared_ptr<MapObjectData> GetObject(int id) const;
    void MergeObjectIds(std::shared_ptr<MapObjectData> absorbingObject, std::shared_ptr<MapObjectData> absorbedObject);
};

#endif // OBJECTMANAGER_H
