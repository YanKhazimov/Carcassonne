#include "MapModel.h"
#include <QPoint>
#include <set>

Tile* MapModel::nextTileNorth(int x, int y) const
{
    return (y + size/2 > 0) ? tileAt(x, y - 1) : nullptr;
}

Tile* MapModel::nextTileSouth(int x, int y) const
{
    return (y + size/2 < size - 1) ? tileAt(x, y + 1) : nullptr;
}

Tile* MapModel::nextTileWest(int x, int y) const
{
    return (x + size/2 > 0) ? tileAt(x - 1, y) : nullptr;
}

Tile* MapModel::nextTileEast(int x, int y) const
{
    return (x + size/2 < size - 1) ? tileAt(x + 1, y) : nullptr;
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
    return inPlayableRange(x, y) &&
            tileAt(x, y) == nullptr &&
           (!nextTileNorth(x, y) || nextTileNorth(x, y)->CanConnect(tile, TileSide::South)) &&
           (!nextTileSouth(x, y) || nextTileSouth(x, y)->CanConnect(tile, TileSide::North)) &&
           (!nextTileWest(x, y) || nextTileWest(x, y)->CanConnect(tile, TileSide::East)) &&
           (!nextTileEast(x, y) || nextTileEast(x, y)->CanConnect(tile, TileSide::West));
}

bool MapModel::canMergeAbbeyTile(int x, int y) const
{
    return tileAt(x, y) == nullptr &&
            nextTileNorth(x, y) && nextTileSouth(x, y) && nextTileWest(x, y) && nextTileEast(x, y);
}

