#include "ShuffledDeck.h"
#include <QDebug>

int myrandom(int i) { return std::rand()%i; }

ShuffledDeck::ShuffledDeck(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    std::srand ( unsigned ( std::time(0) ) );
}

void ShuffledDeck::setSource(QAbstractItemModel *source)
{
    if (!sourceModel())
    {
        setSourceModel(source);
        connect(source, &QAbstractItemModel::rowsInserted, this, &ShuffledDeck::shuffle);
        sort(0); // initiates custom sorting
        shuffle();
    }
    else
    {
        qWarning() << "ShuffledDeck already has a source";
    }
}

void ShuffledDeck::forceReorder(int source, int destination)
{
    // swapping
    std::swap(sourceIndexes[source], sourceIndexes[destination]);
    invalidate();
}

QModelIndex ShuffledDeck::mapToSource(const QModelIndex &index) const
{
    if (sourceModel())
    {
        if (sourceIndexes.size() == sourceModel()->rowCount())
            return sourceModel()->index(sourceIndexes[index.row()], index.column(), index.parent());
        else
            return sourceModel()->index(index.row(), index.column(), index.parent());
    }

    return QModelIndex();
}

bool ShuffledDeck::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    if (sourceIndexes.empty())
        return true;

    return sourceIndexes[source_left.row()] < sourceIndexes[source_right.row()];
}

void ShuffledDeck::shuffle()
{
    sourceIndexes.resize(sourceModel()->rowCount());
    std::iota(sourceIndexes.begin(), sourceIndexes.end(), 0); // fill with values 0, 1, ...
    if (!sourceIndexes.empty())
    {
        //std::random_shuffle(sourceIndexes.begin() + 1, sourceIndexes.end(), myrandom); // leaving startng tile first
        invalidate();
    }
}
