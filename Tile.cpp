#include "Tile.h"
#include <QPoint>
#include <QQmlEngine>

Tile::Tile(const std::vector<std::pair<std::shared_ptr<MapObjectData>, TileData::ObjectLocation>>& objects, const QUrl &image, int imgRotation, QObject *parent)
    : QObject(parent), TileData(objects),
      imageUrl(image), imageRotation(imgRotation), x(-100), y(-100), isFixed(false), isPlaced(false)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    QObject::connect(this, &Tile::layoutChanged, this, &Tile::objectIdsChanged);

    updateBonuses();
    QObject::connect(this, &Tile::layoutChanged, this, &Tile::updateBonuses);

    for (auto& tileObject: tileObjects)
    {
        tileObject->setTile(this);
    }
}

Tile::Tile(Tile &&other) noexcept
    : TileData(std::move(other)), imageUrl(other.imageUrl), imageRotation(other.imageRotation), x(other.x), y(other.y), isFixed(other.isFixed), isPlaced(other.isPlaced)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

void Tile::rotateClockwise()
{
    RotateClockwise();
    emit layoutChanged();

    setImageRotation(imageRotation + 90);
}

void Tile::rotateCounterclockwise()
{
    RotateCounterclockwise();
    emit layoutChanged();

    setImageRotation(imageRotation + 270);
}

void Tile::setPosition(int _x, int _y)
{
    x = _x;
    y = _y;
    emit indexChanged();
}

void Tile::checkObjectCompletion(std::shared_ptr<MapObjectData> object)
{
    if (object->currentObject()->isCompleted())
    {
        emit objectCompleted(object->currentObject()->initialId);
    }
}

int Tile::getX() const
{
    return x;
}

int Tile::getY() const
{
    return y;
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

int Tile::getImageRotation() const
{
    return imageRotation;
}

void Tile::setImageRotation(int rotation)
{
    if (imageRotation != rotation)
    {
        imageRotation = rotation;
        emit imageRotationChanged();
    }
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
        switch (tileObject->bonusType)
        {
        case QmlEnums::BonusType::Wheat: wheat++; break;
        case QmlEnums::BonusType::Barrel: barrels++; break;
        case QmlEnums::BonusType::Cloth: cloth++; break;
        }
    }

    return { wheat, barrels, cloth };
}

void Tile::updateBonuses()
{
    bonusTypes = {
                  checkConnector(TileSide::North)->getBonusType(),
        checkConnector(TileSide::East)->getBonusType(),
        checkConnector(TileSide::South)->getBonusType(),
        checkConnector(TileSide::West)->getBonusType()
    };
    emit tileBonusesChanged();
}
