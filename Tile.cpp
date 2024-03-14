#include "Tile.h"
#include <QPoint>
#include <QQmlEngine>

Tile::Tile(const std::vector<std::pair<std::shared_ptr<TileObject>, TileData::ObjectLocation>>& objects, const QUrl &image, int imgRotation, QObject *parent)
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

void Tile::checkObjectCompletion(std::shared_ptr<TileObject> object)
{
    if (object->currentObject()->isCompleted())
    {
        emit objectCompleted(object->currentObject()->initialId);
    }
}

TileObject* Tile::abbeyObject() const
{
    return hasAbbey() ? N().get() : nullptr;
}

TileObject *Tile::monasteryObject() const
{
    return hasMonastery() ? C().get() : nullptr;
}

TileObject *Tile::fieldWholeObject() const
{
    return hasFieldWhole() ? NW().get() : nullptr;
}

TileObject *Tile::fieldHalfNorthObject() const
{
    return hasFieldHalfNorth() ? NW().get() : nullptr;
}

TileObject *Tile::fieldHalfEastObject() const
{
    return hasFieldHalfEast() ? SE().get() : nullptr;
}

TileObject *Tile::fieldHalfSouthObject() const
{
    return hasFieldHalfSouth() ? SE().get() : nullptr;
}

TileObject *Tile::fieldHalfWestObject() const
{
    return hasFieldHalfWest() ? NW().get() : nullptr;
}

TileObject *Tile::fieldNorthEastObject() const
{
    return hasFieldNorthEast() ? NE().get() : nullptr;
}

TileObject *Tile::fieldSouthEastObject() const
{
    return hasFieldSouthEast() ? SE().get() : nullptr;
}

TileObject *Tile::fieldSouthWestObject() const
{
    return hasFieldSouthWest() ? SW().get() : nullptr;
}

TileObject *Tile::fieldNorthWestObject() const
{
    return hasFieldNorthWest() ? NW().get() : nullptr;
}

TileObject *Tile::fieldArc2cNorthObject() const
{
    return hasFieldArc2cNorth() ? N().get() : nullptr;
}

TileObject *Tile::fieldArc2cEastObject() const
{
    return hasFieldArc2cEast() ? E().get() : nullptr;
}

TileObject *Tile::fieldArc2cSouthObject() const
{
    return hasFieldArc2cSouth() ? S().get() : nullptr;
}

TileObject *Tile::fieldArc2cWestObject() const
{
    return hasFieldArc2cWest() ? W().get() : nullptr;
}

TileObject *Tile::fieldArc3cNorthEastObject() const
{
    return hasFieldArc3cNorthEast() ? N().get() : nullptr;
}

TileObject *Tile::fieldArc3cSouthEastObject() const
{
    return hasFieldArc3cSouthEast() ? S().get() : nullptr;
}

TileObject *Tile::fieldArc3cSouthWestObject() const
{
    return hasFieldArc3cSouthWest() ? S().get() : nullptr;
}

TileObject *Tile::fieldArc3cNorthWestObject() const
{
    return hasFieldArc3cNorthWest() ? N().get() : nullptr;
}

TileObject *Tile::field3qNoNorthEastObject() const
{
    return hasField3qNoNorthEast() ? NW().get() : nullptr;
}

TileObject *Tile::field3qNoNorthWestObject() const
{
    return hasField3qNoNorthWest() ? SE().get() : nullptr;
}

TileObject *Tile::field3qNoSouthEastObject() const
{
    return hasField3qNoSouthEast() ? NW().get() : nullptr;
}

TileObject *Tile::field3qNoSouthWestObject() const
{
    return hasField3qNoSouthWest() ? NW().get() : nullptr;
}

TileObject *Tile::fieldDiagonalNWSEObject() const
{
    return hasFieldDiagonalNWSE() ? SE().get() : nullptr;
}

TileObject *Tile::fieldDiagonalNESWObject() const
{
    return hasFieldDiagonalNESW() ? NE().get() : nullptr;
}

TileObject *Tile::fieldLTriangleNorthEastObject() const
{
    return hasFieldLTriangleNorthEast() ? NE().get() : nullptr;
}

TileObject *Tile::fieldLTriangleNorthWestObject() const
{
    return hasFieldLTriangleNorthWest() ? NW().get() : nullptr;
}

TileObject *Tile::fieldLTriangleSouthEastObject() const
{
    return hasFieldLTriangleSouthEast() ? SE().get() : nullptr;
}

