#include "ObjectManager.h"
#include "Tile.h"
#include "DataTypes.h"
#include <iostream>

ObjectManager* ObjectManager::m_instance = nullptr;
int ObjectManager::invalidObjectId = 0;

std::shared_ptr<TileObject> ObjectManager::generateVoid()
{
    mapObjects[-1] = { std::make_shared<TileObject>(ObjectType::None, -1, -1), 0, {} };
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

void ObjectManager::reset()
{
    mapObjects.clear();
    generateVoid();
    objectCounter = 1;
}

void ObjectManager::reset(const QJsonArray &json)
{
    mapObjects.clear();
    generateVoid();
    objectCounter = json.size() + 1;

    for (int objectIndex = 0; objectIndex < json.size(); ++objectIndex)
    {
        int masterId = json.at(objectIndex).toObject()["masterId"].toInt();
        QJsonObject object = json.at(objectIndex).toObject()["object"].toObject();
        int initialId = object["initialId"].toInt();
        int initialValency = object["initialValency"].toInt();
        QmlEnums::BonusType bonusType = static_cast<QmlEnums::BonusType>(object["bonusType"].toInt());
        ObjectType type = static_cast<ObjectType>(object["type"].toInt());
        switch(type)
        {
        case ObjectType::Town:
            mapObjects[initialId] = { std::make_shared<Town>(initialValency, initialId, bonusType), masterId, {} };
            break;
        case ObjectType::Road:
            mapObjects[initialId] = { std::make_shared<Road>(initialValency, initialId, bonusType), masterId, {} };
            break;
        case ObjectType::Field:
            mapObjects[initialId] = { std::make_shared<Field>(initialId), masterId, {} };
            break;
        case ObjectType::Monastery:
            mapObjects[initialId] = { std::make_shared<Monastery>(initialId), masterId, {} };
            break;
        case ObjectType::Abbey:
            mapObjects[initialId] = { std::make_shared<Abbey>(initialId), masterId, {} };
            break;
        default:
            qCritical() << "Unknown object type in save file:" <<  static_cast<int>(type);
        }
        if (object.contains("meeple"))
        {
            QJsonObject meepleObject = object["meeple"].toObject();
            std::get<0>(mapObjects[initialId])->setMeeple(meepleObject["playerIndex"].toInt(),
                                                          static_cast<QmlEnums::MeepleType>(meepleObject["meepleType"].toInt()),
                                                          meepleObject["tileXRatio"].toDouble(),
                                                          meepleObject["tileYRatio"].toDouble());
        }
    }

    // adding dependencies once every object is read
    for (int objectIndex = 0; objectIndex < json.size(); ++objectIndex)
    {
        QJsonObject object = json.at(objectIndex).toObject()["object"].toObject();
        int initialId = object["initialId"].toInt();
        QJsonArray slaves = json.at(objectIndex).toObject()["slaves"].toArray();
        for (const QJsonValue& slave: slaves)
        {
            std::shared_ptr<TileObject> slaveObject = std::get<0>(mapObjects[slave.toInt()]);
            std::get<2>(mapObjects[initialId]).push_back(slaveObject);
        }
    }
}

std::shared_ptr<TileObject> ObjectManager::GenerateRoad(unsigned valency, QmlEnums::BonusType bonusType)
{
    mapObjects[objectCounter] = { std::make_shared<Road>(valency, objectCounter, bonusType), 0, {} };
    return std::get<0>(mapObjects[objectCounter++]);
}

std::shared_ptr<TileObject> ObjectManager::GenerateTown(unsigned valency, QmlEnums::BonusType bonusType)
{
    mapObjects[objectCounter] = { std::make_shared<Town>(valency, objectCounter, bonusType), 0, {} };
    return std::get<0>(mapObjects[objectCounter++]);
}

std::shared_ptr<TileObject> ObjectManager::GenerateField()
{
    mapObjects[objectCounter] = { std::make_shared<Field>(objectCounter), 0, {} };
    return std::get<0>(mapObjects[objectCounter++]);
}

std::shared_ptr<TileObject> ObjectManager::GenerateAbbey()
{
    mapObjects[objectCounter] = { std::make_shared<Abbey>(objectCounter), 0, {} };
    return std::get<0>(mapObjects[objectCounter++]);
}

std::shared_ptr<TileObject> ObjectManager::GenerateMonastery()
{
    mapObjects[objectCounter] = { std::make_shared<Monastery>(objectCounter), 0, {} };
    return std::get<0>(mapObjects[objectCounter++]);
}

int ObjectManager::VoidId() const
{
    return voidId;
}

std::shared_ptr<TileObject> ObjectManager::GetAggregateObject(unsigned id) const
{
    if (auto iter = mapObjects.find(id); iter != mapObjects.end())
    {
        auto [objectPtr, substituteId, slaves] = iter->second;
        return substituteId == 0 ? objectPtr : GetAggregateObject(substituteId);
    }
    else
    {
        return nullptr;
    }
}

std::shared_ptr<TileObject> ObjectManager::GetObject(unsigned int id) const
{
    auto iter = mapObjects.find(id);
    return iter != mapObjects.end() ? std::get<0>(iter->second) : nullptr;
}

std::vector<std::shared_ptr<TileObject> > ObjectManager::GetObjectDependencies(unsigned id) const
{
    return std::get<2>(mapObjects.at(id));
}

void ObjectManager::MergeObjectIds(std::shared_ptr<TileObject> absorbingObject,
                                   std::shared_ptr<TileObject> absorbedObject, std::set<Tile*>& updatedTiles)
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
        emit slaveObject->currentIdChanged(masterId);

        masterDependencies.insert(masterDependencies.end(), slaveDependencies.begin(), slaveDependencies.end());

        for (auto& dep: slaveDependencies)
        {
            updatedTiles.insert(dep->tile);
            emit dep->currentIdChanged(masterId);
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
    if (auto object = GetAggregateObject(objectId); object->type == ObjectType::Field)
    {
        std::set<std::shared_ptr<TileObject>> adjacentTowns;
        std::vector<std::shared_ptr<TileObject>> group = GetObjectDependencies(objectId);
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

QJsonArray ObjectManager::serialize() const
{
    QJsonArray result;

    for (auto iter = mapObjects.begin(); iter != mapObjects.end(); ++iter)
    {
        if (iter->first == voidId)
            continue;

        QJsonObject record;
//        record["initialId"] = QJsonValue::fromVariant(iter->first);
        record["object"] = std::get<0>(iter->second)->serialize();
        record["masterId"] = QJsonValue::fromVariant(std::get<1>(iter->second));

        QJsonArray slaves;
        for (const auto& slave: std::get<2>(iter->second))
        {
            slaves.push_back(QJsonValue::fromVariant(slave->initialId)/*serialize()*/);
        }
        if (!slaves.empty())
            record["slaves"] = slaves;

        result.push_back(record);
    }

    return result;
}

QList<MeepleInfo> ObjectManager::getObjectMeeples() const
{
    QList<MeepleInfo> result;

    for (auto iter = mapObjects.begin(); iter != mapObjects.end(); ++iter)
    {
        auto meeple = std::get<0>(iter->second)->meepleInfo;
        if (meeple != MeepleInfo{})
        {
            result.push_back(meeple);
        }
    }

    return result;
}
