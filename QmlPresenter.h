#ifndef QMLPRESENTER_H
#define QMLPRESENTER_H

#include <QObject>
#include "Tile.h"
#include "TilesModel.h"
#include "mapmodel.h"

class QmlPresenter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(TilesModel* deck READ getTiles NOTIFY tilesChanged)
    Q_PROPERTY(unsigned HighlightedObjectId READ highlightedObjectId WRITE setHighlightedObjectId NOTIFY highlightedObjectIdChanged)
    Q_PROPERTY(MapModel* mapModel READ getMapModel NOTIFY mapModelChanged)

    TilesModel deck;
    TilesModel* getTiles();

    MapModel mapModel;
    MapModel* getMapModel();

    ObjectManager& objectManager;
    unsigned highlightedObjId = -1;

    void setHighlightedObjectId(unsigned id);
    unsigned highlightedObjectId() const;

public:
    explicit QmlPresenter(ObjectManager& objManager, QObject *parent = nullptr);

    void AddTiles(std::list<Tile> &tiles);
    Q_INVOKABLE Tile* getTile(int i);
    Q_INVOKABLE void highlight(int id);
    Q_INVOKABLE void updateHighlight();

signals:
    void tilesChanged();
    void highlightedObjectIdChanged();
    void mapModelChanged();
};

#endif // QMLPRESENTER_H
