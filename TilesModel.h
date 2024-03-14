#ifndef TILESMODEL_H
#define TILESMODEL_H

#include "Tile.h"
#include <QAbstractListModel>

class TilesModel : public QAbstractListModel
{
    Q_OBJECT

    QList<std::shared_ptr<Tile>> tilesList;

public:
    TilesModel(QObject* parent = 0);
    Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int,QByteArray> roleNames() const override;

    void setTiles(const std::vector<std::shared_ptr<Tile> > &tiles);
    void clear();
};

#endif // TILESMODEL_H
