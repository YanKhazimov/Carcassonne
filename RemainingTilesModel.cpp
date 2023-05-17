#include "RemainingTilesModel.h"
#include "DataRoles.h"
#include "Tile.h"
#include <QFileInfo>
#include <QDebug>

RemainingTilesModel::RemainingTilesModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

void RemainingTilesModel::setSource(QAbstractItemModel *source)
{
    if (!sourceModel())
    {
        setSourceModel(source);
        connect(source, &QAbstractItemModel::dataChanged, this, &RemainingTilesModel::onDataChanged);
        connect(source, &QAbstractItemModel::rowsInserted, this, &RemainingTilesModel::onRowsInserted);
        sort(0);
    }
    else
    {
        qWarning() << "RemainingTilesModel already has a source";
    }
}

QVariant RemainingTilesModel::data(const QModelIndex &index, int role) const
{
    if (role == DataRoles::TileCopies)
    {
        Tile* tile = index.data(DataRoles::TilePtr).value<Tile*>();
        const QString& picture = index.data(DataRoles::TileImagePath).value<QString>();
        if (tile->fixed())
        {
            return fixedTiles[picture].size();
        }
        else
        {
            return unfixedTiles[picture].size();
        }
    }

    return QSortFilterProxyModel::data(index, role);
}

int RemainingTilesModel::getTileCopies(int row) const
{
    return index(row, 0).data(DataRoles::TileCopies).toInt();
}

void RemainingTilesModel::onDataChanged(QModelIndex first, QModelIndex last, QVector<int> roles)
{
    if (roles.contains(DataRoles::IsTileFixed))
    {
        // tile is fixed -> move it to the other map and resort
        for (int i = first.row(); i <= last.row(); ++i)
        {
            const QModelIndex sourceIndex = sourceModel()->index(i, 0);
            Tile* tile = sourceIndex.data(DataRoles::TilePtr).value<Tile*>();
            Q_ASSERT(tile->fixed());
            const QString& picture = sourceIndex.data(DataRoles::TileImagePath).value<QString>();
            auto tileIter = std::find(unfixedTiles[picture].begin(), unfixedTiles[picture].end(), tile);
            unfixedTiles[picture].erase(tileIter);
            fixedTiles[picture].push_back(tile);
            if (unfixedTiles[picture].empty())
                unfixedTiles.remove(picture);
        }

        invalidate();
    }
}

void RemainingTilesModel::onRowsInserted(const QModelIndex &source_parent, int first, int last)
{
    for (int i = first; i <= last; ++i)
    {
        const QModelIndex sourceIndex = sourceModel()->index(i, 0, source_parent);
        Tile* tile = sourceIndex.data(DataRoles::TilePtr).value<Tile*>();
        // initially all tiles are not fixed
        unfixedTiles[sourceIndex.data(DataRoles::TileImagePath).value<QString>()].push_back(tile);
    }
}

bool RemainingTilesModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    Tile* left = source_left.data(DataRoles::TilePtr).value<Tile*>();
    Tile* right = source_right.data(DataRoles::TilePtr).value<Tile*>();
    QString leftPath = source_left.data(DataRoles::TileImagePath).value<QString>();
    QString rightPath = source_right.data(DataRoles::TileImagePath).value<QString>();
    QString leftBasename = QFileInfo(QUrl(leftPath).fileName()).baseName();
    QString rightBasename = QFileInfo(QUrl(rightPath).fileName()).baseName();

    if (left->fixed() != right->fixed())
        return left->fixed() < right->fixed();
    return leftBasename.toInt() < rightBasename.toInt();
}

bool RemainingTilesModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
    Tile* tile = sourceIndex.data(DataRoles::TilePtr).value<Tile*>();

    const QString& picture = sourceIndex.data(DataRoles::TileImagePath).value<QString>();
    return fixedTiles.contains(picture) && fixedTiles.value(picture).at(0) == tile ||
            unfixedTiles.contains(picture) && unfixedTiles.value(picture).at(0) == tile;
}