TileObject *Tile::fieldLTriangleSouthWestObject() const
{
    return hasFieldLTriangleSouthWest() ? SW().get() : nullptr;
}

TileObject *Tile::fieldJTriangleNorthEastObject() const
{
    return hasFieldJTriangleNorthEast() ? NE().get() : nullptr;
}

TileObject *Tile::fieldJTriangleNorthWestObject() const
{
    return hasFieldJTriangleNorthWest() ? NW().get() : nullptr;
}

TileObject *Tile::fieldJTriangleSouthEastObject() const
{
    return hasFieldJTriangleSouthEast() ? SE().get() : nullptr;
}

TileObject *Tile::fieldJTriangleSouthWestObject() const
{
    return hasFieldJTriangleSouthWest() ? SW().get() : nullptr;
}

TileObject *Tile::fieldLTrapezoidNorthEastObject() const
{
    return hasFieldLTrapezoidNorthEast() ? NE().get() : nullptr;
}

TileObject *Tile::fieldLTrapezoidNorthWestObject() const
{
    return hasFieldLTrapezoidNorthWest() ? NW().get() : nullptr;
}

TileObject *Tile::fieldLTrapezoidSouthEastObject() const
{
    return hasFieldLTrapezoidSouthEast() ? SE().get() : nullptr;
}

TileObject *Tile::fieldLTrapezoidSouthWestObject() const
{
    return hasFieldLTrapezoidSouthWest() ? SW().get() : nullptr;
}

TileObject *Tile::fieldJTrapezoidNorthEastObject() const
{
    return hasFieldJTrapezoidNorthEast() ? NE().get() : nullptr;
}

TileObject *Tile::fieldJTrapezoidNorthWestObject() const
{
    return hasFieldJTrapezoidNorthWest() ? NW().get() : nullptr;
}

TileObject *Tile::fieldJTrapezoidSouthEastObject() const
{
    return hasFieldJTrapezoidSouthEast() ? SE().get() : nullptr;
}

TileObject *Tile::fieldJTrapezoidSouthWestObject() const
{
    return hasFieldJTrapezoidSouthWest() ? SW().get() : nullptr;
}

TileObject *Tile::fieldNEEObject() const
{
    return hasFieldHalfQuarterNEE() ? NEE().get() : nullptr;
}

TileObject *Tile::fieldSEEObject() const
{
    return hasFieldHalfQuarterSEE() ? SEE().get() : nullptr;
}

TileObject *Tile::fieldSSEObject() const
{
    return hasFieldHalfQuarterSSE() ? SSE().get() : nullptr;
}

TileObject *Tile::fieldSSWObject() const
{
    return hasFieldHalfQuarterSSW() ? SSW().get() : nullptr;
}

TileObject *Tile::fieldSWWObject() const
{
    return hasFieldHalfQuarterSWW() ? SWW().get() : nullptr;
}

TileObject *Tile::fieldNWWObject() const
{
    return hasFieldHalfQuarterNWW() ? NWW().get() : nullptr;
}

TileObject *Tile::fieldNNWObject() const
{
    return hasFieldHalfQuarterNNW() ? NNW().get() : nullptr;
}

TileObject *Tile::fieldNNEObject() const
{
    return hasFieldHalfQuarterNNE() ? NNE().get() : nullptr;
}

TileObject *Tile::roadNorthObject() const
{
    return hasRoadNorth() ? N().get() : nullptr;
}

TileObject *Tile::roadEastObject() const
{
    return hasRoadEast() ? E().get() : nullptr;
}

TileObject *Tile::roadSouthObject() const
{
    return hasRoadSouth() ? S().get() : nullptr;
}

TileObject *Tile::roadWestObject() const
{
    return hasRoadWest() ? W().get() : nullptr;
}

TileObject *Tile::roadLongNorthObject() const
{
    return hasRoadLongNorth() ? N().get() : nullptr;
}

TileObject *Tile::roadLongEastObject() const
{
    return hasRoadLongEast() ? E().get() : nullptr;
}

TileObject *Tile::roadLongSouthObject() const
{
    return hasRoadLongSouth() ? S().get() : nullptr;
}

TileObject *Tile::roadLongWestObject() const
{
    return hasRoadLongWest() ? W().get() : nullptr;
}

TileObject *Tile::C_ToTownNorthEastRoadObject() const
{
    return hasC_ToTown_NorthEastRoad() ? NE().get() : nullptr;
}

