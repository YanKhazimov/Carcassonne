#include "QmlPresenter.h"
#include "DataRoles.h"
#include "ObjectManager.h"
#include "DataTypes.h"
#include <QDebug>

TilesModel *QmlPresenter::getTiles()
{
    return &deck;
}

MapModel *QmlPresenter::getMapModel()
{
    return &mapModel;
}

void QmlPresenter::addWheatToActivePlayer(int amount)
{
    Player* acivePlayerPtr = getPlayer(activePlayer());
    acivePlayerPtr->addWheat(amount);

    maxWheat = qMax(maxWheat, acivePlayerPtr->getWheat());

    for (int i = 0; i < players.rowCount(); ++i)
    {
        Player* player = getPlayer(i);
        player->setWheatLead(player->getWheat() == maxWheat);
    }
}

void QmlPresenter::addBarrelsToActivePlayer(int amount)
{
    Player* acivePlayerPtr = getPlayer(activePlayer());
    acivePlayerPtr->addBarrels(amount);

    maxBarrels = qMax(maxBarrels, acivePlayerPtr->getBarrels());

    for (int i = 0; i < players.rowCount(); ++i)
    {
        Player* player = getPlayer(i);
        player->setBarrelsLead(player->getBarrels() == maxBarrels);
    }
}

void QmlPresenter::addClothToActivePlayer(int amount)
{
    Player* acivePlayerPtr = getPlayer(activePlayer());
    acivePlayerPtr->addCloth(amount);

    maxCloth = qMax(maxCloth, acivePlayerPtr->getCloth());

    for (int i = 0; i < players.rowCount(); ++i)
    {
        Player* player = getPlayer(i);
        player->setClothLead(player->getCloth() == maxCloth);
    }
}

PlayersModel *QmlPresenter::getPlayers()
{
    return &players;
}

int QmlPresenter::getPlayerCount() const
{
    return players.rowCount();
}

int QmlPresenter::activePlayer() const
{
    for (int i = 0; i < players.rowCount(); ++i)
    {
        Player* player = players.index(i, 0).data(DataRoles::PlayerPtr).value<Player*>();
        if (player->isActive())
            return i;
    }

    return players.rowCount();
}

void QmlPresenter::setActivePlayer(int index)
{
    int currentActivePlayer = activePlayer();
    if (currentActivePlayer != index)
    {
        getPlayer(currentActivePlayer)->setActive(false);
        getPlayer(index)->setActive(true);
        emit activePlayerChanged();
    }
}

ScoreboardModel *QmlPresenter::getSortedPlayers()
{
    return &sortedPlayers;
}

void QmlPresenter::setHighlightedObjectId(unsigned id)
{
    if (highlightedObjId != id)
    {
        highlightedObjId = id;
        emit highlightedObjectIdChanged();
    }
}

unsigned QmlPresenter::highlightedObjectId() const
{
    return highlightedObjId;
}

void QmlPresenter::scoreCompletionBonuses(unsigned objectId)
{
    auto object = objectManager.GetObject(objectId);
    if (object->type == ObjectType::Town)
    {
        scoreTownResorces(objectId);
        scoreLargestTown(objectId);
    }
    else if (object->type == ObjectType::Road)
    {
        scoreLongestRoad(objectId);
    }
}

QmlPresenter::QmlPresenter(ObjectManager& objManager, QObject *parent)
    : QObject(parent), mapModel(13), objectManager(objManager), gameState(GameState::NewTurn)
{
    connect(&players, &QAbstractListModel::rowsInserted, this, &QmlPresenter::playerCountChanged);

    sortedPlayers.setSource(&players);

    populatePlayers(4);

    Player* player0 = players.index(0, 0).data(DataRoles::PlayerPtr).value<Player*>();
    player0->setActive(true);

    connect(&mapModel, &MapModel::fieldIntegrityCheckRequested, this, &QmlPresenter::checkFieldIntegrity);
}

void QmlPresenter::AddTiles(std::list<Tile> &tiles)
{
    for (Tile& tile: tiles)
    {
        deck.AddTile(&tile);

        auto [wheat, barrels, cloth] = tile.resources();
        unassignedWheat += wheat;
        unassignedBarrels += barrels;
        unassignedCloth += cloth;

        connect(&tile, &Tile::objectCompleted, this, &QmlPresenter::scoreCompletedObject);
        connect(&tile, &Tile::objectCompleted, this, &QmlPresenter::scoreCompletionBonuses);
    }
}

Tile *QmlPresenter::getTile(int i)
{
    return deck.index(i, 0).data(DataRoles::TilePtr).value<Tile*>();
}

void QmlPresenter::highlight(int id)
{
    auto targetObject = objectManager.GetObject(id);
    setHighlightedObjectId(targetObject->initialId);
}

