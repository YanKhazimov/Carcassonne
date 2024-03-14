#include "TileObject.h"
#include "ObjectManager.h"
#include "Tile.h"
#include <QQmlEngine>

using namespace QmlEnums;

TileObject::TileObject(ObjectType t, int i, int v, QObject *parent)
    : QObject(parent), type(t), initialId(i), initialValency(v)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

std::shared_ptr<TileObject> TileObject::currentObject() const
{
    return ObjectManager::instance()->GetAggregateObject(initialId);
}

int TileObject::currentId() const
{
    return currentObject()->initialId;
}

void TileObject::mergeObject(std::shared_ptr<TileObject> other, std::set<Tile*>& updatedTiles)
{
    ObjectManager::instance()->MergeObjectIds(ObjectManager::instance()->GetObject(initialId)
        /*std::make_shared<TileObject>(*this)*/, other, updatedTiles);
}

void TileObject::setTile(Tile *tilePtr)
{
    tile = meepleInfo.tile = tilePtr;
}

QmlEnums::BonusType TileObject::getBonusType() const
{
    return bonusType;
}

bool TileObject::isCompleted() const
{
    return completedCentralObject;
}

Town::Town(int _valency, int id, QmlEnums::BonusType _bonusType, QObject *parent)
    : TileObject(ObjectType::Town, id, _valency, parent)
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

Road::Road(int _valency, int id, QmlEnums::BonusType _bonusType, QObject *parent)
    : TileObject(ObjectType::Road, id, _valency, parent)
{
    valency = _valency;
    bonusType = _bonusType;
    pointValue = _bonusType == QmlEnums::BonusType::RoadLake ? 2 : 1;
}

bool Road::isCompleted() const
{
    return valency == 0;
}

Field::Field(unsigned id, QObject *parent)
    : TileObject(ObjectType::Field, id, -1, parent)
{
}

Abbey::Abbey(unsigned id, QObject *parent)
    : TileObject(ObjectType::Abbey, id, -1, parent)
{
    // setting valency to 1 so that it closes every connection
    valency = 1;
    pointValue = 9;
}

Monastery::Monastery(unsigned id, QObject *parent)
    : TileObject(ObjectType::Monastery, id, -1, parent)
{
    pointValue = 9;
}

std::list<MeepleInfo> TileObject::freeMeeples(const std::set<QmlEnums::MeepleType>& typesToRemove)
{
    std::list<MeepleInfo> removedMeeples;
    for (const auto& object: group())
    {
        if (typesToRemove.find(object->meepleInfo.meepleType) != typesToRemove.end())
        {
            removedMeeples.push_back(object->meepleInfo);
            emit object->tile->meepleReset();
            object->meepleInfo = MeepleInfo{};
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
        if (object->meepleInfo.meepleType == MeepleType::MeepleSmall)
            presence[object->meepleInfo.playerIndex]++;
        else if (object->meepleInfo.meepleType == MeepleType::MeepleBig)
            presence[object->meepleInfo.playerIndex] += 2;
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
        if (object->meepleInfo.meepleType == MeepleType::MeeplePig)
            result.insert(object->meepleInfo.playerIndex);
    }

    return result;
}

bool TileObject::meeplePresent(const std::set<QmlEnums::MeepleType> &types, int playerIndex) const
{
    for (const auto& object: group())
    {
        auto typeIter = types.find(object->meepleInfo.meepleType);
        if (typeIter != types.end() &&
            (playerIndex == -1 || object->meepleInfo.playerIndex == playerIndex))
            return true;
    }

    return false;
}

QJsonObject TileObject::serialize() const
{
    QJsonObject json;

    json["type"] = (int)type;
    json["initialId"] = (int)initialId;
    json["initialValency"] = (int)initialValency;
    json["pointValue"] = pointValue;
    json["valency"] = valency;
    json["bonusType"] = bonusType;
    json["completedCentralObject"] = completedCentralObject;
    // json["hasBeenTaken"] = playerPresence.hasBeenTaken;

    if (meepleInfo != MeepleInfo{})
    {
        json["meeple"] = QJsonObject({
                                      { "playerIndex", meepleInfo.playerIndex },
                                      { "meepleType", meepleInfo.meepleType },
                                      { "tileXRatio", meepleInfo.tileXRatio },
                                      { "tileYRatio", meepleInfo.tileYRatio }
        });
    }

    return json;
}

bool TileObject::taken() const
{
    return meepleInfo != MeepleInfo{};
}

std::vector<std::shared_ptr<TileObject> > TileObject::group() const
{
    auto dependencies = ObjectManager::instance()->GetObjectDependencies(currentObject()->initialId);
    dependencies.push_back(ObjectManager::instance()->GetAggregateObject(initialId));
    return dependencies;
}

void TileObject::setMeeple(int playerIndex, MeepleType meepleType, qreal tileXRatio, qreal tileYRatio)
{
    Q_ASSERT(meepleInfo == MeepleInfo{});
    meepleInfo = { playerIndex, meepleType, tileXRatio, tileYRatio };
}

int MeepleInfo::tileX() const
{
    return tile->getX();
}

int MeepleInfo::tileY() const
{
    return tile->getY();
}

MeepleInfo::MeepleInfo()
    : playerIndex(-1), meepleType(QmlEnums::MeepleNone), tileXRatio(-1.0), tileYRatio(-1.0)
{
}

MeepleInfo::MeepleInfo(int player, QmlEnums::MeepleType type, qreal _tileXRatio, qreal _tileYRatio)
    : playerIndex(player), meepleType(type), tileXRatio(_tileXRatio), tileYRatio(_tileYRatio)
{
}

bool MeepleInfo::operator==(const MeepleInfo &other) const noexcept
{
    return playerIndex == other.playerIndex && meepleType == other.meepleType &&
           qFuzzyCompare(tileXRatio, other.tileXRatio) && qFuzzyCompare(tileYRatio, other.tileYRatio);
}

bool MeepleInfo::operator!=(const MeepleInfo &other) const noexcept
{
    return !(*this == other);
}
