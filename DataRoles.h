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
    IsTileFixed,
    TileCopies,
    TileImagePath
};

#endif // DATAROLES_H
