#include "TilesModel.h"
#include "DataRoles.h"

TilesModel::TilesModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int TilesModel::rowCount(const QModelIndex &parent) const
{
    return tilesList.size();
}

QVariant TilesModel::data(const QModelIndex &index, int role) const
{
    if (role == DataRoles::TilePtr)
        return QVariant::fromValue(tilesList.at(index.row()));

    if (role == DataRoles::TileImagePath)
        return QVariant::fromValue(tilesList.at(index.row())->property("Picture").toString());

    return QVariant();
}

QHash<int, QByteArray> TilesModel::roleNames() const
{
    return {{257, "TilePtr"}};
}

void TilesModel::AddTiles(std::list<Tile> &tiles)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount() + tiles.size() - 1);
    int i = tilesList.size();
    for (Tile& tile: tiles)
    {
        tilesList.append(&tile);
        connect(&tile, &Tile::isFixedChanged, this, [this, i](){
            emit dataChanged(index(i, 0), index(i, 0), { DataRoles::IsTileFixed });
        });
        ++i;
    }
    endInsertRows();
}
