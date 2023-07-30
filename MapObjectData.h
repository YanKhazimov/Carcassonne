#ifndef MAPOBJECTDATA_H
#define MAPOBJECTDATA_H
#include "DataTypes.h"
#include <memory>
#include <set>

class Tile;

struct MapObjectData {
    Tile* tile;
    ObjectType type = ObjectType::None;
    //! id in context of the object's tile
    const unsigned initialId;
    const unsigned initialValency;
    int pointValue = 0;

    //! actual object
    std::shared_ptr<MapObjectData> currentObject() const;
    int valency = -1;

    void mergeObject(std::shared_ptr<MapObjectData> other, std::set<Tile *> &updatedTiles);
    MapObjectData(ObjectType type, unsigned id, int valency);
    void setTile(Tile* tilePtr);

    QmlEnums::BonusType bonusType;
    QmlEnums::BonusType getBonusType() const;

    virtual bool isCompleted() const;
    void markCompleted();

    struct MeepleInfo {
        int playerIndex;
        QmlEnums::MeepleType meepleType;
        Tile *tile;
    };

    struct PlayerPresence {
        std::list<MeepleInfo> meeples;
        bool hasBeenTaken = false;
    };

    void addMeeple(int playerIndex, QmlEnums::MeepleType meepleType, Tile* tile);
    std::list<MeepleInfo> freeMeeples(const std::set<QmlEnums::MeepleType>& typesToRemove);
    std::vector<int> mostPresentPlayers() const;
    bool taken() const;
    std::set<int> pigs() const;
    bool meeplePresent(const std::set<QmlEnums::MeepleType> &types, int playerIndex = -1) const;

private:
    PlayerPresence playerPresence;
    std::vector<std::shared_ptr<MapObjectData>> group() const;

protected:
    bool completedCentralObject = false;
};

class Town : public MapObjectData
{
public:
    Town(int valency, unsigned id, QmlEnums::BonusType bonusType);
    bool isCompleted() const override;
};

class Road : public MapObjectData
{
public:
    Road(int valency, unsigned id, QmlEnums::BonusType bonusType);
    bool isCompleted() const override;
};

class Field : public MapObjectData
{
public:
    Field(unsigned id);
};

class Abbey : public MapObjectData
{
public:
    Abbey(unsigned id);
};

class Monastery : public MapObjectData
{
public:
    Monastery(unsigned id);
};


#endif // MAPOBJECTDATA_H
