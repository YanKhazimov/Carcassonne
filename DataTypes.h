#ifndef DATATYPES_H
#define DATATYPES_H

#include "qobjectdefs.h"
#include <QColor>
#include <QVariantList>

enum TileSide {
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

namespace QmlEnums {
    Q_NAMESPACE

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
    Q_ENUM_NS(BonusType)

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
    TileSide opposite(TileSide side);

extern QVariantList playerColors;

#endif // DATATYPES_H
