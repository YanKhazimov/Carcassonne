#include "QmlPresenter.h"
#include "DataRoles.h"
#include "ObjectManager.h"
#include "DataTypes.h"
#include "Logger.h"
#include "DeckBuilder.h"
#include <iostream>
#include <QPoint>
#include <QDebug>
#include <QGuiApplication>
#include <QCursor>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

std::vector<std::shared_ptr<Tile>> QmlPresenter::deserializeTiles(const QJsonArray &json)
{
    return DeckBuilder::BuildDeck(json);
}

void QmlPresenter::setDeck(const std::vector<std::shared_ptr<Tile>>& tiles)
{
    shuffledDeck.setRandom(false);
    deck.setTiles(tiles);
    connectTiles(tiles);
}

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

void QmlPresenter::addResourceToActivePlayer(int amount, QmlEnums::BonusType resourceType)
{
    Player* activePlayerPtr = getPlayer(activePlayer());
    activePlayerPtr->addResource(amount, resourceType);

    maxResources[resourceType] = qMax(maxResources[resourceType], activePlayerPtr->getResource(resourceType));

    for (int i = 0; i < players.rowCount(); ++i)
    {
        Player* player = getPlayer(i);
        player->setResourceLead(resourceType, player->getResource(resourceType) == maxResources[resourceType]);
    }

    if (maxResources[resourceType] == activePlayerPtr->getResource(resourceType))
    {
        // took or extended the lead -> log it
        Logger::instance()->logEffect(std::make_shared<ResourceLeadLogRecord>(activePlayerPtr->getColor(), activePlayerPtr->getName(),
                                                                              maxResources[resourceType], amount, resourceType));
    }
    else
    {
        // no lead -> log gathered amount
        Logger::instance()->logEffect(std::make_shared<ResourceLogRecord>(activePlayerPtr->getColor(), activePlayerPtr->getName(),
                                                                          amount, resourceType));
    }
}

void QmlPresenter::deserializePlayers(const QJsonArray &json, std::vector<Tile*>& abbeyTiles)
{
    players.resetPlayers(json);
    abbeyTiles.resize(players.rowCount());

    for (int i = 0; i < players.rowCount(); ++i)
    {
        auto abbeyTile = getPlayer(i)->getAbbeyTile();
        connect(abbeyTile, &Tile::objectCompleted, this, &QmlPresenter::onObjectCompleted);
        connect(abbeyTile, &Tile::isFixedChanged, this, [abbeyTile, this]() {
            if (abbeyTile->fixed())
                onTileFixed(abbeyTile);
        });
        abbeyTiles[i] = abbeyTile;
    }

    // emit players.dataChanged(players.index(0, 0), players.index(players.rowCount() - 1, 0), {DataRoles::PlayerScore});
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
        if (player && player->isActive())
            return i;
    }

    return -1;
}

