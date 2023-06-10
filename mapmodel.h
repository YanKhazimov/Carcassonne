#ifndef MAPMODEL_H
#define MAPMODEL_H

#include "Tile.h"
#include <QAbstractTableModel>
#include <vector>

class MapModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int MinX MEMBER minOccupiedX NOTIFY minMaxChanged)
    Q_PROPERTY(int MaxX MEMBER maxOccupiedX NOTIFY minMaxChanged)
    Q_PROPERTY(int MinY MEMBER minOccupiedY NOTIFY minMaxChanged)
    Q_PROPERTY(int MaxY MEMBER maxOccupiedY NOTIFY minMaxChanged)
    Q_PROPERTY(int MinPlayableX MEMBER minPlayableX NOTIFY minMaxChanged)
    Q_PROPERTY(int MaxPlayableX MEMBER maxPlayableX NOTIFY minMaxChanged)
    Q_PROPERTY(int MinPlayableY MEMBER minPlayableY NOTIFY minMaxChanged)
    Q_PROPERTY(int MaxPlayableY MEMBER maxPlayableY NOTIFY minMaxChanged)
    Q_PROPERTY(bool XRangeDefined READ xRangeDefined NOTIFY minMaxChanged)
    Q_PROPERTY(bool YRangeDefined READ yRangeDefined NOTIFY minMaxChanged)
    Q_PROPERTY(int MaxCapacity READ playSize CONSTANT)
    Q_PROPERTY(Tile* LatestTile MEMBER latestTile NOTIFY latestTileChanged)

    std::vector<std::vector<Tile*>> tiles;
    unsigned size = 0;
    int minOccupiedX, maxOccupiedX, minOccupiedY, maxOccupiedY;
    int minPlayableX, maxPlayableX, minPlayableY, maxPlayableY;
    Tile* latestTile = nullptr;

    bool canMergeRegularTile(int x, int y, const TileData& tile) const;
    bool canMergeAbbeyTile(int x, int y) const;
    int playSize() const;
    Tile* tileAt(int x, int y) const;
    bool inPlayableRange(int x, int y) const;
    void updateMinMax(int x, int y);
    bool xRangeDefined() const;
    bool yRangeDefined() const;

    void checkNearbyMonasteryAbbeyCompletion(int newTileX, int newTileY);

public:
    explicit MapModel(QObject* parent = 0);

    Q_INVOKABLE void setSize(unsigned playableSize);
    Q_INVOKABLE void placeTile(Tile* tile, int x, int y);
    void fixTile(Tile* tile);
    Q_INVOKABLE bool isFreeAdjacent(int x, int y) const;
    Q_INVOKABLE bool canMergeAsIs(int x, int y, Tile* tile) const;
    Q_INVOKABLE bool canMergeRotated(int x, int y, Tile* tile) const;
    bool fitsCurrentBoard(Tile* tile) const;
    bool canMergeAbbeyTile() const;
    bool builderObjectProgression(Tile* tile, int activePlayer) const;

    Tile* nextTileNorth(int x, int y) const;
    Tile* nextTileSouth(int x, int y) const;
    Tile* nextTileWest(int x, int y) const;
    Tile* nextTileEast(int x, int y) const;
    Tile* nextTileNorthEast(int x, int y) const;
    Tile* nextTileSouthEast(int x, int y) const;
    Tile* nextTileSouthWest(int x, int y) const;
    Tile* nextTileNorthWest(int x, int y) const;

signals:
    void minMaxChanged();
    void latestTileChanged();
    void fieldIntegrityCheckRequested(unsigned fieldInitialId);
};

#endif // MAPMODEL_H
