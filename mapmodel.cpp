#include "mapmodel.h"
#include <QPoint>

Tile* MapModel::nextTileNorth(int x, int y) const
{
    return (y + size/2 > 0) ? tiles[y + size/2 - 1][x + size/2] : nullptr;
}

Tile* MapModel::nextTileSouth(int x, int y) const
{
    return (y + size/2 + 1 < size) ? tiles[y + size/2 + 1][x + size/2] : nullptr;
}

Tile* MapModel::nextTileWest(int x, int y) const
{
    return (x + size/2 > 0) ? tiles[y + size/2][x + size/2 - 1] : nullptr;
}

Tile* MapModel::nextTileEast(int x, int y) const
{
    return (x + size/2 + 1 < size) ? tiles[y + size/2][x + size/2 + 1] : nullptr;
}

bool MapModel::canMergeData(int x, int y, const TileData &tile) const
{
    return tiles[y + size/2][x + size/2] == nullptr &&
            (!nextTileNorth(x, y) || nextTileNorth(x, y)->CanConnect(tile, Direction::South)) &&
            (!nextTileSouth(x, y) || nextTileSouth(x, y)->CanConnect(tile, Direction::North)) &&
            (!nextTileWest(x, y) || nextTileWest(x, y)->CanConnect(tile, Direction::East)) &&
            (!nextTileEast(x, y) || nextTileEast(x, y)->CanConnect(tile, Direction::West));
}

int MapModel::maxCapacity() const
{
    return size/2;
}

MapModel::MapModel(unsigned mapSize, QObject *parent)
    : QObject(parent), tiles {mapSize, std::vector<Tile*>{mapSize, nullptr}},
      size(mapSize), minX(0), maxX(0), minY(0), maxY(0)
{
}

void MapModel::placeTile(Tile *tile, int x, int y)
{
    Q_ASSERT(y + size/2 >= 0 && y + size/2 >= 0 && y + size/2 < size && y + size/2 < size);

    tile->place(x, y);
}

void MapModel::fixTile(Tile *tile)
{
    QPoint position = tile->position();
    tiles[position.y() + size/2][position.x() + size/2] = tile;
    tile->setFixed(true);

    // update minmax
    if (position.x() < minX || position.x() > maxX)
    {
        minX = std::min(minX, position.x());
        maxX = std::max(maxX, position.x());
        emit minMaxChanged();
    }
    else if (position.y() < minY || position.y() > maxY) // one or the other, cannot expand diagonally
    {
        minY = std::min(minY, position.y());
        maxY = std::max(maxY, position.y());
        emit minMaxChanged();
    }

    // merge objects
    if (Tile* nextNorth = nextTileNorth(position.x(), position.y()); nextNorth)
        nextNorth->Connect(*tile, Direction::South);
    if (Tile* nextEast = nextTileEast(position.x(), position.y()); nextEast)
        nextEast->Connect(*tile, Direction::West);
    if (Tile* nextSouth = nextTileSouth(position.x(), position.y()); nextSouth)
        nextSouth->Connect(*tile, Direction::North);
    if (Tile* nextWest = nextTileWest(position.x(), position.y()); nextWest)
        nextWest->Connect(*tile, Direction::East);

    // todo try precise emission
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (tiles[i][j])
                emit tiles[i][j]->objectIdsChanged();
        }
    }
}

bool MapModel::isAdjacent(int x, int y) const
{
    return tiles[y + size/2][x + size/2] == nullptr &&
            ((x + size/2 + 1 < size && tiles[y + size/2][x + size/2 + 1] != nullptr) ||
            (y + size/2 + 1 < size && tiles[y + size/2 + 1][x + size/2] != nullptr) ||
            (x + size/2 > 0 && tiles[y + size/2][x + size/2 - 1] != nullptr) ||
            (y + size/2 > 0 && tiles[y + size/2 - 1][x + size/2] != nullptr));
}

bool MapModel::canMergeAsIs(int x, int y, Tile *tile) const
{
    return tile && canMergeData(x, y, *tile);
}

bool MapModel::canMergeRotated(int x, int y, Tile *tile) const
{
    if (!tile)
        return false;

    TileData copy = tile->copy();

    return canMergeData(x, y, copy.rotateClockwise()) ||
            canMergeData(x, y, copy.rotateClockwise()) ||
            canMergeData(x, y, copy.rotateClockwise());
}
