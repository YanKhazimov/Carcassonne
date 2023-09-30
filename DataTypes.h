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
Q_DECLARE_METATYPE(ObjectType)

namespace QmlEnums {
    Q_NAMESPACE

    enum BonusType {
        None,
        Wheat,
        Barrel,
        Cloth,
        MaxResourceType,
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

    enum LogRecordType
    {
        LogNone = 0,
        LogScoring,
        LogObjectCompletion,
        LogFreeTurn,
        LogRoadLeadChange,
        LogTownLeadChange,
        LogMeeplePlaced,
        LogTilePlaced,
        LogMeeplesReleased,
        LogNewTurn,
        LogResourceLeadChange,
        LogResource,
        LogGameEnd
    };
    Q_ENUM_NS(LogRecordType)
}

TileSide opposite(TileSide side);

extern QVariantList playerColors;
extern QMap<QString, QMap<ObjectType, QString>> objectStrings;

#endif // DATATYPES_H
