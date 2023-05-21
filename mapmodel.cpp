#include "mapmodel.h"
#include <QPoint>
#include <set>

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

Tile *MapModel::nextTileNorthEast(int x, int y) const
{
    return nextTileNorth(x, y) ? nextTileEast(x, y - 1) : nullptr;
}

Tile *MapModel::nextTileSouthEast(int x, int y) const
{
    return nextTileSouth(x, y) ? nextTileEast(x, y + 1) : nullptr;
}

Tile *MapModel::nextTileSouthWest(int x, int y) const
{
    return nextTileSouth(x, y) ? nextTileWest(x, y + 1) : nullptr;
}

Tile *MapModel::nextTileNorthWest(int x, int y) const
{
    return nextTileNorth(x, y) ? nextTileWest(x, y - 1) : nullptr;
}

bool MapModel::canMergeRegularTile(int x, int y, const TileData &tile) const
{
    return tiles[y + size/2][x + size/2] == nullptr &&
            (!nextTileNorth(x, y) || nextTileNorth(x, y)->CanConnect(tile, Direction::South)) &&
            (!nextTileSouth(x, y) || nextTileSouth(x, y)->CanConnect(tile, Direction::North)) &&
            (!nextTileWest(x, y) || nextTileWest(x, y)->CanConnect(tile, Direction::East)) &&
            (!nextTileEast(x, y) || nextTileEast(x, y)->CanConnect(tile, Direction::West));
}

bool MapModel::canMergeAbbeyTile(int x, int y) const
{
    return tiles[y + size/2][x + size/2] == nullptr &&
            nextTileNorth(x, y) && nextTileSouth(x, y) && nextTileWest(x, y) && nextTileEast(x, y);
}

bool MapModel::canMergeAbbeyTile() const
{
    QPair<int, int> xCheckRange {minX + 1, maxX - 1};
    QPair<int, int> yCheckRange {minY + 1, maxY - 1};
    for (int x = xCheckRange.first; x <= xCheckRange.second; ++x)
        for (int y = yCheckRange.first; y <= yCheckRange.second; ++y)
        {
            if (canMergeAbbeyTile(x, y))
            {
                return true;
            }
        }

    return false;
}

int MapModel::maxCapacity() const
{
    return size/2;
}

void MapModel::checkNearbyMonasteryAbbeyCompletion(int newTileX, int newTileY)
{
    auto getTilesAround = [this](int x, int y){
        std::vector<Tile*> vec;
        if (Tile* northTile = nextTileNorth(x, y))
        {
            vec.push_back(northTile);
            if (Tile* northWestTile = nextTileWest(northTile->position().x(), northTile->position().y()))
                vec.push_back(northWestTile);
            if (Tile* northEastTile = nextTileEast(northTile->position().x(), northTile->position().y()))
                vec.push_back(northEastTile);
        }
        if (Tile* westTile = nextTileWest(x, y))
            vec.push_back(westTile);
        if (Tile* eastTile = nextTileEast(x, y))
            vec.push_back(eastTile);
        if (Tile* southTile = nextTileSouth(x, y))
        {
            vec.push_back(southTile);
            if (Tile* southWestTile = nextTileWest(southTile->position().x(), southTile->position().y()))
                vec.push_back(southWestTile);
            if (Tile* southEastTile = nextTileEast(southTile->position().x(), southTile->position().y()))
                vec.push_back(southEastTile);
        }

        return vec;
    };

    std::vector<Tile*> monasteryTiles = getTilesAround(newTileX, newTileY);
    monasteryTiles.push_back(tiles[newTileY + size/2][newTileX + size/2]);

    for (Tile* monasteryTile: monasteryTiles)
    {
        if (!monasteryTile->hasCentralScorableObject())
            continue;

        std::vector<Tile*> completionTiles = getTilesAround(monasteryTile->position().x(), monasteryTile->position().y());
        if (completionTiles.size() == 8)
        {
            monasteryTile->markCentralObjectCompleted();
        }
    }
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
    std::set<Tile*> updatedTiles;
    if (Tile* nextNorth = nextTileNorth(position.x(), position.y()); nextNorth)
        nextNorth->Connect(*tile, Direction::South, updatedTiles);
    if (Tile* nextEast = nextTileEast(position.x(), position.y()); nextEast)
        nextEast->Connect(*tile, Direction::West, updatedTiles);
    if (Tile* nextSouth = nextTileSouth(position.x(), position.y()); nextSouth)
        nextSouth->Connect(*tile, Direction::North, updatedTiles);
    if (Tile* nextWest = nextTileWest(position.x(), position.y()); nextWest)
        nextWest->Connect(*tile, Direction::East, updatedTiles);

    for (Tile* tile: updatedTiles)
    {
        emit tile->objectIdsChanged();
    }

    checkNearbyMonasteryAbbeyCompletion(position.x(), position.y());

    for (unsigned fieldObjectId: tile->getFieldObjectIds())
    {
        emit fieldIntegrityCheckRequested(fieldObjectId);
    }

    latestTile = tile;
    emit latestTileChanged();
}

bool MapModel::isFreeAdjacent(int x, int y) const
{
    return tiles[y + size/2][x + size/2] == nullptr &&
            ((x + size/2 + 1 < size && tiles[y + size/2][x + size/2 + 1] != nullptr) ||
            (y + size/2 + 1 < size && tiles[y + size/2 + 1][x + size/2] != nullptr) ||
            (x + size/2 > 0 && tiles[y + size/2][x + size/2 - 1] != nullptr) ||
            (y + size/2 > 0 && tiles[y + size/2 - 1][x + size/2] != nullptr));
}

bool MapModel::canMergeAsIs(int x, int y, Tile *tile) const
{
    return tile && (canMergeRegularTile(x, y, *tile) || tile->isAbbeyTile && canMergeAbbeyTile(x, y));
}

bool MapModel::canMergeRotated(int x, int y, Tile *tile) const
{
    if (!tile)
        return false;

    TileData copy = tile->copy();

    return canMergeRegularTile(x, y, copy.rotateClockwise()) ||
            canMergeRegularTile(x, y, copy.rotateClockwise()) ||
            canMergeRegularTile(x, y, copy.rotateClockwise());
}

bool MapModel::fitsCurrentBoard(Tile *tile) const
{
   QPair<int, int> xCheckRange {qMin(minX - 1, -maxCapacity()), qMax(maxX + 1, maxCapacity())};
   QPair<int, int> yCheckRange {qMin(minY - 1, -maxCapacity()), qMax(maxY + 1, maxCapacity())};
   for (int x = xCheckRange.first; x <= xCheckRange.second; ++x)
       for (int y = yCheckRange.first; y <= yCheckRange.second; ++y)
       {
           if (isFreeAdjacent(x, y))
           {
               if (canMergeAsIs(x, y, tile) || canMergeRotated(x, y, tile))
               {
                   return true;
               }
           }
       }

   return false;
}