TileObject *Tile::C_ToTownNorthWestRoadObject() const
{
    return hasC_ToTown_NorthWestRoad() ? NW().get() : nullptr;
}

TileObject *Tile::C_ToTownSouthEastRoadObject() const
{
    return hasC_ToTown_SouthEastRoad() ? SE().get() : nullptr;
}

TileObject *Tile::C_ToTownSouthWestRoadObject() const
{
    return hasC_ToTown_SouthWestRoad() ? SW().get() : nullptr;
}

TileObject *Tile::C_ToTownEastNorthRoadObject() const
{
    return hasC_ToTown_EastNorthRoad() ? NE().get() : nullptr;
}

TileObject *Tile::C_ToTownEastSouthRoadObject() const
{
    return hasC_ToTown_EastSouthRoad() ? SE().get() : nullptr;
}

TileObject *Tile::C_ToTownWestNorthRoadObject() const
{
    return hasC_ToTown_WestNorthRoad() ? NW().get() : nullptr;
}

TileObject *Tile::C_ToTownWestSouthRoadObject() const
{
    return hasC_ToTown_WestSouthRoad() ? SW().get() : nullptr;
}

TileObject *Tile::roadNorthSouthObject() const
{
    return hasRoadNorthSouth() ? N().get() : nullptr;
}

TileObject *Tile::roadEastWestObject() const
{
    return hasRoadEastWest() ? E().get() : nullptr;
}

TileObject *Tile::roadDownThroughTownNorthSouthObject() const
{
    return hasRoadDownThroughTownNorthSouth() ? N().get() : nullptr;
}

TileObject *Tile::roadDownThroughTownEastWestObject() const
{
    return hasRoadDownThroughTownEastWest() ? E().get() : nullptr;
}

TileObject *Tile::roadDownThroughTownSouthNorthObject() const
{
    return hasRoadDownThroughTownSouthNorth() ? S().get() : nullptr;
}

TileObject *Tile::roadDownThroughTownWestEastObject() const
{
    return hasRoadDownThroughTownWestEast() ? W().get() : nullptr;
}

TileObject *Tile::T_NorthWestSouthRoadObject() const
{
    return hasT_NorthWestSouthRoad() ? N().get() : nullptr;
}

TileObject *Tile::T_WestSouthEastRoadObject() const
{
    return hasT_WestSouthEastRoad() ? W().get() : nullptr;
}

TileObject *Tile::T_SouthEastNorthRoadObject() const
{
    return hasT_SouthEastNorthRoad() ? S().get() : nullptr;
}

TileObject *Tile::T_EastNorthWestRoadObject() const
{
    return hasT_EastNorthWestRoad() ? E().get() : nullptr;
}

TileObject *Tile::C_NorthEastRoadObject() const
{
    return hasC_NorthEastRoad() ? N().get() : nullptr;
}

TileObject *Tile::C_NorthWestRoadObject() const
{
    return hasC_NorthWestRoad() ? N().get() : nullptr;
}

TileObject *Tile::C_SouthEastRoadObject() const
{
    return hasC_SouthEastRoad() ? S().get() : nullptr;
}

TileObject *Tile::C_SouthWestRoadObject() const
{
    return hasC_SouthWestRoad() ? S().get() : nullptr;
}

TileObject *Tile::L_NorthEastRoadObject() const
{
    return hasL_NorthEastRoad() ? N().get() : nullptr;
}

TileObject *Tile::L_NorthWestRoadObject() const
{
    return hasL_NorthWestRoad() ? N().get() : nullptr;
}

TileObject *Tile::L_SouthEastRoadObject() const
{
    return hasL_SouthEastRoad() ? S().get() : nullptr;
}

TileObject *Tile::L_SouthWestRoadObject() const
{
    return hasL_SouthWestRoad() ? S().get() : nullptr;
}

TileObject *Tile::J_NorthWestRoadObject() const
{
    return hasJ_NorthWestRoad() ? N().get() : nullptr;
}

TileObject *Tile::J_NorthEastRoadObject() const
{
    return hasJ_NorthEastRoad() ? N().get() : nullptr;
}

TileObject *Tile::J_SouthWestRoadObject() const
{
    return hasJ_SouthWestRoad() ? S().get() : nullptr;
}

TileObject *Tile::J_SouthEastRoadObject() const
{
    return hasJ_SouthEastRoad() ? S().get() : nullptr;
}

