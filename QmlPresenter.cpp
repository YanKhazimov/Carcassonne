#include "QmlPresenter.h"
#include "DataRoles.h"
#include "ObjectManager.h"
#include <iostream>

TilesModel *QmlPresenter::getTiles()
{
    return &deck;
}

MapModel *QmlPresenter::getMapModel()
{
    return &mapModel;
}

void QmlPresenter::setHighlightedObjectId(unsigned id)
{
    if (highlightedObjId != id)
    {
        std::cout << "highlightedObjectId " << highlightedObjId << " -> " << id << std::endl;
        highlightedObjId = id;
        emit highlightedObjectIdChanged();
    }
}

unsigned QmlPresenter::highlightedObjectId() const
{
    return highlightedObjId;
}

QmlPresenter::QmlPresenter(ObjectManager& objManager, QObject *parent)
    : QObject(parent), mapModel(13), objectManager(objManager)
{
}

void QmlPresenter::AddTiles(std::list<Tile> &tiles)
{
    for (Tile& tile: tiles)
    {
        deck.AddTile(&tile);
    }
}

Tile *QmlPresenter::getTile(int i)
{
    return deck.index(i, 0).data(DataRoles::TilePtr).value<Tile*>();
}

void QmlPresenter::highlight(int id)
{
    auto targetObject = objectManager.GetObject(id);
    setHighlightedObjectId(targetObject->initialId);
}

void QmlPresenter::updateHighlight()
{
    highlight(objectManager.GetObject(highlightedObjId)->initialId);
}
