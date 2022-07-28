#ifndef MAPMODEL_H
#define MAPMODEL_H

#include "Tile.h"
#include <QAbstractTableModel>
#include <vector>

class MapModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int MinX MEMBER minX NOTIFY minMaxChanged)
    Q_PROPERTY(int MaxX MEMBER maxX NOTIFY minMaxChanged)
    Q_PROPERTY(int MinY MEMBER minY NOTIFY minMaxChanged)
    Q_PROPERTY(int MaxY MEMBER maxY NOTIFY minMaxChanged)
    Q_PROPERTY(int MaxCapacity READ maxCapacity CONSTANT)

    std::vector<std::vector<Tile*>> tiles;
    const unsigned size;
    int minX, maxX, minY, maxY;

    Tile* nextTileNorth(int x, int y) const;
    Tile* nextTileSouth(int x, int y) const;
    Tile* nextTileWest(int x, int y) const;
    Tile* nextTileEast(int x, int y) const;

    bool canMergeData(int x, int y, const TileData& tile) const;
    int maxCapacity() const;

public:
    MapModel(unsigned mapSize, QObject* parent = 0);

    Q_INVOKABLE void placeTile(Tile* tile, int x, int y);
    Q_INVOKABLE void fixTile(Tile* tile);
    Q_INVOKABLE bool isAdjacent(int x, int y) const;
    Q_INVOKABLE bool canMergeAsIs(int x, int y, Tile* tile) const;
    Q_INVOKABLE bool canMergeRotated(int x, int y, Tile* tile) const;

signals:
    void minMaxChanged();
};

#endif // MAPMODEL_H