bool MapModel::canMergeAbbeyTile() const
{
    QPair<int, int> xCheckRange { minOccupiedX + 1, maxOccupiedX - 1 };
    QPair<int, int> yCheckRange { minOccupiedY + 1, maxOccupiedY - 1 };
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

std::shared_ptr<const TileObject> MapModel::builderObjectProgression(Tile *tile, int activePlayer) const
{
    const int x = tile->getX();
    const int y = tile->getY();
    
    if (Tile* nextNorth = nextTileNorth(x, y); nextNorth)
    {
        if (auto object = nextNorth->checkConnector(TileSide::South);
            object->meeplePresent({QmlEnums::MeepleType::MeepleBuilder}, activePlayer) &&
            // either the connector on the non-abbey tile extends the existing connector object
            // or the abbey tile is about to close the existing connector object with valency 1
            (!tile->isAbbeyTile() || object->currentObject()->valency == 1))
            return object;
    }
    if (Tile* nextEast = nextTileEast(x, y); nextEast)
    {
        if (auto object = nextEast->checkConnector(TileSide::West);
            object->meeplePresent({QmlEnums::MeepleType::MeepleBuilder}, activePlayer) &&
            // either the connector on the non-abbey tile extends the existing connector object
            // or the abbey tile is about to close the existing connector object with valency 1
            (!tile->isAbbeyTile() || object->currentObject()->valency == 1))
            return object;
    }
    if (Tile* nextSouth = nextTileSouth(x, y); nextSouth)
    {
        if (auto object = nextSouth->checkConnector(TileSide::North);
            object->meeplePresent({QmlEnums::MeepleType::MeepleBuilder}, activePlayer) &&
            // either the connector on the non-abbey tile extends the existing connector object
            // or the abbey tile is about to close the existing connector object with valency 1
            (!tile->isAbbeyTile() || object->currentObject()->valency == 1))
            return object;
    }
    if (Tile* nextWest = nextTileWest(x, y); nextWest)
    {
        if (auto object = nextWest->checkConnector(TileSide::East);
            object->meeplePresent({QmlEnums::MeepleType::MeepleBuilder}, activePlayer) &&
            // either the connector on the non-abbey tile extends the existing connector object
            // or the abbey tile is about to close the existing connector object with valency 1
            (!tile->isAbbeyTile() || object->currentObject()->valency == 1))
            return object;
    }

    return nullptr;
}

int MapModel::playSize() const
{
    // 3x3 is the guaranteed center
    return (size - 3) / 2 + 3;
}

Tile* MapModel::tileAt(int x, int y) const
{
    return tiles[y + size/2][x + size/2];
}

void MapModel::checkNearbyMonasteryAbbeyCompletion(int newTileX, int newTileY)
{
    auto getTilesAround = [this](int x, int y){
        std::vector<Tile*> vec;
        if (Tile* northTile = nextTileNorth(x, y))
        {
            vec.push_back(northTile);
            if (Tile* northWestTile = nextTileWest(northTile->getX(), northTile->getY()))
                vec.push_back(northWestTile);
            if (Tile* northEastTile = nextTileEast(northTile->getX(), northTile->getY()))
                vec.push_back(northEastTile);
        }
        if (Tile* westTile = nextTileWest(x, y))
            vec.push_back(westTile);
        if (Tile* eastTile = nextTileEast(x, y))
            vec.push_back(eastTile);
        if (Tile* southTile = nextTileSouth(x, y))
        {
            vec.push_back(southTile);
            if (Tile* southWestTile = nextTileWest(southTile->getX(), southTile->getY()))
                vec.push_back(southWestTile);
            if (Tile* southEastTile = nextTileEast(southTile->getX(), southTile->getY()))
                vec.push_back(southEastTile);
        }

        return vec;
    };

    std::vector<Tile*> monasteryTiles = getTilesAround(newTileX, newTileY);
    monasteryTiles.push_back(tileAt(newTileX, newTileY));

    for (Tile* monasteryTile: monasteryTiles)
    {
        if (!monasteryTile->hasCentralScorableObject())
            continue;

        std::vector<Tile*> completionTiles = getTilesAround(monasteryTile->getX(), monasteryTile->getY());
        if (completionTiles.size() == 8)
        {
            monasteryTile->markCentralObjectCompleted();
        }
    }
}

MapModel::MapModel(QObject *parent)
    : QObject(parent)
{
}

void MapModel::setSize(unsigned playableSize)
{
    // 3x3 is the guaranteed center
    size = 3 + (playableSize - 3) * 2;
    tiles = { size, std::vector<Tile*>{size, nullptr} };

    minOccupiedX = maxOccupiedX = minOccupiedY = maxOccupiedY = 0;
    maxPlayableX = maxPlayableY = playableSize - 2;
    minPlayableX = -maxPlayableX;
    minPlayableY = -maxPlayableY;
}

bool MapModel::inPlayableRange(int x, int y) const
{
    return minPlayableX <= x && x <= maxPlayableX
            && minPlayableY <= y && y <= maxPlayableY;
}

void MapModel::updateMinMax(int x, int y)
{
    auto updatePlayableX = [this]() {
        int occupied = maxOccupiedX - minOccupiedX + 1;
        int undetermined = playSize() - (occupied + 2);
        if (undetermined >= 0) {
            minPlayableX = minOccupiedX - 1 - undetermined;
            maxPlayableX = maxOccupiedX + 1 + undetermined;
        }
    };

    auto updatePlayableY = [this]() {
        int occupied = maxOccupiedY - minOccupiedY + 1;
        int undetermined = playSize() - (occupied + 2);
        if (undetermined >= 0) {
            minPlayableY = minOccupiedY - 1 - undetermined;
            maxPlayableY = maxOccupiedY + 1 + undetermined;
        }
    };

    if (x < minOccupiedX)
    {
        minOccupiedX = x;
        updatePlayableX();
    }
    else if (x > maxOccupiedX)
    {
        maxOccupiedX = x;
        updatePlayableX();
    }
    else if (y < minOccupiedY)
    {
        minOccupiedY = y;
        updatePlayableY();
    }
    else if (y > maxOccupiedY)
    {
        maxOccupiedY = y;
        updatePlayableY();
    }
    else
    {
        return;
    }

    emit minMaxChanged();
}

bool MapModel::xRangeDefined() const
{
    return (maxPlayableX - minPlayableX) - (maxOccupiedX - minOccupiedX) <= 2;
}

bool MapModel::yRangeDefined() const
{
    return (maxPlayableY - minPlayableY) - (maxOccupiedY - minOccupiedY) <= 2;
}

void MapModel::placeTile(Tile *tile, int x, int y)
{
    Q_ASSERT(inPlayableRange(x, y));

    tile->place(x, y);
}

void MapModel::fixTile(Tile *tile)
{
    const int x = tile->getX();
    const int y = tile->getY();
    tiles[y + size/2][x + size/2] = tile;
    tile->setFixed(true);

    // update minmax
    updateMinMax(x, y);

    // merge objects
    std::set<Tile*> updatedTiles;
    if (Tile* nextNorth = nextTileNorth(x, y); nextNorth)
        nextNorth->Connect(*tile, TileSide::South, updatedTiles);
    if (Tile* nextEast = nextTileEast(x, y); nextEast)
        nextEast->Connect(*tile, TileSide::West, updatedTiles);
    if (Tile* nextSouth = nextTileSouth(x, y); nextSouth)
        nextSouth->Connect(*tile, TileSide::North, updatedTiles);
    if (Tile* nextWest = nextTileWest(x, y); nextWest)
        nextWest->Connect(*tile, TileSide::East, updatedTiles);

    for (Tile* updatedTile: updatedTiles)
    {
        emit updatedTile->objectIdsChanged();
    }

    checkNearbyMonasteryAbbeyCompletion(x, y);

    for (unsigned fieldObjectId: tile->getFieldObjectIds())
    {
        emit fieldIntegrityCheckRequested(fieldObjectId);
    }

    latestTile = tile;
    emit latestTileChanged();
}

bool MapModel::isFreeAdjacent(int x, int y) const
{
    return inPlayableRange(x, y) &&
            tileAt(x, y) == nullptr &&
            (nextTileNorth(x, y) != nullptr ||
            nextTileSouth(x, y) != nullptr ||
            nextTileEast(x, y) != nullptr ||
            nextTileWest(x, y) != nullptr);
}

bool MapModel::canMergeAsIs(int x, int y, Tile *tile) const
{
    return tile && (canMergeRegularTile(x, y, *tile) || tile->isAbbeyTile() && canMergeAbbeyTile(x, y));
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
   QPair<int, int> xCheckRange { qMax(minOccupiedX - 1, minPlayableX), qMin(maxOccupiedX + 1, maxPlayableX) };
   QPair<int, int> yCheckRange { qMax(minOccupiedY - 1, minPlayableY), qMin(maxOccupiedY + 1, maxPlayableY) };
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
