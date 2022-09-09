#ifndef QMLPRESENTER_H
#define QMLPRESENTER_H

#include <QObject>
#include "Tile.h"
#include "TilesModel.h"
#include "mapmodel.h"
#include "PlayersModel.h"

class QmlPresenter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(TilesModel* deck READ getTiles NOTIFY tilesChanged)
    Q_PROPERTY(unsigned HighlightedObjectId READ highlightedObjectId WRITE setHighlightedObjectId NOTIFY highlightedObjectIdChanged)
    Q_PROPERTY(MapModel* mapModel READ getMapModel NOTIFY mapModelChanged)
    Q_PROPERTY(GameState GameState MEMBER gameState NOTIFY gameStateChanged)
    Q_PROPERTY(PlayersModel* Players READ getPlayers CONSTANT)
    Q_PROPERTY(int PlayerCount READ getPlayerCount NOTIFY playerCountChanged)
    Q_PROPERTY(int ActivePlayer READ activePlayer WRITE setActivePlayer NOTIFY activePlayerChanged)
    Q_PROPERTY(ScoreboardModel* SortedPlayers READ getSortedPlayers CONSTANT)
    Q_PROPERTY(int UnassignedWheat MEMBER unassignedWheat NOTIFY unassignedWheatChanged)
    Q_PROPERTY(int UnassignedBarrels MEMBER unassignedBarrels NOTIFY unassignedBarrelsChanged)
    Q_PROPERTY(int UnassignedCloth MEMBER unassignedCloth NOTIFY unassignedClothChanged)
    Q_PROPERTY(int MaxTown MEMBER maxTown NOTIFY maxTownChanged)
    Q_PROPERTY(int MaxRoad MEMBER maxRoad NOTIFY maxRoadChanged)

public:
    enum class GameState {
        NewTurn,
        TileDrawn,
        TilePlaced,
        TileFixed,
        MeeplePlaced
    };
    Q_ENUM(GameState)

private:
    TilesModel deck;
    TilesModel* getTiles();

    MapModel mapModel;
    MapModel* getMapModel();

    ObjectManager& objectManager;
    unsigned highlightedObjId = -1;
    int maxWheat = 0, maxBarrels = 0, maxCloth = 0;
    int maxTown = 0, maxRoad = 0;

    int unassignedWheat = 0;
    int unassignedBarrels = 0;
    int unassignedCloth = 0;

    void addWheatToActivePlayer(int amount);
    void addBarrelsToActivePlayer(int amount);
    void addClothToActivePlayer(int amount);

    GameState gameState;

    PlayersModel players;
    PlayersModel* getPlayers();
    int getPlayerCount() const;
    int activePlayer() const;
    void setActivePlayer(int index);

    ScoreboardModel sortedPlayers;
    ScoreboardModel* getSortedPlayers();

    void setHighlightedObjectId(unsigned id);
    unsigned highlightedObjectId() const;

    void scoreCompletionBonuses(unsigned objectId);
    void scoreTownResorces(unsigned townId);
    void scoreLargestTown(unsigned townId);
    void scoreLongestRoad(unsigned roadId);

    void scoreCompletedObject(unsigned objectId);

public:
    explicit QmlPresenter(ObjectManager& objManager, QObject *parent = nullptr);

    void AddTiles(std::list<Tile> &tiles);
    Q_INVOKABLE Tile* getTile(int i);
    Q_INVOKABLE void highlight(int id);
    Q_INVOKABLE void updateHighlight();
    Q_INVOKABLE void populatePlayers(int number);
    Q_INVOKABLE Player* getPlayer(int i);
    Q_INVOKABLE Tile* getAbbeyTile(int i);
    Q_INVOKABLE void switchActivePlayer();
    Q_INVOKABLE void placeMeeple(int meepleType, int playerIndex, unsigned objectId, Tile *tile);

signals:
    void tilesChanged();
    void highlightedObjectIdChanged();
    void mapModelChanged();
    void gameStateChanged();
    void playerCountChanged();
    void activePlayerChanged();
    void unassignedWheatChanged();
    void unassignedBarrelsChanged();
    void unassignedClothChanged();
    void maxTownChanged();
    void maxRoadChanged();
};

#endif // QMLPRESENTER_H
