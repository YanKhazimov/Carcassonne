#include "TileObject.h"
#include "ObjectManager.h"
#include "Tile.h"

using namespace QmlEnums;

TileObject::TileObject(ObjectType t, unsigned i, int v)
    : type(t), initialId(i), initialValency(v)
{
}

std::shared_ptr<TileObject> TileObject::currentObject() const
{
    return ObjectManager::instance()->GetObject(initialId);
}

int TileObject::currentId() const
{
    return currentObject()->initialId;
}

void TileObject::mergeObject(std::shared_ptr<TileObject> other, std::set<Tile*>& updatedTiles)
{
    ObjectManager::instance()->MergeObjectIds(ObjectManager::instance()->GetObject(initialId), other, updatedTiles);
}

void TileObject::setTile(Tile *tilePtr)
{
    tile = tilePtr;
}

QmlEnums::BonusType TileObject::getBonusType() const
{
    return bonusType;
}

bool TileObject::isCompleted() const
{
    return completedCentralObject;
}

Town::Town(int _valency, unsigned id, QmlEnums::BonusType _bonusType)
    : TileObject(ObjectType::Town, id, _valency)
{
    valency = _valency;
    bonusType = _bonusType;
    pointValue = _bonusType == QmlEnums::BonusType::TownCenter ? 3 : 2;
}

bool Town::isCompleted() const
{
    return valency == 0;
}

void TileObject::markCompleted()
{
    completedCentralObject = true;
}

Road::Road(int _valency, unsigned id, QmlEnums::BonusType _bonusType)
    : TileObject(ObjectType::Road, id, _valency)
{
    valency = _valency;
    bonusType = _bonusType;
    pointValue = _bonusType == QmlEnums::BonusType::RoadLake ? 2 : 1;
}

bool Road::isCompleted() const
{
    return valency == 0;
}

Field::Field(unsigned id)
    : TileObject(ObjectType::Field, id, -1)
{
}

Abbey::Abbey(unsigned id)
    : TileObject(ObjectType::Abbey, id, -1)
{
    // setting valency to 1 so that it closes every connection
    valency = 1;
    pointValue = 9;
}

Monastery::Monastery(unsigned id)
    : TileObject(ObjectType::Monastery, id, -1)
{
    pointValue = 9;
}

std::list<TileObject::MeepleInfo> TileObject::freeMeeples(const std::set<QmlEnums::MeepleType>& typesToRemove)
{
    std::list<MeepleInfo> removedMeeples;
    for (const auto& object: group())
    {
        for (auto iter = object->playerPresence.meeples.begin(); iter != object->playerPresence.meeples.end(); )
        {
            if (typesToRemove.find(iter->meepleType) != typesToRemove.end())
            {
                removedMeeples.push_back(*iter);
                emit iter->tile->meepleReset();
                iter = object->playerPresence.meeples.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    return removedMeeples;
}

std::vector<int> TileObject::mostPresentPlayers() const
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

std::set<int> TileObject::pigs() const
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

bool TileObject::meeplePresent(const std::set<QmlEnums::MeepleType> &types, int playerIndex) const
{
    for (const auto& object: group())
    {
        for (const auto& meeple: object->playerPresence.meeples)
        {
            auto typeIter = types.find(meeple.meepleType);
            if (typeIter != types.end() &&
                (playerIndex == -1 || meeple.playerIndex == playerIndex))
                return true;
        }
    }

    return false;
}

bool TileObject::taken() const
{
    return playerPresence.hasBeenTaken;
}

std::vector<std::shared_ptr<TileObject> > TileObject::group() const
{
    auto dependencies = ObjectManager::instance()->GetObjectDependencies(currentObject()->initialId);
    dependencies.push_back(ObjectManager::instance()->GetObject(initialId));
    return dependencies;
}

void TileObject::addMeeple(int playerIndex, MeepleType meepleType, Tile *tile)
{
    playerPresence.meeples.push_back({ playerIndex, meepleType, tile });
    playerPresence.hasBeenTaken = true;
}