TileObject *Tile::town1eArcNorthObject() const
{
    return hasTown1eArcNorth() ? N().get() : nullptr;
}

TileObject *Tile::town1eArcEastObject() const
{
    return hasTown1eArcEast() ? E().get() : nullptr;
}

TileObject *Tile::town1eArcSouthObject() const
{
    return hasTown1eArcSouth() ? S().get() : nullptr;
}

TileObject *Tile::town1eArcWestObject() const
{
    return hasTown1eArcWest() ? W().get() : nullptr;
}

TileObject *Tile::town1eBridgeNorthObject() const
{
    return hasTown1eBridgeNorth() ? N().get() : nullptr;
}

TileObject *Tile::town1eBridgeEastObject() const
{
    return hasTown1eBridgeEast() ? E().get() : nullptr;
}

TileObject *Tile::town1eBridgeSouthObject() const
{
    return hasTown1eBridgeSouth() ? S().get() : nullptr;
}

TileObject *Tile::town1eBridgeWestObject() const
{
    return hasTown1eBridgeWest() ? W().get() : nullptr;
}

TileObject *Tile::town1e4cNorthObject() const
{
    return hasTown1e4cNorth() ? N().get() : nullptr;
}

TileObject *Tile::town1e4cEastObject() const
{
    return hasTown1e4cEast() ? E().get() : nullptr;
}

TileObject *Tile::town1e4cSouthObject() const
{
    return hasTown1e4cSouth() ? S().get() : nullptr;
}

TileObject *Tile::town1e4cWestObject() const
{
    return hasTown1e4cWest() ? W().get() : nullptr;
}

TileObject *Tile::town1e3cNorthToSouthEastObject() const
{
    return hasTown1e3cNorthToSouthEast() ? N().get() : nullptr;
}

TileObject *Tile::town1e3cEastToSouthWestObject() const
{
    return hasTown1e3cEastToSouthWest() ? E().get() : nullptr;
}

TileObject *Tile::town1e3cSouthToNorthWestObject() const
{
    return hasTown1e3cSouthToNorthWest() ? S().get() : nullptr;
}

TileObject *Tile::town1e3cWestToNorthEastObject() const
{
    return hasTown1e3cWestToNorthEast() ? W().get() : nullptr;
}

TileObject *Tile::town2eNorthSouthObject() const
{
    return hasTown2eNorthSouth() ? N().get() : nullptr;
}

TileObject *Tile::town2eEastWestObject() const
{
    return hasTown2eEastWest() ? E().get() : nullptr;
}

TileObject *Tile::town2e2cNorthEastObject() const
{
    return hasTown2e2cNorthEast() ? N().get() : nullptr;
}

TileObject *Tile::town2e2cNorthWestObject() const
{
    return hasTown2e2cNorthWest() ? N().get() : nullptr;
}

TileObject *Tile::town2e2cSouthEastObject() const
{
    return hasTown2e2cSouthEast() ? S().get() : nullptr;
}

TileObject *Tile::town2e2cSouthWestObject() const
{
    return hasTown2e2cSouthWest() ? S().get() : nullptr;
}

TileObject *Tile::town2e3cNorthEastObject() const
{
    return hasTown2e3cNorthEast() ? N().get() : nullptr;
}

TileObject *Tile::town2e3cNorthWestObject() const
{
    return hasTown2e3cNorthWest() ? N().get() : nullptr;
}

TileObject *Tile::town2e3cSouthEastObject() const
{
    return hasTown2e3cSouthEast() ? S().get() : nullptr;
}

TileObject *Tile::town2e3cSouthWestObject() const
{
    return hasTown2e3cSouthWest() ? S().get() : nullptr;
}

TileObject *Tile::town3e4cNorthEastWestObject() const
{
    return hasTown3e4cNorthEastWest() ? N().get() : nullptr;
}

TileObject *Tile::town3e4cEastNorthSouthObject() const
{
    return hasTown3e4cEastNorthSouth() ? E().get() : nullptr;
}

TileObject *Tile::town3e4cSouthEastWestObject() const
{
    return hasTown3e4cSouthEastWest() ? S().get() : nullptr;
}

TileObject *Tile::town3e4cWestNorthSouthObject() const
{
    return hasTown3e4cWestNorthSouth() ? W().get() : nullptr;
}

TileObject *Tile::townWholeObject() const
{
    return hasTownWhole() ? N().get() : nullptr;
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
        switch (tileObject->getBonusType())
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
