#include "Tile.h"
#include <QPoint>

Tile::Tile(const std::vector<TileObject> &objects, QObject *parent)
    : QObject(parent), TileData(objects), x(-100), y(-100), isFixed(false), isPlaced(false)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    QObject::connect(this, &Tile::layoutChanged, this, &Tile::objectIdsChanged);
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
