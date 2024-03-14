#ifndef SHUFFLEDDECK_H
#define SHUFFLEDDECK_H

#include <QSortFilterProxyModel>
#include <QJsonArray>

class ShuffledDeck : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit ShuffledDeck(QObject *parent = nullptr);
    void setSource(QAbstractItemModel* source);
    void forceReorder(int source, int destination);
    QModelIndex mapToSource(const QModelIndex& index) const override;
    QJsonArray serialize() const;
    void shuffle();
    void setRandom(bool value);

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;

private:
    std::vector<int> sourceIndexes;
    bool random = true;
};

#endif // SHUFFLEDDECK_H
