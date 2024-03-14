#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "TileObject.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include <QJsonArray>

class ObjectManager
{
    //! initial id -> { object, id of master object, slave objects }
    std::unordered_map<int, std::tuple<std::shared_ptr<TileObject>, int, std::vector<std::shared_ptr<TileObject>>>> mapObjects;
    unsigned objectCounter = 1;
    int voidId;
    static ObjectManager* m_instance;

    ObjectManager();
    std::shared_ptr<TileObject> generateVoid();

public:
    static ObjectManager* instance();
    static int invalidObjectId;
    void reset();
    void reset(const QJsonArray &json);
    std::shared_ptr<TileObject> GenerateRoad(unsigned valency, QmlEnums::BonusType bonusType = QmlEnums::BonusType::None);
    std::shared_ptr<TileObject> GenerateTown(unsigned valency, QmlEnums::BonusType bonusType = QmlEnums::BonusType::None);
    std::shared_ptr<TileObject> GenerateField();
    std::shared_ptr<TileObject> GenerateAbbey();
    std::shared_ptr<TileObject> GenerateMonastery();
    int VoidId() const;
    std::shared_ptr<TileObject> GetAggregateObject(unsigned id) const;
    std::shared_ptr<TileObject> GetObject(unsigned id) const;
    std::vector<std::shared_ptr<TileObject>> GetObjectDependencies(unsigned id) const;
    void MergeObjectIds(std::shared_ptr<TileObject> absorbingObject, std::shared_ptr<TileObject> absorbedObject, std::set<Tile *> &updatedTiles);
    std::tuple<int, int, int> getTownResources(unsigned townId);
    int countObjectTiles(unsigned objectId);
    int getPoints(unsigned objectId);
    int countTownsAround(unsigned objectId);
    QJsonArray serialize() const;
    QList<MeepleInfo> getObjectMeeples() const;
};

#endif // OBJECTMANAGER_H
