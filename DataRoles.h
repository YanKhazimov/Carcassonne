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
    TurnIndex,
    TurnActions,
    ActionEffects,
    EventType,
    EventPoints,
    EventObjectType,
    EventObjectSize,
    EventObjectId,
    EventMeepleType,
    EventMeeplePlayer,
    EventMeeples,
    EventResourceType,
    EventTile,
    CurrentTurnSeconds,
    PastTurnsSeconds
};

#endif // DATAROLES_H
