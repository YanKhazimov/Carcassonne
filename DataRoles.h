#ifndef DATAROLES_H
#define DATAROLES_H

#include <qnamespace.h>

enum DataRoles {
    TilePtr = Qt::UserRole + 1,
    PlayerPtr,
    PlayerName,
    PlayerScore,
    PlayerPlace,
    PlayerColor,
    WheatLead,
    BarrelsLead,
    ClothLead,
    TownLead,
    RoadLead,
    BiggestTown,
    BiggestRoad,
    IsTileFixed,
    TileCopies,
    TileImagePath,
    EventType,
    EventPoints,
    EventObjectType,
    EventObjectSize,
    EventMeepleType,
    EventMeepleTypes
};

#endif // DATAROLES_H
