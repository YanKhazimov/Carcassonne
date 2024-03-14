#ifndef TILEOBJECT_H
#define TILEOBJECT_H
#include "DataTypes.h"
#include <memory>
#include <set>

class Tile;

class TileObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int InitialId MEMBER initialId CONSTANT)
    Q_PROPERTY(int CurrentId READ currentId NOTIFY currentIdChanged)

public:
    struct MeepleInfo {
        int playerIndex;
        QmlEnums::MeepleType meepleType;
        Tile *tile;
    };
    struct PlayerPresence {
        std::list<MeepleInfo> meeples;
        bool hasBeenTaken = false;
    };

    Tile* tile;
    ObjectType type = ObjectType::None;
    int pointValue = 0;

    //! id in context of the object's tile
    const unsigned initialId;
    const unsigned initialValency;

    //! actual object
    int valency = -1;
    std::shared_ptr<TileObject> currentObject() const;

    TileObject(ObjectType type, unsigned id, int valency);

    void markCompleted();
    void mergeObject(std::shared_ptr<TileObject> other, std::set<Tile *> &updatedTiles);
    virtual bool isCompleted() const;
    QmlEnums::BonusType getBonusType() const;
    void setTile(Tile* tilePtr);
    void addMeeple(int playerIndex, QmlEnums::MeepleType meepleType, Tile* tile);
    std::list<MeepleInfo> freeMeeples(const std::set<QmlEnums::MeepleType>& typesToRemove);
    std::vector<int> mostPresentPlayers() const;
    bool taken() const;
    std::set<int> pigs() const;
    bool meeplePresent(const std::set<QmlEnums::MeepleType> &types, int playerIndex = -1) const;

private:
    PlayerPresence playerPresence;
    std::vector<std::shared_ptr<TileObject>> group() const;
    int currentId() const;

protected:
    QmlEnums::BonusType bonusType;
    bool completedCentralObject = false;

signals:
    void currentIdChanged(int newId);
};

class Town : public TileObject
{
public:
    Town(int valency, unsigned id, QmlEnums::BonusType bonusType);
    bool isCompleted() const override;
};

class Road : public TileObject
{
public:
    Road(int valency, unsigned id, QmlEnums::BonusType bonusType);
    bool isCompleted() const override;
};

class Field : public TileObject
{
public:
    Field(unsigned id);
};

class Abbey : public TileObject
{
public:
    Abbey(unsigned id);
};

class Monastery : public TileObject
{
public:
    Monastery(unsigned id);
};


#endif // TILEOBJECT_H
