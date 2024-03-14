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
        return QVariant::fromValue(tilesList.at(index.row()).get());

    if (role == DataRoles::TileImagePath)
        return QVariant::fromValue(tilesList.at(index.row())->property("Picture").toString());

    return QVariant();
}

QHash<int, QByteArray> TilesModel::roleNames() const
{
    return {{257, "TilePtr"}};
}

void TilesModel::setTiles(const std::vector<std::shared_ptr<Tile>>& tiles)
{
//    beginInsertRows(QModelIndex(), rowCount(), rowCount() + tiles.size() - 1);
    beginResetModel();

    tilesList.clear();

    int i = tilesList.size();
    for (const auto& tile: tiles)
    {
        tilesList.append(tile);
        connect(tile.get(), &Tile::isFixedChanged, this, [this, i](){
            emit dataChanged(index(i, 0), index(i, 0), { DataRoles::IsTileFixed });
        });
        ++i;
    }

    endResetModel();
//    endInsertRows();
}

void TilesModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    tilesList.clear();
    endRemoveRows();
}
