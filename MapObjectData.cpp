#include "MapObjectData.h"
#include "ObjectManager.h"
#include "Tile.h"

using namespace QmlEnums;

MapObjectData::MapObjectData(ObjectType t, unsigned i, int v, ObjectManager *m)
    : manager(m), type(t), initialId(i), initialValency(v)
{
}

std::shared_ptr<MapObjectData> MapObjectData::currentObject() const
{
    return manager->GetObject(initialId);
}

void MapObjectData::mergeObject(std::shared_ptr<MapObjectData> other, std::set<Tile*>& updatedTiles)
{
    manager->MergeObjectIds(std::make_shared<MapObjectData>(*this), other, updatedTiles);
}

void MapObjectData::setTile(Tile *tilePtr)
{
    tile = tilePtr;
}

BonusType MapObjectData::getBonusType() const
{
    return bonusType;
}

bool MapObjectData::isCompleted() const
{
    return completedCentralObject;
}

Town::Town(int _valency, unsigned id, BonusType _bonusType, ObjectManager *manager)
    : MapObjectData(ObjectType::Town, id, _valency, manager)
{
    valency = _valency;
    bonusType = _bonusType;
    pointValue = _bonusType == BonusType::TownCenter ? 3 : 2;
}

bool Town::isCompleted() const
{
    return valency == 0;
}

void MapObjectData::markCompleted()
{
    completedCentralObject = true;
}

Road::Road(int _valency, unsigned id, BonusType _bonusType, ObjectManager *manager)
    : MapObjectData(ObjectType::Road, id, _valency, manager)
{
    valency = _valency;
    pointValue = _bonusType == BonusType::RoadLake ? 2 : 1;
}

bool Road::isCompleted() const
{
    return valency == 0;
}

Field::Field(unsigned id, ObjectManager *manager)
    : MapObjectData(ObjectType::Field, id, -1, manager)
{
}

Abbey::Abbey(unsigned id, ObjectManager *manager)
    : MapObjectData(ObjectType::Abbey, id, -1, manager)
{
    // setting valency to 1 so that it closes every connection
    valency = 1;
    pointValue = 9;
}

Monastery::Monastery(unsigned id, ObjectManager *manager)
    : MapObjectData(ObjectType::Monastery, id, -1, manager)
{
    pointValue = 9;
}

void MapObjectData::freeMeeples(const std::set<QmlEnums::MeepleType>& typesToRemove)
{
    for (const auto& object: group())
    {
        for (auto iter = object->playerPresence.meeples.begin(); iter != object->playerPresence.meeples.end(); )
        {
            if (typesToRemove.find(iter->meepleType) != typesToRemove.end())
            {
                emit iter->tile->meepleReset();
                iter = object->playerPresence.meeples.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
}

std::vector<int> MapObjectData::mostPresentPlayers() const
{
    std::vector<int> result;

    std::map<int, int> presence;

    for (const auto& object: group())
    {
        for (const auto& meeple: object->playerPresence.meeples)
        {
            if (meeple.meepleType == MeepleType::MeepleSmall)
                presence[meeple.playerIndex]++;
            else if (meeple.meepleType == MeepleType::MeepleBig)
                presence[meeple.playerIndex] += 2;
        }
    }

    int maxPresence = 0;
    for (auto& playerPresence: presence)
    {
        if (playerPresence.second > maxPresence)
        {
            maxPresence = playerPresence.second;
            result.clear();
            result.push_back(playerPresence.first);
        }
        else if (playerPresence.second == maxPresence)
        {
            result.push_back(playerPresence.first);
        }
    }

    return result;
}

std::set<int> MapObjectData::pigs() const
{
    std::set<int> result;

    for (const auto& object: group())
    {
        for (const auto& meeple: object->playerPresence.meeples)
        {
            if (meeple.meepleType == MeepleType::MeeplePig)
                result.insert(meeple.playerIndex);
        }
    }

    return result;
}

bool MapObjectData::commonMeeplesPresent(int playerIndex) const
{
    for (const auto& object: group())
    {
        for (const auto& meeple: object->playerPresence.meeples)
        {
            if ((meeple.meepleType == MeepleType::MeepleSmall ||
                    meeple.meepleType == MeepleType::MeepleBig) &&
                    meeple.playerIndex == playerIndex)
                return true;
        }
    }

    return false;
}

bool MapObjectData::barnPresent() const
{
    for (const auto& object: group())
    {
        for (const auto& meeple: object->playerPresence.meeples)
        {
            if (meeple.meepleType == MeepleType::MeepleBarn)
                return true;
        }
    }

    return false;
}

bool MapObjectData::taken() const
{
    return playerPresence.hasBeenTaken;
}

std::vector<std::shared_ptr<MapObjectData> > MapObjectData::group() const
{
    auto dependencies = manager->GetObjectDependencies(currentObject()->initialId);
    dependencies.push_back(manager->GetObject(initialId));
    return dependencies;
}

void MapObjectData::addMeeple(int playerIndex, MeepleType meepleType, Tile *tile)
{
    playerPresence.meeples.push_back({ playerIndex, meepleType, tile });
    //qDebug() << "object" << initialId;
    //qDebug() << "add meeple" << playerIndex << (int)meepleType;
    playerPresence.hasBeenTaken = true;
}