void QmlPresenter::updateHighlight()
{
    highlight(objectManager.GetObject(highlightedObjId)->initialId);
}

void QmlPresenter::populatePlayers(int number)
{
    for (int i = 0; i < number; ++i)
    {
        players.AddPlayer(playerColors[i]);
        getPlayer(i)->createAbbeyTile(objectManager);
        connect(getPlayer(i)->getAbbeyTile(), &Tile::objectCompleted, this, &QmlPresenter::scoreCompletedObject);
    }

    emit players.dataChanged(players.index(0, 0), players.index(players.rowCount() - 1, 0), {DataRoles::PlayerScore});
}

Player *QmlPresenter::getPlayer(int i)
{
    return players.index(i, 0).data(DataRoles::PlayerPtr).value<Player*>();
}

Tile *QmlPresenter::getAbbeyTile(int i)
{
    return getPlayer(i)->getAbbeyTile();
}

void QmlPresenter::scoreTownResorces(unsigned townId)
{
    auto [wheat, barrels, cloth] = objectManager.getTownResources(townId);

    if (wheat > 0)
    {
        addWheatToActivePlayer(wheat);
        unassignedWheat -= wheat;
        emit unassignedWheatChanged();
    }

    if (barrels > 0)
    {
        addBarrelsToActivePlayer(barrels);
        unassignedBarrels -= barrels;
        emit unassignedBarrelsChanged();
    }

    if (cloth > 0)
    {
        addClothToActivePlayer(cloth);
        unassignedCloth -= cloth;
        emit unassignedClothChanged();
    }
}

void QmlPresenter::scoreLargestTown(unsigned townId)
{
    int townSize = objectManager.countObjectTiles(townId);

    if (townSize > maxTown)
    {
        maxTown = townSize;
        emit maxTownChanged();

        int currentActivePlayer = activePlayer();

        for (int i = 0; i < players.rowCount(); ++i)
        {
            Player* player = getPlayer(i);
            player->setTownLead(i == currentActivePlayer);
        }
    }
}

void QmlPresenter::scoreLongestRoad(unsigned roadId)
{
    int roadSize = objectManager.countObjectTiles(roadId);

    if (roadSize > maxRoad)
    {
        maxRoad = roadSize;
        emit maxRoadChanged();

        int currentActivePlayer = activePlayer();

        for (int i = 0; i < players.rowCount(); ++i)
        {
            Player* player = getPlayer(i);
            player->setRoadLead(i == currentActivePlayer);
        }
    }
}

void QmlPresenter::scoreCompletedObject(unsigned objectId)
{
    if (auto object = objectManager.GetObject(objectId); object)
    {
        int points = objectManager.getPoints(objectId);
        std::vector<int> mostPresentPlayers = object->mostPresentPlayers();

        for (auto playerIndex: mostPresentPlayers)
        {
            getPlayer(playerIndex)->scorePoints(points);
        }

        object->freeRemovableMeeples();
    }
}

void QmlPresenter::processBarnPresence(unsigned objectId, int meepleScore)
{
    if (auto object = objectManager.GetObject(objectId); object)
    {
        std::vector<int> mostPresentPlayers = object->mostPresentPlayers();
        if (!mostPresentPlayers.empty())
        {
            std::set<int> pigs = object->pigs();
            int fieldTowns = objectManager.countTownsAround(object->initialId);

            for (auto playerIndex: mostPresentPlayers)
            {
                bool pig = pigs.find(playerIndex) != pigs.end();
                getPlayer(playerIndex)->scorePoints(fieldTowns * (pig ? (meepleScore + 1) : meepleScore));
            }
        }

        object->freeRemovableMeeples();
    }
}

void QmlPresenter::checkFieldIntegrity(unsigned fieldObjectId)
{
    for (unsigned barnFieldInitialId: barnFieldInitialIds)
    {
        if (fieldObjectId == objectManager.GetObject(barnFieldInitialId)->initialId)
        {
            processBarnPresence(fieldObjectId, 1);
        }
    }
}

void QmlPresenter::switchActivePlayer()
{
    setActivePlayer((activePlayer() + 1) % players.rowCount());
}

void QmlPresenter::placeMeeple(int meepleType, int playerIndex, unsigned objectId, Tile* tile)
{
    if (auto object = objectManager.GetObject(objectId); object)
    {
        object->addMeeple(playerIndex, (QmlEnums::MeepleType)meepleType, tile);

        if (object->isCompleted())
        {
            scoreCompletedObject(object->initialId);
        }

        if ((QmlEnums::MeepleType)meepleType == QmlEnums::MeepleType::MeepleBarn)
        {
            processBarnPresence(object->initialId, 3);
            barnFieldInitialIds.insert(object->initialId);
        }
    }
}
