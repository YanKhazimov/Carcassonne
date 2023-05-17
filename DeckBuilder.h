#ifndef DECKBUILDER_H
#define DECKBUILDER_H

#include "Tile.h"

#include <vector>
#include <memory>

class DeckBuilder
{
public:
    DeckBuilder();
    static std::list<Tile> BuildDeck(ObjectManager& objectManager, const QString& imagesFolder, const QString& imageFormat);
    static std::shared_ptr<Tile> createAbbeyTile(ObjectManager& objectManager, const QString& imagesFolder, const QString& imageFormat);
};

#endif // DECKBUILDER_H
