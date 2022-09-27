#ifndef PLAYERSMODEL_H
#define PLAYERSMODEL_H

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include "Player.h"
#include <memory>

class PlayersModel: public QAbstractListModel
{
    Q_OBJECT

    std::vector<std::shared_ptr<Player>> players;

public:
    PlayersModel();
    Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void AddPlayer(QColor color, QString name);
};

class ScoreboardModel: public QSortFilterProxyModel
{
    Q_OBJECT

private slots:
    void onDataChanged(QModelIndex first, QModelIndex last, QVector<int> roles);

public:
    explicit ScoreboardModel(QObject *parent = nullptr);
    void setSource(PlayersModel* source);
};

#endif // PLAYERSMODEL_H
