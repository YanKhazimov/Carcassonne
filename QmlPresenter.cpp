#include "QmlPresenter.h"
#include "DataRoles.h"
#include "ObjectManager.h"
#include "DataTypes.h"
#include <iostream>
#include <QPoint>
#include <QDebug>
#include <QGuiApplication>
#include <QCursor>

RemainingTilesModel *QmlPresenter::getRemainingTiles()
{
    return &remainingTilesModel;
}

ShuffledDeck *QmlPresenter::getShuffledDeck()
{
    return &shuffledDeck;
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

    populatePlayers({}, {});

    connect(&mapModel, &MapModel::fieldIntegrityCheckRequested, this, &QmlPresenter::checkFieldIntegrity);

    remainingTilesModel.setSource(&deck);
    shuffledDeck.setSource(&deck);
}

void QmlPresenter::AddTiles(std::list<Tile> &tiles)
{
    for (Tile& tile: tiles)
    {
        auto [wheat, barrels, cloth] = tile.resources();
        unassignedWheat += wheat;
        unassignedBarrels += barrels;
        unassignedCloth += cloth;

        connect(&tile, &Tile::objectCompleted, this, &QmlPresenter::scoreCompletedObject);
        connect(&tile, &Tile::objectCompleted, this, &QmlPresenter::scoreCompletionBonuses);
    }

    deck.AddTiles(tiles);
}

Tile *QmlPresenter::getTile(int i)
{
    return shuffledDeck.index(i, 0).data(DataRoles::TilePtr).value<Tile*>();
}

Tile *QmlPresenter::getRemainingTile(int i)
{
    return remainingTilesModel.index(i, 0).data(DataRoles::TilePtr).value<Tile*>();
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

void QmlPresenter::populatePlayers(QVariantList colors, QVariantList names)
{
    Q_ASSERT(colors.length() == names.length());
    for (int i = 0; i < colors.length(); ++i)
    {
        players.AddPlayer(colors[i].value<QColor>(), names[i].value<QString>());
        getPlayer(i)->createAbbeyTile(objectManager);
        connect(getPlayer(i)->getAbbeyTile(), &Tile::objectCompleted, this, &QmlPresenter::scoreCompletedObject);
    }

    if (colors.length() > 0)
    {
        Player* player0 = players.index(0, 0).data(DataRoles::PlayerPtr).value<Player*>();
        player0->setActive(true);
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

        object->freeMeeples({ QmlEnums::MeepleSmall, QmlEnums::MeepleBig, QmlEnums::MeepleBuilder });
    }
}

void QmlPresenter::processBarnPresence(unsigned objectId, int meepleScore)
{
    if (auto object = objectManager.GetObject(objectId); object && object->type == ObjectType::Field)
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

        object->freeMeeples({ QmlEnums::MeepleSmall, QmlEnums::MeepleBig, QmlEnums::MeeplePig });
    }
}

void QmlPresenter::checkFieldIntegrity(unsigned fieldObjectId)
{
    for (auto& barnFieldInitialId: barnFieldInitialIds)
    {
        if (fieldObjectId == objectManager.GetObject(barnFieldInitialId.first)->initialId)
        {
            processBarnPresence(fieldObjectId, 1);
        }
    }
}

void QmlPresenter::scoreFieldMeeples(unsigned fieldObjectId)
{
    processBarnPresence(fieldObjectId, 3);
}

void QmlPresenter::scoreBarnes(unsigned fieldObjectId)
{
    std::vector<unsigned> idsToDelete;
    for (auto& barnFieldInitialId: barnFieldInitialIds)
    {
        auto barnField = objectManager.GetObject(barnFieldInitialId.first);
        if (fieldObjectId == barnField->initialId)
        {
            for (auto& playerIndex: barnFieldInitialId.second)
            {
                getPlayer(playerIndex)->scorePoints(4 * objectManager.countTownsAround(fieldObjectId));
            }

            barnField->freeMeeples({ QmlEnums::MeepleBarn });
            idsToDelete.push_back(barnFieldInitialId.first);
        }
    }

    for (unsigned toDelete: idsToDelete)
    {
        barnFieldInitialIds.erase(toDelete);
    }
}

