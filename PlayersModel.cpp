#include "PlayersModel.h"
#include "DataRoles.h"
#include <QColor>

void PlayersModel::connectPlayerSignals()
{
    for (int i = 0; i < players.size(); ++i)
    {
        connect(players[i].get(), &Player::nameChanged, this, [this, i](){
            emit dataChanged(index(i, 0), index(i, 0), {DataRoles::PlayerName});
        });
        connect(players[i].get(), &Player::scoreChanged, this, [this, i](){
            // emitting this role so that dependent sort model does the sorting
            emit dataChanged(index(i, 0), index(i, 0), {DataRoles::PlayerScore});
        });
        connect(players[i].get(), &Player::placeChanged, this, [this, i](){
            emit dataChanged(index(i, 0), index(i, 0), {DataRoles::PlayerPlace});
        });
        connect(players[i].get(), &Player::wheatLeadChanged, this, [this, i](){
            emit dataChanged(index(i, 0), index(i, 0), {DataRoles::WheatLead});
        });
        connect(players[i].get(), &Player::barrelsLeadChanged, this, [this, i](){
            emit dataChanged(index(i, 0), index(i, 0), {DataRoles::BarrelsLead});
        });
        connect(players[i].get(), &Player::clothLeadChanged, this, [this, i](){
            emit dataChanged(index(i, 0), index(i, 0), {DataRoles::ClothLead});
        });
        connect(players[i].get(), &Player::townLeadChanged, this, [this, i](){
            emit dataChanged(index(i, 0), index(i, 0), {DataRoles::TownLead});
        });
        connect(players[i].get(), &Player::roadLeadChanged, this, [this, i](){
            emit dataChanged(index(i, 0), index(i, 0), {DataRoles::RoadLead});
        });
        connect(players[i].get(), &Player::biggestTownChanged, this, [this, i](){
            emit dataChanged(index(i, 0), index(i, 0), {DataRoles::BiggestTown});
        });
        connect(players[i].get(), &Player::biggestRoadChanged, this, [this, i](){
            emit dataChanged(index(i, 0), index(i, 0), {DataRoles::BiggestRoad});
        });
        connect(players[i].get(), &Player::currentTurnSecondsChanged, this, [this, i](){
            emit dataChanged(index(i, 0), index(i, 0), {DataRoles::CurrentTurnSeconds});
        });
        connect(players[i].get(), &Player::prevTurnsSecondsChanged, this, [this, i](){
            emit dataChanged(index(i, 0), index(i, 0), {DataRoles::PastTurnsSeconds});
        });
    }
}

PlayersModel::PlayersModel()
{
}

int PlayersModel::rowCount(const QModelIndex &parent) const
{
    return players.size();
}

QVariant PlayersModel::data(const QModelIndex &index, int role) const
{
    if (role == DataRoles::PlayerPtr)
        return QVariant::fromValue(players.at(index.row()).get());

    if (role == DataRoles::PlayerName)
        return players.at(index.row())->getName();

    if (role == DataRoles::PlayerScore)
        return players.at(index.row())->getScore();

    if (role == DataRoles::PlayerPlace)
        return players.at(index.row())->getPlace();

    if (role == DataRoles::PlayerColor)
        return players.at(index.row())->getColor();

    if (role == DataRoles::WheatLead)
        return players.at(index.row())->getWheatLead();

    if (role == DataRoles::BarrelsLead)
        return players.at(index.row())->getBarrelsLead();

    if (role == DataRoles::ClothLead)
        return players.at(index.row())->getClothLead();

    if (role == DataRoles::TownLead)
        return players.at(index.row())->getTownLead();

    if (role == DataRoles::RoadLead)
        return players.at(index.row())->getRoadLead();

    if (role == DataRoles::BiggestTown)
        return players.at(index.row())->getBiggestTown();

    if (role == DataRoles::BiggestRoad)
        return players.at(index.row())->getBiggestRoad();

    if (role == DataRoles::CurrentTurnSeconds)
        return players.at(index.row())->getCurrentTurnSeconds();

    if (role == DataRoles::PastTurnsSeconds)
        return players.at(index.row())->getPrevTurnsSeconds();

    return QVariant();
}

QColor PlayersModel::getPlayerColor(int _index) const
{
    return players.at(_index)->getColor();
}

void PlayersModel::resetPlayers(QVariantList colors, QVariantList names)
{
    Q_ASSERT(colors.length() == names.length());

    beginResetModel();

    players.resize(colors.length());
    for (int i = 0; i < players.size(); ++i)
    {
        players[i] = std::make_shared<Player>(colors[i].value<QColor>(), names[i].value<QString>());
    }
    connectPlayerSignals();

    endResetModel();
}

void PlayersModel::resetPlayers(const QJsonArray &json)
{
    beginResetModel();

    players.resize(json.count());
    for (int i = 0; i < players.size(); ++i)
    {
        players[i] = std::make_shared<Player>(json[i].toObject());
    }
    connectPlayerSignals();

    endResetModel();
}

void PlayersModel::deserialize(const QJsonArray &json)
{
    std::vector<std::shared_ptr<Player>> players;

    for (const auto& player: json)
    {
        players.emplace_back(new Player(player.toObject()));
    }
}

QJsonArray PlayersModel::serialize() const
{
    QJsonArray result;

    for (const auto& player: players)
    {
        result.push_back(player->serialilze());
    }

    return result;
}

QHash<int, QByteArray> PlayersModel::roleNames() const
{
    return {
        { DataRoles::PlayerScore, "SCORE" },
        { DataRoles::PlayerName, "NAME" },
        { DataRoles::PlayerPlace, "PLACE" },
        { DataRoles::PlayerColor, "COLOR" },
        { DataRoles::WheatLead, "WHEAT_LEAD" },
        { DataRoles::BarrelsLead, "BARRELS_LEAD" },
        { DataRoles::ClothLead, "CLOTH_LEAD" },
        { DataRoles::TownLead, "TOWN_LEAD" },
        { DataRoles::RoadLead, "ROAD_LEAD" },
        { DataRoles::BiggestTown, "BIGGEST_TOWN" },
        { DataRoles::BiggestRoad, "BIGGEST_ROAD" },
        { DataRoles::CurrentTurnSeconds, "CURRENT_TURN_TIME" },
        { DataRoles::PastTurnsSeconds, "PAST_TURNS_TIME" }
    };
}
