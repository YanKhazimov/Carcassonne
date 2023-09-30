#ifndef PLAYERSMODEL_H
#define PLAYERSMODEL_H

#include <QAbstractListModel>
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
    Q_INVOKABLE QColor getPlayerColor(int index) const;
};

#endif // PLAYERSMODEL_H
