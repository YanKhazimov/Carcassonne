#ifndef SHUFFLEDDECK_H
#define SHUFFLEDDECK_H

#include <QSortFilterProxyModel>

class ShuffledDeck : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit ShuffledDeck(QObject *parent = nullptr);
    void setSource(QAbstractItemModel* source);
    void forceReorder(int source, int destination);
    QModelIndex mapToSource(const QModelIndex& index) const override;

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;

private slots:
    void shuffle();

private:
    std::vector<int> sourceIndexes;
};

#endif // SHUFFLEDDECK_H
