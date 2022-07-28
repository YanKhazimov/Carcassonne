#ifndef MAPOBJECTDATA_H
#define MAPOBJECTDATA_H
#include "DataTypes.h"
#include <memory>

class ObjectManager;

struct MapObjectData {
    ObjectType type = ObjectType::None;
    //! id in context of the object's tile
    const unsigned initialId;
    const unsigned initialValency;
    int valency = -1;
    ObjectManager* manager;

    MapObjectData(ObjectType t, unsigned i, int v, ObjectManager* m);
    //! actual object
    std::shared_ptr<MapObjectData> currentObject() const;
    void mergeObject(std::shared_ptr<MapObjectData> other);
};

class Town : public MapObjectData {
public:
    Town(int v, unsigned i, ObjectManager* m);
};

class Road : public MapObjectData {
public:
    Road(int v, unsigned i, ObjectManager* m);
};

class Field : public MapObjectData {
public:
    Field(unsigned i, ObjectManager* m);
};


#endif // MAPOBJECTDATA_H
