#ifndef DATATYPES_H
#define DATATYPES_H

#include "qobjectdefs.h"
#include <QColor>
#include <QVariantList>

enum Direction {
    East,
    North,
    South,
    West,
    Last = West
};

enum class ObjectType {
    None = 0,
    Town,
    Road,
    Field,
    Monastery,
    Abbey
};

enum BonusType {
    None,
    Wheat,
    Barrel,
    Cloth,
    Shield,
    DoubleShield,
    TownCenter,
    RoadLake
};

namespace QmlEnums {
    Q_NAMESPACE

    enum MeepleType {
        MeepleNone = 0,
        MeepleSmall,
        MeepleBig,
        MeepleBarn,
        MeepleBuilder,
        MeeplePig
    };
    Q_ENUM_NS(MeepleType)

}
Direction opposite(Direction direction);

extern QVariantList playerColors;

#endif // DATATYPES_H
