#ifndef QMLPRESENTER_H
#define QMLPRESENTER_H

#include <QObject>
#include <QJsonObject>
#include "Tile.h"
#include "TilesModel.h"
#include "MapModel.h"
#include "PlayersModel.h"
#include "RemainingTilesModel.h"
#include "ShuffledDeck.h"
#include "ScoreboardModel.h"

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
    Q_PROPERTY(QVariantList PossibleColors READ getPossibleColors CONSTANT)
    Q_PROPERTY(RemainingTilesModel* remainingTilesModel READ getRemainingTiles NOTIFY remainingTilesChanged)
    Q_PROPERTY(bool AllFttingTilesPlayed MEMBER allFttingTilesPlayed NOTIFY allFttingTilesPlayedChanged)
    Q_PROPERTY(QVariantList ScorableFields READ getScorableFields NOTIFY scorableFieldsChanged)
    Q_PROPERTY(QAbstractListModel* TurnLog READ getTurnLogRecords NOTIFY gameLogChanged)

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
    std::vector<std::shared_ptr<Tile>> deserializeTiles(const QJsonArray &json);
    void setDeck(const std::vector<std::shared_ptr<Tile>>& tiles);
    TilesModel deck;

    RemainingTilesModel remainingTilesModel;
    RemainingTilesModel* getRemainingTiles();

    ShuffledDeck shuffledDeck;
    ShuffledDeck* getShuffledDeck();

    MapModel mapModel;
    MapModel* getMapModel();

    unsigned highlightedObjId = -1;
    int maxResources[QmlEnums::BonusType::MaxResourceType];
    int maxTown = 0, maxRoad = 0;

    int unassignedWheat = 0;
    int unassignedBarrels = 0;
    int unassignedCloth = 0;

    void addResourceToActivePlayer(int amount, QmlEnums::BonusType resourceType);

    GameState gameState;

    void deserializePlayers(const QJsonArray &json, std::vector<Tile *> &abbeyTiles);
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
    void addMeepleToObject(std::shared_ptr<TileObject>& object, QmlEnums::MeepleType meepleType, int playerIndex, qreal tileXRatio, qreal tileYRatio);
    void removeMeepleFromObject(std::shared_ptr<TileObject>& object, const std::set<QmlEnums::MeepleType>& typesToRemove);

    int bonusTurn = -1;

    QAbstractListModel* getTurnLogRecords();

    void updateScorableFieldIds();

    bool abbeyStage = false;

    void onObjectCompleted(unsigned objectId);
    void logObjectCompletion(unsigned objectId);
    void onTileFixed(Tile *tile);
    bool processGameEnd(int fixedTilesCount);
    QJsonObject serializeGameState();
    void deserializeGameState(const QJsonObject &json);
    void connectTiles(const std::vector<std::shared_ptr<Tile>>& tiles);
    void calculateUnassignedResources(const std::vector<std::shared_ptr<Tile>>& tiles);

public:
    explicit QmlPresenter(QObject *parent = nullptr);

    Q_INVOKABLE void createRandomTiles();
    Q_INVOKABLE Tile* getTile(int i);
    Q_INVOKABLE Tile* getRemainingTile(int i);
    Q_INVOKABLE void highlight(int id);
    Q_INVOKABLE void updateHighlight();
    Q_INVOKABLE void populatePlayers(QVariantList colors, QVariantList names);
    Q_INVOKABLE Player* getPlayer(int i);
    Q_INVOKABLE Tile* getAbbeyTile(int i);
    Q_INVOKABLE void passTurn(int fixedTilesCount);
    Q_INVOKABLE void placeMeeple(int meepleType, int playerIndex, unsigned objectId, qreal tileXRatio, qreal tileYRatio);
    Q_INVOKABLE void scoreField(unsigned fieldCurrentId);
    Q_INVOKABLE bool canPlaceMeeple(unsigned objectId, int playerIndex, int type, Tile *tile) const;
    Q_INVOKABLE bool isFieldObject(unsigned objectId) const;
    Q_INVOKABLE void setWaitingCursor(bool value);
    Q_INVOKABLE void fixTile(Tile* tile);
    Q_INVOKABLE void saveGame();
    Q_INVOKABLE void loadGame();
    Q_INVOKABLE QList<MeepleInfo> activeMeeples();

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
    void remainingTilesChanged();
    void allFttingTilesPlayedChanged();
    void showMessage(QString message, GameState stateToSet);
    void scorableFieldsChanged();
    void gameLogChanged();
    void pointsScored(int points, QColor playerColor, Tile* tile);
    void gameObjectsLoaded();
};

#endif // QMLPRESENTER_H
