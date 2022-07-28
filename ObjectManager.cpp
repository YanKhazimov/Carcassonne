#include "ObjectManager.h"

std::shared_ptr<MapObjectData> ObjectManager::generateVoid()
{
    mapObjects[-1] = { std::make_shared<MapObjectData>(ObjectType::None, -1, -1, this), -1 };
    return mapObjects[-1].first;
}

ObjectManager::ObjectManager()
{
    voidId = generateVoid()->initialId;
}

std::shared_ptr<MapObjectData> ObjectManager::GenerateRoad(unsigned valency)
{
    mapObjects[objectCounter] = { std::make_shared<Road>(valency, objectCounter, this), -1 };
    return mapObjects[objectCounter++].first;
}

std::shared_ptr<MapObjectData> ObjectManager::GenerateTown(unsigned valency)
{
    mapObjects[objectCounter] = { std::make_shared<Town>(valency, objectCounter, this), -1 };
    return mapObjects[objectCounter++].first;
}

std::shared_ptr<MapObjectData> ObjectManager::GenerateField()
{
    mapObjects[objectCounter] = { std::make_shared<Field>(objectCounter, this), -1 };
    return mapObjects[objectCounter++].first;
}

unsigned ObjectManager::VoidId() const
{
    return voidId;
}

std::shared_ptr<MapObjectData> ObjectManager::GetObject(int id) const
{
    auto [objectPtr, substituteId] = mapObjects.at(id);
    return objectPtr ? objectPtr : GetObject(substituteId);
}

void ObjectManager::MergeObjectIds(std::shared_ptr<MapObjectData> absorbingObject, std::shared_ptr<MapObjectData> absorbedObject)
{
    if (absorbedObject->currentObject() != absorbingObject->currentObject())
    {
        auto realAbsorbedObject = GetObject(absorbedObject->initialId);
        mapObjects[realAbsorbedObject->initialId] = { nullptr, absorbingObject->initialId };
    }
}
