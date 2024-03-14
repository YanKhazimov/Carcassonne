#ifndef DECKBUILDER_H
#define DECKBUILDER_H

#include "Tile.h"

#include <memory>

class DeckBuilder
{
public:
    static std::vector<std::shared_ptr<Tile>> BuildDeck(const QString& imagesFolder, const QString& imageFormat);
    static std::vector<std::shared_ptr<Tile>> BuildDeck(const QJsonArray &json);
    static std::shared_ptr<Tile> createAbbeyTile(const QString& imagesFolder, const QString& imageFormat);
    static std::shared_ptr<Tile> readAbbeyTile(const QJsonObject &json);
};

#endif // DECKBUILDER_H
