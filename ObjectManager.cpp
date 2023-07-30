#include "ObjectManager.h"
#include "Tile.h"
#include <iostream>

ObjectManager* ObjectManager::m_instance = nullptr;

std::shared_ptr<MapObjectData> ObjectManager::generateVoid()
{
    mapObjects[-1] = { std::make_shared<MapObjectData>(ObjectType::None, -1, -1), 0, {} };
    return std::get<0>(mapObjects[-1]);
}

ObjectManager::ObjectManager()
{
    voidId = generateVoid()->initialId;
}

ObjectManager *ObjectManager::instance()
{
    if (!m_instance)
    {
        m_instance = new ObjectManager;
    }
    return m_instance;
}

std::shared_ptr<MapObjectData> ObjectManager::GenerateRoad(unsigned valency, QmlEnums::BonusType bonusType)
{
    mapObjects[objectCounter] = { std::make_shared<Road>(valency, objectCounter, bonusType), 0, {} };
    return std::get<0>(mapObjects[objectCounter++]);
}

std::shared_ptr<MapObjectData> ObjectManager::GenerateTown(unsigned valency, QmlEnums::BonusType bonusType)
{
    mapObjects[objectCounter] = { std::make_shared<Town>(valency, objectCounter, bonusType), 0, {} };
    return std::get<0>(mapObjects[objectCounter++]);
}

std::shared_ptr<MapObjectData> ObjectManager::GenerateField()
{
    mapObjects[objectCounter] = { std::make_shared<Field>(objectCounter), 0, {} };
    return std::get<0>(mapObjects[objectCounter++]);
}

std::shared_ptr<MapObjectData> ObjectManager::GenerateAbbey()
{
    mapObjects[objectCounter] = { std::make_shared<Abbey>(objectCounter), 0, {} };
    return std::get<0>(mapObjects[objectCounter++]);
}

std::shared_ptr<MapObjectData> ObjectManager::GenerateMonastery()
{
    mapObjects[objectCounter] = { std::make_shared<Monastery>(objectCounter), 0, {} };
    return std::get<0>(mapObjects[objectCounter++]);
}

unsigned ObjectManager::VoidId() const
{
    return voidId;
}

std::shared_ptr<MapObjectData> ObjectManager::GetObject(unsigned id) const
{
    auto [objectPtr, substituteId, slaves] = mapObjects.at(id);
    return substituteId == 0 ? objectPtr : GetObject(substituteId);
}

std::vector<std::shared_ptr<MapObjectData> > ObjectManager::GetObjectDependencies(unsigned id) const
{
    return std::get<2>(mapObjects.at(id));
}

void ObjectManager::MergeObjectIds(std::shared_ptr<MapObjectData> absorbingObject,
            std::shared_ptr<MapObjectData> absorbedObject, std::set<Tile*>& updatedTiles)
{
    unsigned masterId = absorbingObject->currentObject()->initialId;
    unsigned slaveId = absorbedObject->currentObject()->initialId;

    if (masterId != slaveId)
    {
        auto& [slaveObject, slaveMaster, slaveDependencies] = mapObjects[slaveId];
        auto& [masterObject, mastersMaster, masterDependencies] = mapObjects[masterId];

        slaveMaster = masterId;
        masterDependencies.push_back(slaveObject);
        updatedTiles.insert(slaveObject->tile);

        masterDependencies.insert(masterDependencies.end(), slaveDependencies.begin(), slaveDependencies.end());

        for (auto& dep: slaveDependencies)
        {
            updatedTiles.insert(dep->tile);
        }
        slaveDependencies.clear();
    }
}

std::tuple<int, int, int> ObjectManager::getTownResources(unsigned townId)
{
    std::vector<QmlEnums::BonusType> bonuses(1, std::get<0>(mapObjects.at(townId))->getBonusType());

    for (auto& dependency: std::get<2>(mapObjects.at(townId)))
    {
        bonuses.push_back(dependency->getBonusType());
    }

    int wheat = 0, barrels = 0, cloth = 0;
    for (auto bonus: bonuses)
    {
        switch (bonus)
        {
        case QmlEnums::BonusType::Wheat: wheat++; break;
        case QmlEnums::BonusType::Barrel: barrels++; break;
        case QmlEnums::BonusType::Cloth: cloth++; break;
        }
    }

    return { wheat, barrels, cloth };
}

int ObjectManager::countObjectTiles(unsigned objectId)
{
    std::set<Tile*> tiles;
    auto [object, masterObjectId, slaveObjects] = mapObjects.at(objectId);
    tiles.insert(object->tile);

    for (auto& slave: slaveObjects)
    {
        tiles.insert(slave->tile);
    }

    return tiles.size();
}

int ObjectManager::getPoints(unsigned objectId)
{
    auto [object, masterObjectId, slaveObjects] = mapObjects.at(objectId);

    std::set<Tile*> tiles({object->tile});
    int pointSourceValue = object->pointValue;
    int pointSourceCount = 1;
    if (object->bonusType == QmlEnums::BonusType::Shield)
        ++pointSourceCount;
    else if (object->bonusType == QmlEnums::BonusType::DoubleShield)
        pointSourceCount += 2;

    for (auto& slave: slaveObjects)
    {
        pointSourceValue = qMax(pointSourceValue, slave->pointValue);

        if (tiles.insert(slave->tile).second)
        {
            ++pointSourceCount;
            if (slave->bonusType == QmlEnums::BonusType::Shield)
                ++pointSourceCount;
            else if (slave->bonusType == QmlEnums::BonusType::DoubleShield)
                pointSourceCount += 2;
        }
    }

    return pointSourceCount * pointSourceValue;
}

int ObjectManager::countTownsAround(unsigned objectId)
{
    if (auto object = GetObject(objectId); object->type == ObjectType::Field)
    {
        std::set<std::shared_ptr<MapObjectData>> adjacentTowns;
        std::vector<std::shared_ptr<MapObjectData>> group = GetObjectDependencies(objectId);
        group.push_back(object);

        for (auto& tileObject: group)
        {
            tileObject->tile->getAdjacentTowns(tileObject, adjacentTowns);
        }

        return adjacentTowns.size();
    }
    else
    {
        std::cerr << "Counting towns around an object " << objectId << " of type " << (int)object->type << std::endl;
        return 0;
    }
}
