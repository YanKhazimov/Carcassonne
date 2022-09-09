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

    return QVariant();
}

QHash<int, QByteArray> TilesModel::roleNames() const
{
    return {{257, "TilePtr"}};
}

void TilesModel::AddTile(Tile *tile)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    tilesList.append(tile);
    endInsertRows();
}
