#ifndef REMAININGTILESMODEL_H
#define REMAININGTILESMODEL_H

#include <QSortFilterProxyModel>
#include "TilesModel.h"

class RemainingTilesModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit RemainingTilesModel(QObject *parent = nullptr);
    void setSource(TilesModel* source);
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE int getTileCopies(int row) const;

private slots:
    void onDataChanged(QModelIndex first, QModelIndex last, QVector<int> roles);
    void onRowsInserted(const QModelIndex &source_parent, int first, int last);

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QMap<QString, QList<Tile*>> fixedTiles, unfixedTiles;
};

#endif // REMAININGTILESMODEL_H
