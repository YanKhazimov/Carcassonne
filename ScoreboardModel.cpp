#include "ScoreboardModel.h"
#include "DataRoles.h"
#include <QDebug>

ScoreboardModel::ScoreboardModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
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

bool ScoreboardModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
{
    // by score then by initial order
    return sourceLeft.data(DataRoles::PlayerScore).toInt() < sourceRight.data(DataRoles::PlayerScore).toInt() ||
           sourceLeft.data(DataRoles::PlayerScore).toInt() == sourceRight.data(DataRoles::PlayerScore).toInt() &&
               sourceLeft.row() > sourceRight.row();
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
