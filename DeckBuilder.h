#ifndef DECKBUILDER_H
#define DECKBUILDER_H

#include "Tile.h"

#include <memory>

class DeckBuilder
{
public:
    static std::list<Tile> BuildDeck(const QString& imagesFolder, const QString& imageFormat);
    static std::shared_ptr<Tile> createAbbeyTile(const QString& imagesFolder, const QString& imageFormat);
};

#endif // DECKBUILDER_H
