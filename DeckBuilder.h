#ifndef DECKBUILDER_H
#define DECKBUILDER_H

#include "Tile.h"

#include <vector>

class DeckBuilder
{
public:
    DeckBuilder();
    static void BuildStandardDeck(ObjectManager& objectManager, std::list<Tile> &tiles);
    static void BuildExampleDeck(ObjectManager& objectManager, std::list<Tile> &tiles);
};

#endif // DECKBUILDER_H
