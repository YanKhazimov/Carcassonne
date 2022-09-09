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

Town::Town(int _valency, unsigned id, BonusType _bonusType, ObjectManager *manager)
    : MapObjectData(ObjectType::Town, id, _valency, manager)
{
    valency = _valency;
    bonusType = _bonusType;
    pointValue = _bonusType == BonusType::TownCenter ? 3 : 2;
}

Road::Road(int _valency, unsigned id, BonusType _bonusType, ObjectManager *manager)
    : MapObjectData(ObjectType::Road, id, _valency, manager)
{
    valency = _valency;
    pointValue = _bonusType == BonusType::RoadLake ? 2 : 1;
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

void MapObjectData::PlayerPresence::freeRemovableMeeples()
{
    for (auto iter = meeples.begin(); iter != meeples.end(); )
    {
        switch (iter->meepleType)
        {
        case MeepleType::MeepleSmall:
        case MeepleType::MeepleBig:
        case MeepleType::MeeplePig:
        case MeepleType::MeepleBuilder:
            emit iter->tile->meepleReset();
            iter = meeples.erase(iter);
            break;
        default:
            ++iter;
        }
    }
}

std::vector<int> MapObjectData::PlayerPresence::mostPresentPlayers() const
{
    std::vector<int> result;

    std::map<int, int> presence;
    for (const auto& meeple: meeples)
    {
        if (meeple.meepleType == MeepleType::MeepleSmall)
            presence[meeple.playerIndex]++;
        else if (meeple.meepleType == MeepleType::MeepleBig)
            presence[meeple.playerIndex] += 2;
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

bool MapObjectData::PlayerPresence::taken() const
{
    return hasBeenTaken;
}

void MapObjectData::PlayerPresence::addMeeple(int playerIndex, MeepleType meepleType, Tile *tile)
{
    meeples.push_back({ playerIndex, meepleType, tile });
    hasBeenTaken = true;
}
