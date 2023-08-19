#ifndef SCOREBOARDMODEL_H
#define SCOREBOARDMODEL_H

#include <QSortFilterProxyModel>
#include "PlayersModel.h"

class ScoreboardModel: public QSortFilterProxyModel
{
    Q_OBJECT

private slots:
    void onDataChanged(QModelIndex first, QModelIndex last, QVector<int> roles);

protected:
    bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const override;

public:
    explicit ScoreboardModel(QObject *parent = nullptr);
    void setSource(PlayersModel* source);
};

#endif // SCOREBOARDMODEL_H
