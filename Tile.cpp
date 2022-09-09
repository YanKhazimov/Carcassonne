#include "Tile.h"
#include <QPoint>
#include <QQmlEngine>

Tile::Tile(std::vector<TileObject> &&objects, QObject *parent)
    : QObject(parent), TileData(std::move(objects)), x(-100), y(-100), isFixed(false), isPlaced(false)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    QObject::connect(this, &Tile::layoutChanged, this, &Tile::objectIdsChanged);

    updateBonuses();
    QObject::connect(this, &Tile::layoutChanged, this, &Tile::updateBonuses);

    for (auto& tileObject: tileObjects)
    {
        tileObject.objPtr->setTile(this);
    }
}

Tile::Tile(Tile &&other) noexcept
    : TileData(std::move(other)), x(other.x), y(other.y), isFixed(other.isFixed), isPlaced(other.isPlaced)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

void Tile::rotateClockwise()
{
    RotateClockwise();
    emit layoutChanged();
}

void Tile::rotateCounterclockwise()
{
    RotateCounterclockwise();
    emit layoutChanged();
}

void Tile::setPosition(int _x, int _y)
{
    x = _x;
    y = _y;
    emit indexChanged();
}

void Tile::checkCompletion(std::shared_ptr<MapObjectData> object)
{
    if (object->currentObject()->valency == 0)
    {
        emit objectCompleted(object->currentObject()->initialId);
    }
}

QPoint Tile::position() const
{
    return QPoint{x, y};
}

bool Tile::fixed() const
{
    return isFixed;
}

void Tile::setFixed(bool fixed)
{
    if (isFixed != fixed)
    {
        isFixed = fixed;
        emit isFixedChanged();
    }
}

bool Tile::placed() const
{
    return isPlaced;
}

void Tile::setPlaced(bool placed)
{
    if (isPlaced != placed)
    {
        isPlaced = placed;
        emit isPlacedChanged();
    }
}

void Tile::displace()
{
    setPlaced(false);
    setPosition(-100, -100);
}

void Tile::place(int _x, int _y)
{
    setPlaced(true);
    setPosition(_x, _y);
}

std::tuple<int, int, int> Tile::resources() const
{
    int wheat = 0, barrels = 0, cloth = 0;
    for (auto& tileObject: tileObjects)
    {
        switch (tileObject.objPtr->bonusType)
        {
        case BonusType::Wheat: wheat++; break;
        case BonusType::Barrel: barrels++; break;
        case BonusType::Cloth: cloth++; break;
        }
    }

    return { wheat, barrels, cloth };
}

void Tile::updateBonuses()
{
    bonusTypes = {
        checkConnector(Direction::North)->getBonusType(),
        checkConnector(Direction::East)->getBonusType(),
        checkConnector(Direction::South)->getBonusType(),
        checkConnector(Direction::West)->getBonusType()
    };
    emit tileBonusesChanged();
}