void QmlPresenter::setActivePlayer(int index)
{
    int currentActivePlayer = activePlayer();
    if (currentActivePlayer != index)
    {
        if (Player* prevPlayer = getPlayer(currentActivePlayer); prevPlayer)
            prevPlayer->setActive(false);
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
    auto object = ObjectManager::instance()->GetAggregateObject(objectId);
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

QmlPresenter::QmlPresenter(QObject *parent)
    : QObject(parent), gameState(GameState::Initialization), maxResources {-1, 0, 0, 0}
{
    // connect(&players, &QAbstractListModel::rowsInserted, this, &QmlPresenter::playerCountChanged);
    connect(&players, &QAbstractListModel::modelReset, this, &QmlPresenter::playerCountChanged);

    sortedPlayers.setSource(&players);

    populatePlayers({}, {});

    connect(&mapModel, &MapModel::fieldIntegrityCheckRequested, this, &QmlPresenter::checkFieldIntegrity);

    remainingTilesModel.setSource(&deck);
    shuffledDeck.setSource(&deck);
}

void QmlPresenter::createRandomTiles()
{
    std::vector<std::shared_ptr<Tile>> tiles = DeckBuilder::BuildDeck("img/pnp/tiles", "png");
    shuffledDeck.setRandom(true);
    deck.setTiles(tiles);
    connectTiles(tiles);
    calculateUnassignedResources(tiles);

    // for (int i = 0; i < shuffledDeck.rowCount(); ++i)
    // {
    //     Tile* tt = shuffledDeck.index(i, 0).data(DataRoles::TilePtr).value<Tile*>();
    //     qWarning() << tt->property("Picture").toString() + " ";
    // }
    // qWarning();
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
    auto targetObject = ObjectManager::instance()->GetAggregateObject(id);
    setHighlightedObjectId(targetObject->initialId);
}

void QmlPresenter::updateHighlight()
{
    highlight(ObjectManager::instance()->GetAggregateObject(highlightedObjId)->initialId);
}

void QmlPresenter::populatePlayers(QVariantList colors, QVariantList names)
{
    // Q_ASSERT(colors.length() == names.length());
    players.resetPlayers(colors, names);

    for (int i = 0; i < players.rowCount(); ++i)
    {
        // players.AddPlayer(colors[i].value<QColor>(), names[i].value<QString>());
        auto abbeyTile = getPlayer(i)->createAbbeyTile();
        connect(abbeyTile.get(), &Tile::objectCompleted, this, &QmlPresenter::onObjectCompleted);
        connect(abbeyTile.get(), &Tile::isFixedChanged, this, [abbeyTile, this]() {
            if (abbeyTile->fixed())
                onTileFixed(abbeyTile.get());
        });
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
    auto [wheat, barrels, cloth] = ObjectManager::instance()->getTownResources(townId);

    if (barrels > 0)
    {
        addResourceToActivePlayer(barrels, QmlEnums::BonusType::Barrel);
        unassignedBarrels -= barrels;
        emit unassignedBarrelsChanged();
    }

    if (wheat > 0)
    {
        addResourceToActivePlayer(wheat, QmlEnums::BonusType::Wheat);
        unassignedWheat -= wheat;
        emit unassignedWheatChanged();
    }

    if (cloth > 0)
    {
        addResourceToActivePlayer(cloth, QmlEnums::BonusType::Cloth);
        unassignedCloth -= cloth;
        emit unassignedClothChanged();
    }
}

void QmlPresenter::scoreLargestTown(unsigned townId)
{
    int townSize = ObjectManager::instance()->countObjectTiles(townId);
    int currentActivePlayer = activePlayer();
    Player* activePlayer = getPlayer(currentActivePlayer);

    if (townSize > activePlayer->getBiggestTown())
    {
        activePlayer->setBiggestTown(townSize);
    }

    if (townSize > maxTown)
    {
        maxTown = townSize;

        for (int i = 0; i < players.rowCount(); ++i)
        {
            Player* player = getPlayer(i);
            player->setTownLead(i == currentActivePlayer);

            if (player->getTownLead())
            {
                Logger::instance()->logEffect(std::make_shared<TownLeadLogRecord>(player->getColor(), player->getName(), maxTown));
            }
        }
    }
}

void QmlPresenter::scoreLongestRoad(unsigned roadId)
{
    int roadSize = ObjectManager::instance()->countObjectTiles(roadId);
    int currentActivePlayer = activePlayer();
    Player* activePlayer = getPlayer(currentActivePlayer);

    if (roadSize > activePlayer->getBiggestRoad())
    {
        activePlayer->setBiggestRoad(roadSize);
    }

    if (roadSize > maxRoad)
    {
        maxRoad = roadSize;

        for (int i = 0; i < players.rowCount(); ++i)
        {
            Player* player = getPlayer(i);
            player->setRoadLead(i == currentActivePlayer);

            if (player->getRoadLead())
            {
                Logger::instance()->logEffect(std::make_shared<RoadLeadLogRecord>(player->getColor(), player->getName(), maxRoad));
            }
        }
    }
}

void QmlPresenter::scoreCompletedObject(unsigned objectId)
{
    auto objectManager = ObjectManager::instance();
    if (auto object = objectManager->GetAggregateObject(objectId); object)
    {
        int points = objectManager->getPoints(objectId);
        std::vector<int> mostPresentPlayers = object->mostPresentPlayers();

        for (auto playerIndex: mostPresentPlayers)
        {
            getPlayer(playerIndex)->scorePoints(points);
            emit pointsScored(points, getPlayer(playerIndex)->getColor(), object->tile);
        }

        removeMeepleFromObject(object, { QmlEnums::MeepleSmall, QmlEnums::MeepleBig, QmlEnums::MeepleBuilder });
    }
}

void QmlPresenter::scoreFieldMeeples(unsigned objectId, int meepleScore)
{
    auto objectManager = ObjectManager::instance();
    if (auto object = objectManager->GetAggregateObject(objectId); object && object->type == ObjectType::Field)
    {
        std::vector<int> mostPresentPlayers = object->mostPresentPlayers();
        if (!mostPresentPlayers.empty())
        {
            std::set<int> pigs = object->pigs();
            int fieldTowns = objectManager->countTownsAround(object->initialId);

            removeMeepleFromObject(object, { QmlEnums::MeepleSmall, QmlEnums::MeepleBig, QmlEnums::MeeplePig });

            for (auto playerIndex: mostPresentPlayers)
            {
                bool pig = pigs.find(playerIndex) != pigs.end();
                int points = fieldTowns * (pig ? (meepleScore + 1) : meepleScore);
                getPlayer(playerIndex)->scorePoints(points);
                emit pointsScored(points, getPlayer(playerIndex)->getColor(), object->tile);
            }
        }
    }
}

void QmlPresenter::checkFieldIntegrity(unsigned fieldObjectId)
{
    for (auto& barnFieldInitialId: barnFieldInitialIds)
    {
        if (fieldObjectId == ObjectManager::instance()->GetAggregateObject(barnFieldInitialId.first)->initialId)
        {
            scoreFieldMeeples(fieldObjectId, 1);
        }
    }
}

void QmlPresenter::scoreBarnes(unsigned fieldObjectId)
{
    std::vector<unsigned> idsToDelete;
    for (auto& barnFieldInitialId: barnFieldInitialIds)
    {
        auto barnField = ObjectManager::instance()->GetAggregateObject(barnFieldInitialId.first);
        if (fieldObjectId == barnField->initialId)
        {
            for (auto& playerIndex: barnFieldInitialId.second)
            {
                getPlayer(playerIndex)->scorePoints(4 * ObjectManager::instance()->countTownsAround(fieldObjectId));
            }

            removeMeepleFromObject(barnField, { QmlEnums::MeepleBarn });
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
    int x = tile->getX();
    int y = tile->getY();

    Tile* north = mapModel.nextTileNorth(x, y);
    Tile* west = mapModel.nextTileWest(x, y);
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

QVariantList QmlPresenter::getScorableFields() const
{
    return QVariantList(scorableFields.begin(), scorableFields.end());
}

void QmlPresenter::addMeepleToObject(std::shared_ptr<TileObject> &object, QmlEnums::MeepleType meepleType, int playerIndex,
                                     qreal tileXRatio, qreal tileYRatio)
{
    object->setMeeple(playerIndex, meepleType, tileXRatio, tileYRatio);
    if (object->type == ObjectType::Field)
    {
        if (scorableFields.insert(object->currentObject()->initialId).second)
            emit scorableFieldsChanged();
    }
}

void QmlPresenter::removeMeepleFromObject(std::shared_ptr<TileObject> &object, const std::set<QmlEnums::MeepleType> &typesToRemove)
{
    auto removedMeeples = object->freeMeeples(typesToRemove);
    if (object->type == ObjectType::Field && object->mostPresentPlayers().empty())
    {
        if (scorableFields.erase(object->currentObject()->initialId) > 0)
            emit scorableFieldsChanged();
    }

    if (gameState != GameState::GameEnd && !removedMeeples.empty())
    {
        Player* player = getPlayer(activePlayer());
        Logger::instance()->logEffect(std::make_shared<FieldMeepleReleaseLogRecord>(player->getColor(), player->getName(),
                                                                                    std::vector<MeepleInfo>(removedMeeples.begin(), removedMeeples.end())));
    }
}

QAbstractListModel *QmlPresenter::getTurnLogRecords()
{
    return Logger::instance();
}

void QmlPresenter::updateScorableFieldIds()
{
    std::vector<unsigned> currentIds;
    for (auto fieldId: scorableFields)
    {
        currentIds.push_back(ObjectManager::instance()->GetAggregateObject(fieldId)->initialId);
    }
    scorableFields.insert(currentIds.begin(), currentIds.end());
    emit scorableFieldsChanged();
}

void QmlPresenter::onObjectCompleted(unsigned int objectId)
{
    // first, logging the completion action
    logObjectCompletion(objectId);

    // then processing the effects from completion
    scoreCompletedObject(objectId);
    scoreCompletionBonuses(objectId);
}

void QmlPresenter::logObjectCompletion(unsigned int objectId)
{
    Player* player = getPlayer(activePlayer());
    auto objectManager = ObjectManager::instance();
    Logger::instance()->logAction(std::make_shared<CompletionLogRecord>(player->getColor(), player->getName(),
                                                                        objectManager->GetAggregateObject(objectId)->type,
                                                                        objectManager->countObjectTiles(objectId),
                                                                        objectManager->GetAggregateObject(objectId)->initialId));
}

void QmlPresenter::onTileFixed(Tile* tile)
{
    Player* player = getPlayer(activePlayer());
    if (player)
    {
        for (int i = 0; i < shuffledDeck.rowCount(); ++i)
        {
            if (tile == shuffledDeck.data(shuffledDeck.index(i, 0), DataRoles::TilePtr).value<Tile*>())
            {
                Logger::instance()->logAction(std::make_shared<TilePlaceLogRecord>(player->getColor(), player->getName(), tile, i));
                return;
            }
        }

        qCritical() << "Cannot find fixed tile in the deck to log!";
    }
}

bool QmlPresenter::processGameEnd(int fixedTilesCount)
{
    QStringList messages;

    if (!allFttingTilesPlayed && shuffledDeck.rowCount() > fixedTilesCount)
    {
        Tile* nextTile = shuffledDeck.index(fixedTilesCount, 0).data(DataRoles::TilePtr).value<Tile*>();
        if (mapModel.fitsCurrentBoard(nextTile))
        {
            return false;
        }

        for (int swapCandidate = fixedTilesCount + 1; swapCandidate < shuffledDeck.rowCount(); swapCandidate++)
        {
            nextTile = shuffledDeck.index(swapCandidate, 0).data(DataRoles::TilePtr).value<Tile*>();
            if (mapModel.fitsCurrentBoard(nextTile))
            {
                // make tile at index "swapCandidate" go to index "fixedTilesCount"
                shuffledDeck.forceReorder(swapCandidate, fixedTilesCount);
                return false;
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
                if (!abbeyStage)
                {
                    emit showMessage(messages.join('\n'), GameState::NewTurn);
                    abbeyStage = true;
                }
                return false;
            }
    }

    // game end
    messages.append("Переход к подсчету очков.");
    emit showMessage(messages.join('\n'), GameState::GameEnd);

    getPlayer(activePlayer())->setActive(false);
    updateScorableFieldIds();
    return true;
}

QJsonObject QmlPresenter::serializeGameState()
{
    QJsonObject json;

    json["unassignedWheat"] = unassignedWheat;
    json["unassignedBarrels"] = unassignedBarrels;
    json["unassignedCloth"] = unassignedCloth;

    json["gameState"] = static_cast<int>(gameState);

    json["objectManager"] = ObjectManager::instance()->serialize();
    json["deck"] = shuffledDeck.serialize();
    json["map"] = mapModel.serialize();
    json["players"] = players.serialize();
    json["log"] = Logger::instance()->serialize();

    return json;
}

void QmlPresenter::deserializeGameState(const QJsonObject &json)
{
    for (const auto& module: { "unassignedWheat", "unassignedBarrels", "unassignedCloth",
                               "gameState", "objectManager", "players", "deck", "map" })
    {
        if (!json.contains(module))
        {
            qCritical() << "Could not load module" << module << "from the save file.";
            return;
        }
    }

    unassignedWheat = json["unassignedWheat"].toInt(-1);
    emit unassignedWheatChanged();
    unassignedBarrels = json["unassignedBarrels"].toInt(-1);
    emit unassignedBarrelsChanged();
    unassignedCloth = json["unassignedCloth"].toInt(-1);
    emit unassignedClothChanged();

    gameState = static_cast<GameState>(json["gameState"].toInt());

    auto objectManager = ObjectManager::instance();
    objectManager->reset(json["objectManager"].toArray());

    std::vector<Tile*> abbeyTiles;
    deserializePlayers(json["players"].toArray(), abbeyTiles);

    std::vector<std::shared_ptr<Tile>> tiles;
    tiles = deserializeTiles(json["deck"].toArray());
    setDeck(tiles);

    mapModel.deserialize(json["map"].toObject(), tiles, abbeyTiles);

    Logger::instance()->deserialize(json["log"].toArray(), tiles);
}

void QmlPresenter::connectTiles(const std::vector<std::shared_ptr<Tile> > &tiles)
{
    for (const auto& tile: tiles)
    {
        connect(tile.get(), &Tile::objectCompleted, this, &QmlPresenter::onObjectCompleted);
        connect(tile.get(), &Tile::isFixedChanged, this, [tile, this]() {
            if (tile->fixed())
                onTileFixed(tile.get());
        });
    }
}

void QmlPresenter::calculateUnassignedResources(const std::vector<std::shared_ptr<Tile> > &tiles)
{
    for (const auto& tile: tiles)
    {
        auto [wheat, barrels, cloth] = tile->resources();
        unassignedWheat += wheat;
        unassignedBarrels += barrels;
        unassignedCloth += cloth;
    }
}

void QmlPresenter::fixTile(Tile *tile)
{
    std::shared_ptr<const TileObject> builderObject(nullptr);
    if (bonusTurn != Logger::instance()->currentTurn() && (builderObject = mapModel.builderObjectProgression(tile, activePlayer())))
    {
        bonusTurn = Logger::instance()->currentTurn() + 1;
    }

    mapModel.fixTile(tile);

    if (bonusTurn == Logger::instance()->currentTurn() + 1)
    {
        Player* player = getPlayer(activePlayer());
        Logger::instance()->logAction(std::make_shared<FreeTurnLogRecord>(
            player->getColor(), player->getName(), builderObject->type, builderObject->initialId));
        Logger::instance()->logEffect(std::make_shared<FreeTurnLogRecord>(
            player->getColor(), player->getName(), builderObject->type, builderObject->initialId));
    }
}

void QmlPresenter::saveGame()
{
    QFile saveFile("save.json");

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file for writing.");
        return;
    }

    saveFile.write(QJsonDocument(serializeGameState()).toJson());
}

void QmlPresenter::loadGame()
{
    QFile loadFile("save.json");

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file for reading.");
        return;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    deserializeGameState(loadDoc.object());

    emit gameObjectsLoaded();
}

QList<MeepleInfo> QmlPresenter::activeMeeples()
{
    return ObjectManager::instance()->getObjectMeeples();
}

void QmlPresenter::passTurn(int fixedTilesCount)
{
    gameState = GameState::NewTurn;
    emit gameStateChanged();

    if (!processGameEnd(fixedTilesCount))
    {
        if (Logger::instance()->currentTurn() + 1 != bonusTurn)
        {
            setActivePlayer((activePlayer() + 1) % players.rowCount());
        }

        Player* player = getPlayer(activePlayer());
        Logger::instance()->logNewTurn(std::make_shared<NewTurnLogRecord>(player->getColor(), player->getName(), Logger::incrementTurn()));
    }
    else
    {
//        Logger::instance()->log(std::make_shared<GameEndLogRecord>());
    }
}

void QmlPresenter::placeMeeple(int meepleType, int playerIndex, unsigned objectId, qreal tileXRatio, qreal tileYRatio)
{
    if (auto object = ObjectManager::instance()->GetObject(objectId),
        aggregateObject = ObjectManager::instance()->GetAggregateObject(objectId);
        aggregateObject && object)
    {
        addMeepleToObject(object, (QmlEnums::MeepleType)meepleType, playerIndex, tileXRatio, tileYRatio);

        Player* player = getPlayer(activePlayer());
        Logger::instance()->logAction(std::make_shared<MeeplePlaceLogRecord>(player->getColor(), player->getName(), aggregateObject->type,
                                                                             (QmlEnums::MeepleType)meepleType, aggregateObject->initialId));

        if (aggregateObject->isCompleted())
        {
            scoreCompletedObject(aggregateObject->initialId);
        }

        if ((QmlEnums::MeepleType)meepleType == QmlEnums::MeepleType::MeepleBarn)
        {
            scoreFieldMeeples(aggregateObject->initialId, 3);
            barnFieldInitialIds[aggregateObject->initialId].push_back(playerIndex);
        }
    }
}

void QmlPresenter::scoreField(unsigned fieldCurrentId)
{
    if (auto object = ObjectManager::instance()->GetAggregateObject(fieldCurrentId); object && object->type == ObjectType::Field)
    {
        scoreFieldMeeples(object->initialId, 3);
        scoreBarnes(object->initialId);
    }
}

bool QmlPresenter::canPlaceMeeple(unsigned objectId, int playerIndex, int type, Tile* tile) const
{
    if (auto object = ObjectManager::instance()->GetAggregateObject(objectId); object)
    {
        switch ((QmlEnums::MeepleType)type)
        {
        case QmlEnums::MeepleSmall:
        case QmlEnums::MeepleBig:
            return !object->taken() && object->mostPresentPlayers().empty();
        case QmlEnums::MeepleBarn:
            return object->type == ObjectType::Field
                   && !object->meeplePresent({ QmlEnums::MeepleType::MeepleBarn })
                    && isFieldCorner(tile, objectId);
        case QmlEnums::MeeplePig:
            return object->type == ObjectType::Field
                    && object->meeplePresent({ QmlEnums::MeepleType::MeepleSmall, QmlEnums::MeepleType::MeepleBig }, playerIndex);
        case QmlEnums::MeepleBuilder:
            return (object->type == ObjectType::Town || object->type == ObjectType::Road)
                    && object->meeplePresent({ QmlEnums::MeepleType::MeepleSmall, QmlEnums::MeepleType::MeepleBig }, playerIndex);
        default:
            std::cerr << "placing unknown meeple type " << type << std::endl;
        }
    }

    return false;
}

bool QmlPresenter::isFieldObject(unsigned objectId) const
{
    return ObjectManager::instance()->GetAggregateObject(objectId)->type == ObjectType::Field;
}

void QmlPresenter::setWaitingCursor(bool value)
{
    if (value)
        QGuiApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    else
        QGuiApplication::restoreOverrideCursor();
}
