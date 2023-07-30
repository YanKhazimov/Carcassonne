#ifndef QMLPRESENTER_H
#define QMLPRESENTER_H

#include <QObject>
#include "Tile.h"
#include "TilesModel.h"
#include "mapmodel.h"
#include "PlayersModel.h"
#include "RemainingTilesModel.h"
#include "ShuffledDeck.h"

class QmlPresenter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ShuffledDeck* deck READ getShuffledDeck NOTIFY tilesChanged)
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
    Q_PROPERTY(qreal TilePictureOpacity MEMBER tilePictureOpacity NOTIFY tilePictureOpacityChanged)
    Q_PROPERTY(QVariantList PossibleColors READ getPossibleColors CONSTANT)
    Q_PROPERTY(RemainingTilesModel* remainingTilesModel READ getRemainingTiles NOTIFY remainingTilesChanged)
    Q_PROPERTY(bool AllFttingTilesPlayed MEMBER allFttingTilesPlayed NOTIFY allFttingTilesPlayedChanged)
    Q_PROPERTY(QVariantList ScorableFields READ getScorableFields NOTIFY scorableFieldsChanged)
    Q_PROPERTY(bool BuilderBonus MEMBER builderBonus CONSTANT)
    Q_PROPERTY(QAbstractListModel* GameLog READ getLogMessages NOTIFY gameLogChanged)

public:
    enum class GameState {
        Initialization,
        NewTurn,
        TileDrawn,
        TilePlaced,
        TileFixed,
        MeeplePlaced,
        GameEnd
    };
    Q_ENUM(GameState)

private:
    TilesModel deck;

    RemainingTilesModel remainingTilesModel;
    RemainingTilesModel* getRemainingTiles();

    ShuffledDeck shuffledDeck;
    ShuffledDeck* getShuffledDeck();

    MapModel mapModel;
    MapModel* getMapModel();

    unsigned highlightedObjId = -1;
    int maxWheat = 0, maxBarrels = 0, maxCloth = 0;
    int maxTown = 0, maxRoad = 0;

    int unassignedWheat = 0;
    int unassignedBarrels = 0;
    int unassignedCloth = 0;

    qreal tilePictureOpacity = 0.5;

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
    void scoreFieldMeeples(unsigned objectId, int meepleScore);

    // initial id -> player indecies
    std::map<unsigned, std::vector<int>> barnFieldInitialIds;

    void checkFieldIntegrity(unsigned fieldObjectId);
    void scoreBarnes(unsigned fieldObjectId);

    bool isFieldCorner(Tile* tile, unsigned objectId) const;

    QVariantList getPossibleColors() const;

    bool allFttingTilesPlayed = false;

    std::set<unsigned> scorableFields;
    QVariantList getScorableFields() const;
    void addMeepleToObject(std::shared_ptr<MapObjectData>& object, QmlEnums::MeepleType meepleType, int playerIndex, Tile* tile);
    std::list<MapObjectData::MeepleInfo> removeMeepleFromObject(std::shared_ptr<MapObjectData>& object, const std::set<QmlEnums::MeepleType>& typesToRemove);

    bool builderBonus = false;

    QAbstractListModel* getLogMessages();

    void updateScorableFieldIds();

    bool abbeyStage = false;

public:
    explicit QmlPresenter(QObject *parent = nullptr);

    void AddTiles(std::list<Tile> &tiles);
    Q_INVOKABLE Tile* getTile(int i);
    Q_INVOKABLE Tile* getRemainingTile(int i);
    Q_INVOKABLE void highlight(int id);
    Q_INVOKABLE void updateHighlight();
    Q_INVOKABLE void populatePlayers(QVariantList colors, QVariantList names);
    Q_INVOKABLE Player* getPlayer(int i);
    Q_INVOKABLE Tile* getAbbeyTile(int i);
    Q_INVOKABLE void passTurn(int fixedTilesCount);
    Q_INVOKABLE void placeMeeple(int meepleType, int playerIndex, unsigned objectId, Tile *tile);
    Q_INVOKABLE void scoreField(unsigned fieldCurrentId);
    Q_INVOKABLE bool canPlaceMeeple(unsigned objectId, int playerIndex, int type, Tile *tile) const;
    Q_INVOKABLE bool isFieldObject(unsigned objectId) const;
    Q_INVOKABLE void setWaitingCursor(bool value);
    bool processGameEnd(int fixedTilesCount);
    Q_INVOKABLE void fixTile(Tile* tile);

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
    void tilePictureOpacityChanged();
    void remainingTilesChanged();
    void allFttingTilesPlayedChanged();
    void showMessage(QString message, GameState stateToSet);
    void scorableFieldsChanged();
    void gameLogChanged();
};

#endif // QMLPRESENTER_H