bool QmlPresenter::isFieldCorner(Tile *tile, unsigned objectId) const
{
    int x = tile->position().x();
    int y = tile->position().y();

    Tile* north = mapModel.nextTileNorth(x, y);
    Tile* west = mapModel.nextTileNorth(x, y);
    Tile* south = mapModel.nextTileSouth(x, y);
    Tile* east = mapModel.nextTileEast(x, y);

    if (tile->NEBarnCornerId() == objectId)
    {
        Tile* northEast = mapModel.nextTileNorthEast(x, y);
        if (north && north->SEBarnCornerId() &&
                east && east->NWBarnCornerId() &&
                northEast && northEast->SWBarnCornerId())
            return true;
    }

    if (tile->SEBarnCornerId() == objectId)
    {
        Tile* southEast = mapModel.nextTileSouthEast(x, y);
        if (south && south->NEBarnCornerId() &&
                east && east->SWBarnCornerId() &&
                southEast && southEast->NWBarnCornerId())
            return true;
    }

    if (tile->SWBarnCornerId() == objectId)
    {
        Tile* southWest = mapModel.nextTileSouthWest(x, y);
        if (south && south->NWBarnCornerId() &&
                west && west->SEBarnCornerId() &&
                southWest && southWest->NEBarnCornerId())
            return true;
    }

    if (tile->NWBarnCornerId() == objectId)
    {
        Tile* northWest = mapModel.nextTileNorthWest(x, y);
        if (north && north->SWBarnCornerId() &&
                west && west->NEBarnCornerId() &&
                northWest && northWest->SEBarnCornerId())
            return true;
    }

    return false;
}

QVariantList QmlPresenter::getPossibleColors() const
{
    return playerColors;
}

void QmlPresenter::processGameEnd(int fixedTilesCount)
{
    QStringList messages;

    if (!allFttingTilesPlayed && shuffledDeck.rowCount() > fixedTilesCount)
    {
        Tile* nextTile = shuffledDeck.index(fixedTilesCount, 0).data(DataRoles::TilePtr).value<Tile*>();
        if (mapModel.fitsCurrentBoard(nextTile))
        {
            return;
        }

        for (int swapCandidate = fixedTilesCount + 1; swapCandidate < shuffledDeck.rowCount(); swapCandidate++)
        {
            nextTile = shuffledDeck.index(swapCandidate, 0).data(DataRoles::TilePtr).value<Tile*>();
            if (mapModel.fitsCurrentBoard(nextTile))
            {
                // make tile at index "swapCandidate" go to index "fixedTilesCount"
                shuffledDeck.forceReorder(swapCandidate, fixedTilesCount);
                return;
            }
        }

        // disallow drawing more regular tiles
        allFttingTilesPlayed = true;
        emit allFttingTilesPlayedChanged();

        messages.append("Оставшиеся фишки невозможно выставить.");
    }

    if (mapModel.canMergeAbbeyTile())
    {
        for (int i = 0; i < players.rowCount(); ++i)
            if (!getAbbeyTile(i)->fixed())
            {
                messages.append("Игроки должны выставить фишки аббатств.");
                emit showMessage(messages.join('\n'), GameState::NewTurn);
                return;
            }
    }

    // game end
    messages.append("Переход к подсчету очков.");
    emit showMessage(messages.join('\n'), GameState::GameEnd);
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
            barnFieldInitialIds[object->initialId].push_back(playerIndex);
        }
    }
}

void QmlPresenter::scoreHighlightedField()
{
    if (auto object = objectManager.GetObject(highlightedObjId); object && object->type == ObjectType::Field)
    {
        scoreFieldMeeples(object->initialId);
        scoreBarnes(object->initialId);
    }
}

bool QmlPresenter::canPlaceMeeple(unsigned objectId, int playerIndex, int type, Tile* tile) const
{
    if (auto object = objectManager.GetObject(objectId); object)
    {
        switch ((QmlEnums::MeepleType)type)
        {
        case QmlEnums::MeepleSmall:
        case QmlEnums::MeepleBig:
            return !object->taken() && object->mostPresentPlayers().empty();
        case QmlEnums::MeepleBarn:
            return object->type == ObjectType::Field
                    && !object->barnPresent()
                    && isFieldCorner(tile, objectId);
        case QmlEnums::MeeplePig:
            return object->type == ObjectType::Field
                    && object->commonMeeplesPresent(playerIndex);
        case QmlEnums::MeepleBuilder:
            return (object->type == ObjectType::Town || object->type == ObjectType::Road)
                    && object->commonMeeplesPresent(playerIndex);
        default:
            std::cerr << "placing unknown meeple type " << type << std::endl;
        }
    }

    return false;
}

bool QmlPresenter::isFieldObject(unsigned objectId) const
{
    return objectManager.GetObject(objectId)->type == ObjectType::Field;
}

void QmlPresenter::setWaitingCursor(bool value)
{
    if (value)
        QGuiApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    else
        QGuiApplication::restoreOverrideCursor();
}
