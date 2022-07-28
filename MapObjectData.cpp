#include "MapObjectData.h"
#include "ObjectManager.h"

MapObjectData::MapObjectData(ObjectType t, unsigned i, int v, ObjectManager *m)
    : type(t), initialId(i), initialValency(v), manager(m)
{
}

std::shared_ptr<MapObjectData> MapObjectData::currentObject() const
{
    return manager->GetObject(initialId);
}

void MapObjectData::mergeObject(std::shared_ptr<MapObjectData> other)
{
    manager->MergeObjectIds(std::make_shared<MapObjectData>(*this), other);
}

Town::Town(int v, unsigned i, ObjectManager *m)
    : MapObjectData(ObjectType::Town, i, v, m)
{
    valency = v;
}

Road::Road(int v, unsigned i, ObjectManager *m)
    : MapObjectData(ObjectType::Road, i, v, m)
{
    valency = v;
}

Field::Field(unsigned i, ObjectManager *m)
    : MapObjectData(ObjectType::Field, i, -1, m)
{
}
