#include "PlayersModel.h"
#include "DataRoles.h"
#include <QColor>
#include <QDebug>

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

    return QVariant();
}

void PlayersModel::AddPlayer(QColor color, QString name)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    int i = players.size();
    players.push_back(std::make_shared<Player>(color, name));

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

    endInsertRows();
}

void ScoreboardModel::onDataChanged(QModelIndex first, QModelIndex last, QVector<int> roles)
{
    if (roles.contains(DataRoles::PlayerScore))
    {
        for (int i = 0; i < rowCount(); ++i)
        {
            QModelIndex sourceIndex = mapToSource(index(i, 0));
            Player* player = sourceIndex.data(DataRoles::PlayerPtr).value<Player*>();
            player->setPlace(rowCount() - i);
        }
    }
}

ScoreboardModel::ScoreboardModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setSortRole(DataRoles::PlayerScore);
}

void ScoreboardModel::setSource(PlayersModel *source)
{
    if (!sourceModel())
    {
        setSourceModel(source);
        connect(source, &PlayersModel::dataChanged, this, &ScoreboardModel::onDataChanged);
        sort(0);
    }
    else
    {
        qWarning() << "ScoreboardModel already has a source";
    }
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
        { DataRoles::RoadLead, "ROAD_LEAD" }
    };
}
