#ifndef TILEOBJECT_H
#define TILEOBJECT_H
#include "DataTypes.h"
#include <memory>
#include <set>

class Tile;

class MeepleInfo {
    Q_GADGET

    Q_PROPERTY(int PlayerIndex MEMBER playerIndex CONSTANT FINAL)
    Q_PROPERTY(QmlEnums::MeepleType MeepleType MEMBER meepleType CONSTANT FINAL)
    Q_PROPERTY(int TileX READ tileX CONSTANT FINAL)
    Q_PROPERTY(int TileY READ tileY CONSTANT FINAL)
    Q_PROPERTY(qreal TileXRatio MEMBER tileXRatio CONSTANT FINAL)
    Q_PROPERTY(qreal TileYRatio MEMBER tileYRatio CONSTANT FINAL)

    int tileX() const;
    int tileY() const;

public:
    Tile* tile = nullptr;
    int playerIndex;
    QmlEnums::MeepleType meepleType;
    qreal tileXRatio;
    qreal tileYRatio;
    MeepleInfo();
    MeepleInfo(int player, QmlEnums::MeepleType type, qreal tileXRatio, qreal tileYRatio);

    bool operator==(const MeepleInfo& other) const noexcept;
    bool operator!=(const MeepleInfo& other) const noexcept;
};
Q_DECLARE_METATYPE(MeepleInfo)

class TileObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int InitialId MEMBER initialId CONSTANT)
    Q_PROPERTY(int CurrentId READ currentId NOTIFY currentIdChanged)

public:
    Tile* tile = nullptr;
    ObjectType type = ObjectType::None;
    //! id in context of the object's tile
    const int initialId;
    const int initialValency;
    int pointValue = 0;
    MeepleInfo meepleInfo;
    //! actual object
    std::shared_ptr<TileObject> currentObject() const;
    int valency = -1;

    void mergeObject(std::shared_ptr<TileObject> other, std::set<Tile *> &updatedTiles);
    TileObject(ObjectType type, int id, int valency, QObject* parent = nullptr);
    void setTile(Tile* tilePtr);

    QmlEnums::BonusType bonusType = QmlEnums::BonusType::None;
    QmlEnums::BonusType getBonusType() const;

    virtual bool isCompleted() const;
    void markCompleted();

    void setMeeple(int playerIndex, QmlEnums::MeepleType meepleType, qreal tileXRatio, qreal tileYRatio);
    std::list<MeepleInfo> freeMeeples(const std::set<QmlEnums::MeepleType>& typesToRemove);
    std::vector<int> mostPresentPlayers() const;
    bool taken() const;
    std::set<int> pigs() const;
    bool meeplePresent(const std::set<QmlEnums::MeepleType> &types, int playerIndex = -1) const;

    QJsonObject serialize() const;

private:
    std::vector<std::shared_ptr<TileObject>> group() const;
    int currentId() const;

protected:
    bool completedCentralObject = false;

signals:
    void currentIdChanged(int newId);
};
Q_DECLARE_METATYPE(QList<MeepleInfo>)

class Town : public TileObject
{
    Q_OBJECT

public:
    Town(int valency, int id, QmlEnums::BonusType bonusType, QObject* parent = nullptr);
    bool isCompleted() const override;
};

class Road : public TileObject
{
    Q_OBJECT

public:
    Road(int valency, int id, QmlEnums::BonusType bonusType, QObject* parent = nullptr);
    bool isCompleted() const override;
};

class Field : public TileObject
{
    Q_OBJECT

public:
    Field(unsigned id, QObject* parent = nullptr);
};

class Abbey : public TileObject
{
    Q_OBJECT

public:
    Abbey(unsigned id, QObject* parent = nullptr);
};

class Monastery : public TileObject
{
    Q_OBJECT

public:
    Monastery(unsigned id, QObject* parent = nullptr);
};


#endif // TILEOBJECT_H
