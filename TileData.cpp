#include "TileData.h"
#include <QDebug>

const int InvalidId = 0;

QString ObjectTypeStrings[] = {
   "x",
   "T",
   "R",
   "F",
   "M"
};

template<typename T, typename ... Ts>
bool sameType(T type0, const Ts&... args)
{
    return ((type0 == args) && ...);
}

template<typename ... T>
bool sameInitialId(const std::shared_ptr<MapObjectData>& obj0, const T&... args)
{
    return ((obj0->initialId == args->initialId) && ...);
}

template<typename ... T>
bool sameId(const std::shared_ptr<MapObjectData>& obj0, const T&... args)
{
    return ((obj0->currentObject()->initialId == args->currentObject()->initialId) && ...);
}

// ! returns 0 in case the ids are not all equal, the id otherwise
template <typename ... T>
unsigned commonId(const std::shared_ptr<MapObjectData>& obj0, const T&... args)
{
    return (((obj0->currentObject()->initialId == args->currentObject()->initialId) ? obj0->currentObject()->initialId : InvalidId) & ...);
}

void TileData::print() const
{
    for (int i = 0; i < 5; ++i)
    {
       for (int j = 0; j < 5; ++j)
       {
           if (grid5x5[i][j])
           {
               qDebug() << ObjectTypeStrings[static_cast<int>(grid5x5[i][j]->currentObject()->type)]
                       << grid5x5[i][j]->currentObject()->initialId << '\t';
           }
           else
           {
               qDebug() << "x0\t";
           }
       }
       qDebug();
    }
}

int TileData::id_NE() const
{
    return NE()->currentObject()->initialId;
}

int TileData::id_SE() const
{
    return SE()->currentObject()->initialId;
}

int TileData::id_SW() const
{
    return SW()->currentObject()->initialId;
}

int TileData::id_NW() const
{
    return NW()->currentObject()->initialId;
}

int TileData::id_N() const
{
    return N()->currentObject()->initialId;
}

int TileData::id_S() const
{
    return S()->currentObject()->initialId;
}

int TileData::id_E() const
{
    return E()->currentObject()->initialId;
}

int TileData::id_W() const
{
    return W()->currentObject()->initialId;
}

bool TileData::hasAbbey() const
{
    return sameType(ObjectType::Abbey, N()->type, E()->type, S()->type, E()->type,
                    NW()->type, NE()->type, SE()->type, SW()->type) &&
           sameInitialId(N(), E(), S(), W(), NW(), NE(), SE(), SW());
}

int TileData::abbeyId() const
{
    return commonId(N(), E(), S(), W(), NW(), NE(), SE(), SW());
}

bool TileData::hasMonastery() const
{
    return C() && C()->type == ObjectType::Monastery;
}

int TileData::monasteryId() const
{
    return C() ? C()->initialId : InvalidId;
}

bool TileData::hasFieldWhole() const
{
    return sameType(ObjectType::Field, NW()->type, NE()->type, SE()->type, SW()->type) &&
            sameInitialId(NW(), NE(), SE(), SW());
}

int TileData::fieldWholeId() const
{
    return commonId(NW(), NE(), SE(), SW());
}

bool TileData::hasFieldHalfNorth() const
{
    return sameType(ObjectType::Field, NW()->type, NE()->type) &&
            sameInitialId(NW(), NE()) &&
            !sameInitialId(NW(), W()) &&
            !sameInitialId(NW(), SW()) &&
            !sameInitialId(NE(), E()) &&
            !sameInitialId(NE(), SE());
}

int TileData::fieldHalfNorthId() const
{
    return commonId(NW(), NE());
}

bool TileData::hasFieldHalfEast() const
{
    return copy().rotateClockwise(3).hasFieldHalfNorth();
}

int TileData::fieldHalfEastId() const
{
    return commonId(SE(), NE());
}

bool TileData::hasFieldHalfSouth() const
{
    return copy().rotateClockwise(2).hasFieldHalfNorth();
}

int TileData::fieldHalfSouthId() const
{
    return commonId(SW(), SE());
}

bool TileData::hasFieldHalfWest() const
{
    return copy().rotateClockwise(1).hasFieldHalfNorth();
}

int TileData::fieldHalfWestId() const
{
    return commonId(SW(), NW());
}

bool TileData::hasFieldNorthEast() const
{
    bool r = NE() && NE()->type == ObjectType::Field &&
            N()->type != ObjectType::Field && E()->type != ObjectType::Field &&
            !sameInitialId(NE(), SE()) && !sameInitialId(NE(), NW()) && !sameInitialId(NE(), SW()) &&
            !hasAnyL_Road(); // && !hasAnyL_Road();
    return r;
}

bool TileData::hasFieldSouthEast() const
{
    return copy().rotateClockwise(3).hasFieldNorthEast();
}

bool TileData::hasFieldSouthWest() const
{
    return copy().rotateClockwise(2).hasFieldNorthEast();
}

bool TileData::hasFieldNorthWest() const
{
    return copy().rotateClockwise(1).hasFieldNorthEast();
}

bool TileData::hasFieldArc2cNorth() const
{
    return N() && N()->type == ObjectType::Field &&
            sameType(ObjectType::Town, NW()->type, NE()->type) &&
            sameInitialId(NW(), NE());
}

bool TileData::hasFieldArc2cEast() const
{
    return copy().rotateClockwise(3).hasFieldArc2cNorth();
}

bool TileData::hasFieldArc2cSouth() const
{
    return copy().rotateClockwise(2).hasFieldArc2cNorth();
}

bool TileData::hasFieldArc2cWest() const
{
    return copy().rotateClockwise(1).hasFieldArc2cNorth();
}

bool TileData::hasFieldArc3cNorthEast() const
{
    return hasTown2e2cSouthWest() && sameType(ObjectType::Field, N()->type, E()->type);
}

int TileData::fieldArc3cNorthEastId() const
{
    return commonId(N(), E());
}

bool TileData::hasFieldArc3cSouthEast() const
{
    return copy().rotateClockwise(3).hasFieldArc3cNorthEast();
}

int TileData::fieldArc3cSouthEastId() const
{
    return commonId(S(), E());
}

bool TileData::hasFieldArc3cSouthWest() const
{
    return copy().rotateClockwise(2).hasFieldArc3cNorthEast();
}

int TileData::fieldArc3cSouthWestId() const
{
    return commonId(S(), W());
}

bool TileData::hasFieldArc3cNorthWest() const
{
    return copy().rotateClockwise(1).hasFieldArc3cNorthEast();
}

int TileData::fieldArc3cNorthWestId() const
{
    return commonId(N(), W());
}

bool TileData::hasField3qNoNorthEast() const
{
    return sameType(ObjectType::Field, NW()->type, SW()->type, SE()->type) &&
            sameInitialId(NW(), SW(), SE()) &&
            SW()->initialId != E()->initialId &&
            SW()->initialId != NE()->initialId &&
            SW()->initialId != N()->initialId;
}

int TileData::field3qNoNorthEastId() const
{
    return commonId(NW(), SW(), SE());
}

bool TileData::hasField3qNoNorthWest() const
{
    return copy().rotateClockwise(1).hasField3qNoNorthEast();
}

int TileData::field3qNoNorthWestId() const
{
    return commonId(NE(), SW(), SE());
}

bool TileData::hasField3qNoSouthEast() const
{
    return copy().rotateClockwise(3).hasField3qNoNorthEast();
}

int TileData::field3qNoSouthEastId() const
{
    return commonId(NE(), SW(), NW());
}

bool TileData::hasField3qNoSouthWest() const
{
    return copy().rotateClockwise(2).hasField3qNoNorthEast();
}

int TileData::field3qNoSouthWestId() const
{
    return commonId(NE(), SE(), NW());
}

bool TileData::hasFieldDiagonalNWSE() const
{
    return sameType(ObjectType::Field, NW()->type, SE()->type) &&
            sameInitialId(NW(), SE()) &&
            !sameInitialId(NW(), SW()) &&
            !sameInitialId(NW(), NE());
}

int TileData::fieldDiagonalNWSEId() const
{
    return commonId(SE(), NW());
}

bool TileData::hasFieldDiagonalNESW() const
{
    return copy().rotateClockwise(1).hasFieldDiagonalNWSE();
}

int TileData::fieldDiagonalNESWId() const
{
    return commonId(NE(), SW());
}

bool TileData::hasFieldLTriangleNorthEast() const
{
    return NE() && NE()->type == ObjectType::Field &&
            hasL_NorthWestRoad();
}

bool TileData::hasFieldLTriangleNorthWest() const
{
    return copy().rotateClockwise(1).hasFieldLTriangleNorthEast();
}

bool TileData::hasFieldLTriangleSouthEast() const
{
    return copy().rotateClockwise(3).hasFieldLTriangleNorthEast();
}

bool TileData::hasFieldLTriangleSouthWest() const
{
    return copy().rotateClockwise(2).hasFieldLTriangleNorthEast();
}

bool TileData::hasFieldLTrapezoidNorthEast() const
{
    return NE() && NE()->type == ObjectType::Field &&
            hasL_NorthEastRoad();
}

bool TileData::hasFieldLTrapezoidNorthWest() const
{
    return copy().rotateClockwise(1).hasFieldLTrapezoidNorthEast();
}

bool TileData::hasFieldLTrapezoidSouthEast() const
{
    return copy().rotateClockwise(3).hasFieldLTrapezoidNorthEast();
}

bool TileData::hasFieldLTrapezoidSouthWest() const
{
    return copy().rotateClockwise(2).hasFieldLTrapezoidNorthEast();
}

bool TileData::hasTown1eArcNorth() const
{
    return N() && N()->type == ObjectType::Town && N()->initialValency == 1 &&
            SE()->initialId != N()->initialId &&
            SW()->initialId != N()->initialId;
}

bool TileData::hasTown1eArcEast() const
{
    return copy().rotateClockwise(3).hasTown1eArcNorth();
}

bool TileData::hasTown1eArcSouth() const
{
    return copy().rotateClockwise(2).hasTown1eArcNorth();
}

bool TileData::hasTown1eArcWest() const
{
    return copy().rotateClockwise(1).hasTown1eArcNorth();
}

bool TileData::hasTown1e4cNorth() const
{
    return N() && N()->type == ObjectType::Town && N()->initialValency == 1 &&
            sameInitialId(SE(), SW(), N(), NE(), NW());
}

bool TileData::hasTown1e4cEast() const
{
    return copy().rotateClockwise(3).hasTown1e4cNorth();
}

bool TileData::hasTown1e4cSouth() const
{
    return copy().rotateClockwise(2).hasTown1e4cNorth();
}

bool TileData::hasTown1e4cWest() const
{
    return copy().rotateClockwise(1).hasTown1e4cNorth();
}

bool TileData::hasTown2eNorthSouth() const
{
    return N() && S() &&
            sameType(ObjectType::Town, N()->type, S()->type) &&
            sameInitialId(S(), N()) &&
            N()->initialValency == 2;
}

int TileData::town2eNorthSouthId() const
{
    return commonId(N(), S());
}

bool TileData::hasTown2eEastWest() const
{
    return copy().rotateClockwise(1).hasTown2eNorthSouth();
}

int TileData::town2eEastWestId() const
{
    return commonId(E(), W());
}

bool TileData::hasTown2e2cNorthEast() const
{
    return N() && E() &&
            sameType(ObjectType::Town, N()->type, E()->type) &&
            sameInitialId(N(), E()) &&
            !sameInitialId(N(), S()) &&
            !sameInitialId(N(), W()) &&
            !sameInitialId(N(), SW());
}

int TileData::town2e2cNorthEastId() const
{
    return commonId(N(), E());
}

bool TileData::hasTown2e2cNorthWest() const
{
    return copy().rotateClockwise(1).hasTown2e2cNorthEast();
}

int TileData::town2e2cNorthWestId() const
{
    return commonId(N(), W());
}

bool TileData::hasTown2e2cSouthEast() const
{
    return copy().rotateClockwise(3).hasTown2e2cNorthEast();
}

int TileData::town2e2cSouthEastId() const
{
    return commonId(S(), E());
}

bool TileData::hasTown2e2cSouthWest() const
{
    return copy().rotateClockwise(2).hasTown2e2cNorthEast();
}

int TileData::town2e2cSouthWestId() const
{
    return commonId(S(), W());
}

bool TileData::hasTown2e3cNorthEast() const
{
    return N() && E() && SW() &&
            sameType(ObjectType::Town, N()->type, E()->type, SW()->type) &&
            sameInitialId(N(), E(), SW()) &&
            !sameInitialId(N(), S()) &&
            !sameInitialId(N(), W());
}

int TileData::town2e3cNorthEastId() const
{
    return commonId(N(), E());
}

bool TileData::hasTown2e3cNorthWest() const
{
    return copy().rotateClockwise(1).hasTown2e3cNorthEast();
}

int TileData::town2e3cNorthWestId() const
{
    return commonId(N(), W());
}

bool TileData::hasTown2e3cSouthEast() const
{
    return copy().rotateClockwise(3).hasTown2e3cNorthEast();
}

int TileData::town2e3cSouthEastId() const
{
    return commonId(S(), E());
}

bool TileData::hasTown2e3cSouthWest() const
{
    return copy().rotateClockwise(2).hasTown2e3cNorthEast();
}

int TileData::town2e3cSouthWestId() const
{
    return commonId(S(), W());
}

bool TileData::hasTownWhole() const
{
    return sameType(ObjectType::Town, N()->type, E()->type, S()->type, W()->type) &&
            sameInitialId(N(), E(), S(), W());
}

int TileData::townWholeId() const
{
    return commonId(N(), E(), S(), W());
}

bool TileData::hasRoadNorth() const
{
    return N() &&
            N()->type == ObjectType::Road &&
            N()->initialValency == 1/* &&
            hasFieldWhole()*/;
}

bool TileData::hasRoadEast() const
{
    return copy().rotateClockwise(3).hasRoadNorth();
}

bool TileData::hasRoadSouth() const
{
    return copy().rotateClockwise(2).hasRoadNorth();
}

bool TileData::hasRoadWest() const
{
    return copy().rotateClockwise(1).hasRoadNorth();
}

bool TileData::hasC_ToTown_NorthEastRoad() const
{
    return N() &&
            N()->type == ObjectType::Road &&
            N()->initialValency == 1 &&
            E() && E()->type == ObjectType::Town &&
            hasFieldNorthEast();
}

bool TileData::hasC_ToTown_NorthWestRoad() const
{
    return N() &&
            N()->type == ObjectType::Road &&
            N()->initialValency == 1 &&
            W() && W()->type == ObjectType::Town &&
            hasFieldNorthWest();
}

bool TileData::hasC_ToTown_SouthEastRoad() const
{
    return copy().rotateClockwise(2).hasC_ToTown_NorthWestRoad();
}

bool TileData::hasC_ToTown_SouthWestRoad() const
{
    return copy().rotateClockwise(2).hasC_ToTown_NorthEastRoad();
}

bool TileData::hasC_ToTown_EastNorthRoad() const
{
    return copy().rotateClockwise(3).hasC_ToTown_NorthWestRoad();
}

bool TileData::hasC_ToTown_EastSouthRoad() const
{
    return copy().rotateClockwise(3).hasC_ToTown_NorthEastRoad();
}

bool TileData::hasC_ToTown_WestNorthRoad() const
{
    return copy().rotateClockwise(1).hasC_ToTown_NorthEastRoad();
}

bool TileData::hasC_ToTown_WestSouthRoad() const
{
    return copy().rotateClockwise(1).hasC_ToTown_NorthWestRoad();
}

bool TileData::hasRoadNorthSouth() const
{
    auto [nw, ne] = getSideConnectors(Direction::North);
    auto [sw, se] = getSideConnectors(Direction::South);
    return N() && S() &&
           sameType(ObjectType::Road, N()->type, S()->type) &&
           N()->initialId == S()->initialId &&
           N()->initialValency == 2 &&
           nw->initialId != ne->initialId &&
           sw->initialId != se->initialId;
}

int TileData::roadNorthSouthId() const
{
    return commonId(N(), S());
}

bool TileData::hasRoadEastWest() const
{
    return copy().rotateClockwise(1).hasRoadNorthSouth();
}

int TileData::roadEastWestId() const
{
    return commonId(E(), W());
}

bool TileData::hasRoadDownThroughTownNorthSouth() const
{
    auto [nw, ne] = getSideConnectors(Direction::North);
    auto [sw, se] = getSideConnectors(Direction::South);
    return N() && S() &&
           sameType(ObjectType::Road, N()->type, S()->type) &&
           N()->initialId == S()->initialId &&
           N()->initialValency == 2 &&
           nw->initialId == ne->initialId &&
           sw->initialId != se->initialId;
}

int TileData::roadDownThroughTownNorthSouthId() const
{
    return commonId(N(), S());
}

bool TileData::hasRoadDownThroughTownEastWest() const
{
    return copy().rotateClockwise(3).hasRoadDownThroughTownNorthSouth();
}

int TileData::roadDownThroughTownEastWestId() const
{
    return commonId(E(), W());
}

bool TileData::hasRoadDownThroughTownSouthNorth() const
{
    return copy().rotateClockwise(2).hasRoadDownThroughTownNorthSouth();
}

int TileData::roadDownThroughTownSouthNorthId() const
{
    return commonId(N(), S());
}

bool TileData::hasRoadDownThroughTownWestEast() const
{
    return copy().rotateClockwise(1).hasRoadDownThroughTownNorthSouth();
}

int TileData::roadDownThroughTownWestEastId() const
{
    return commonId(E(), W());
}

bool TileData::hasT_NorthWestSouthRoad() const
{
    return N() && W() && S() &&
            sameType(ObjectType::Road, N()->type, W()->type, S()->type) &&
            sameInitialId(N(), S(), W()) &&
            N()->initialValency == 3;
}

int TileData::T_NorthWestSouthRoadId() const
{
    return commonId(N(), W(), S());
}

bool TileData::hasT_WestSouthEastRoad() const
{
    return copy().rotateClockwise(1).hasT_NorthWestSouthRoad();
}

int TileData::T_WestSouthEastRoadId() const
{
    return commonId(E(), W(), S());
}

bool TileData::hasT_SouthEastNorthRoad() const
{
    return copy().rotateClockwise(2).hasT_NorthWestSouthRoad();
}

int TileData::T_SouthEastNorthRoadId() const
{
    return commonId(E(), N(), S());
}

bool TileData::hasT_EastNorthWestRoad() const
{
    return copy().rotateClockwise(3).hasT_NorthWestSouthRoad();
}

int TileData::T_EastNorthWestRoadId() const
{
    return commonId(E(), W(), N());
}

bool TileData::hasC_NorthEastRoad() const
{
    return N() && E() &&
            sameType(ObjectType::Road, N()->type, E()->type) &&
            sameInitialId(N(), E())  &&
            N()->initialValency == 2 &&
            sameInitialId(NW(), SE());
}

int TileData::C_NorthEastRoadId() const
{
    return commonId(E(), N());
}

bool TileData::hasC_NorthWestRoad() const
{
    return copy().rotateClockwise(1).hasC_NorthEastRoad();
}

int TileData::C_NorthWestRoadId() const
{
    return commonId(W(), N());
}

bool TileData::hasC_SouthEastRoad() const
{
    return copy().rotateClockwise(3).hasC_NorthEastRoad();
}

int TileData::C_SouthEastRoadId() const
{
    return commonId(E(), S());
}

bool TileData::hasC_SouthWestRoad() const
{
    return copy().rotateClockwise(2).hasC_NorthEastRoad();
}

int TileData::C_SouthWestRoadId() const
{
    return commonId(W(), S());
}

bool TileData::hasL_NorthEastRoad() const
{
    return N() && E() &&
            sameType(ObjectType::Road, N()->type, E()->type) &&
            sameInitialId(N(), E()) &&
            N()->initialValency == 2 &&
            sameType(ObjectType::Field, NW()->type, SW()->type, SE()->type) &&
            !sameInitialId(NW(), SE()) &&
            sameInitialId(NW(), SW());
}

int TileData::L_NorthEastRoadId() const
{
    return commonId(E(), N());
}

bool TileData::hasL_NorthWestRoad() const
{
    return copy().rotateClockwise(1).hasL_NorthEastRoad();
}

int TileData::L_NorthWestRoadId() const
{
    return commonId(W(), N());
}

bool TileData::hasL_SouthEastRoad() const
{
    return copy().rotateClockwise(3).hasL_NorthEastRoad();
}

int TileData::L_SouthEastRoadId() const
{
    return commonId(E(), S());
}

bool TileData::hasL_SouthWestRoad() const
{
    return copy().rotateClockwise(2).hasL_NorthEastRoad();
}

int TileData::L_SouthWestRoadId() const
{
    return commonId(W(), S());
}

bool TileData::hasAnyL_Road() const
{
    return hasL_NorthEastRoad() ||
            hasL_NorthWestRoad() ||
            hasL_SouthEastRoad() ||
            hasL_SouthWestRoad();
}

std::shared_ptr<MapObjectData> TileData::getConnector(Direction direction)
{
    switch (direction) {
    case Direction::North: return grid5x5[0][2]; break;
    case Direction::East: return grid5x5[2][4]; break;
    case Direction::South: return grid5x5[4][2]; break;
    case Direction::West: return grid5x5[2][0]; break;
    default: qDebug() << "Unknown direction" << (int)direction; return nullptr;
    }
}

std::pair<std::shared_ptr<MapObjectData>, std::shared_ptr<MapObjectData> > TileData::getSideConnectors(Direction direction) const
{
    switch (direction) {
    case Direction::North: return { NNW() ? NNW() : NW(), NNE() ? NNE() : NE() }; break;
    case Direction::East: return { NEE() ? NEE() : NE(), SEE() ? SEE() : SE() }; break;
    case Direction::South: return { SSW() ? SSW() : SW(), SSE() ? SSE() : SE() }; break;
    case Direction::West: return { NWW() ? NWW() : NW(), SWW() ? SWW() : SW() }; break;
    default: qDebug() << "Unknown direction" << (int)direction; return { nullptr, nullptr };
    }
}

std::shared_ptr<const MapObjectData> TileData::checkConnector(Direction direction) const
{
    switch (direction) {
        case Direction::North: return N(); break;
        case Direction::East: return E(); break;
        case Direction::South: return S(); break;
        case Direction::West: return W(); break;
        default: qDebug() << "Unknown direction" << (int)direction; return nullptr;
    }
}

void TileData::checkCompletion(std::shared_ptr<MapObjectData> object)
{
    qDebug() << "Reimplement me";
}

void TileData::mergeObjectShapes(std::shared_ptr<MapObjectData> absorbingObject, std::shared_ptr<MapObjectData> absorbedObject) const
{
    if (absorbedObject->initialId == absorbingObject->initialId)
    {
        qDebug() << "merging object with equal initial id:" << absorbedObject->initialId;
        return;
    }

    if (absorbedObject->currentObject() != absorbingObject->currentObject())
    {
        int otherValency = absorbedObject->currentObject()->valency;
        absorbingObject->currentObject()->valency += otherValency - 2;
    }
    else
    {
        absorbingObject->currentObject()->valency -= 2;
    }
}

const std::shared_ptr<MapObjectData> TileData::NW() const { return grid5x5[0][0]; }
const std::shared_ptr<MapObjectData> TileData::NNW() const { return grid5x5[0][1]; }
const std::shared_ptr<MapObjectData> TileData::N() const { return grid5x5[0][2]; }
const std::shared_ptr<MapObjectData> TileData::NNE() const { return grid5x5[0][3]; }
const std::shared_ptr<MapObjectData> TileData::NE() const { return grid5x5[0][4]; }
const std::shared_ptr<MapObjectData> TileData::NWW() const { return grid5x5[1][0]; }
const std::shared_ptr<MapObjectData> TileData::NEE() const { return grid5x5[1][4]; }
const std::shared_ptr<MapObjectData> TileData::W() const { return grid5x5[2][0]; }
const std::shared_ptr<MapObjectData> TileData::C() const { return grid5x5[2][2]; }
const std::shared_ptr<MapObjectData> TileData::E() const { return grid5x5[2][4]; }
const std::shared_ptr<MapObjectData> TileData::SWW() const { return grid5x5[3][0]; }
const std::shared_ptr<MapObjectData> TileData::SEE() const { return grid5x5[3][4]; }
const std::shared_ptr<MapObjectData> TileData::SW() const { return grid5x5[4][0]; }
const std::shared_ptr<MapObjectData> TileData::SSW() const { return grid5x5[4][1]; }
const std::shared_ptr<MapObjectData> TileData::S() const { return grid5x5[4][2]; }
const std::shared_ptr<MapObjectData> TileData::SSE() const { return grid5x5[4][3]; }
const std::shared_ptr<MapObjectData> TileData::SE() const { return grid5x5[4][4]; }

TileData TileData::copy() const
{
    return *this;
}

TileData& TileData::rotateClockwise(int times)
{
    while (times-- > 0) {
        RotateClockwise();
    }

    return *this;
}

TileData::TileData(std::vector<TileObject> &&objects)
    : grid5x5 {
          {nullptr,nullptr,nullptr,nullptr,nullptr},
          {nullptr,nullptr,nullptr,nullptr,nullptr},
          {nullptr,nullptr,nullptr,nullptr,nullptr},
          {nullptr,nullptr,nullptr,nullptr,nullptr},
          {nullptr,nullptr,nullptr,nullptr,nullptr}
          },
      tileObjects(std::move(objects)),
      isAbbeyTile(tileObjects.size() == 1 && tileObjects[0].objPtr->type == ObjectType::Abbey)
{
    for (auto& tileObject: tileObjects)
    {
        for (auto& location: tileObject.location)
        {
            grid5x5[location.first][location.second] = tileObject.objPtr;
        }
    }
}

void TileData::RotateClockwise()
{
    auto swap = grid5x5[0][0];
    grid5x5[0][0] = grid5x5[4][0];
    grid5x5[4][0] = grid5x5[4][4];
    grid5x5[4][4] = grid5x5[0][4];
    grid5x5[0][4] = swap;

    swap = grid5x5[0][1];
    grid5x5[0][1] = grid5x5[3][0];
    grid5x5[3][0] = grid5x5[4][3];
    grid5x5[4][3] = grid5x5[1][4];
    grid5x5[1][4] = swap;

    swap = grid5x5[0][2];
    grid5x5[0][2] = grid5x5[2][0];
    grid5x5[2][0] = grid5x5[4][2];
    grid5x5[4][2] = grid5x5[2][4];
    grid5x5[2][4] = swap;

    swap = grid5x5[0][3];
    grid5x5[0][3] = grid5x5[1][0];
    grid5x5[1][0] = grid5x5[4][1];
    grid5x5[4][1] = grid5x5[3][4];
    grid5x5[3][4] = swap;
}

void TileData::RotateCounterclockwise()
{
    auto swap = grid5x5[0][0];
    grid5x5[0][0] = grid5x5[0][4];
    grid5x5[0][4] = grid5x5[4][4];
    grid5x5[4][4] = grid5x5[4][0];
    grid5x5[4][0] = swap;

    swap = grid5x5[0][1];
    grid5x5[0][1] = grid5x5[1][4];
    grid5x5[1][4] = grid5x5[4][3];
    grid5x5[4][3] = grid5x5[3][0];
    grid5x5[3][0] = swap;

    swap = grid5x5[0][2];
    grid5x5[0][2] = grid5x5[2][4];
    grid5x5[2][4] = grid5x5[4][2];
    grid5x5[4][2] = grid5x5[2][0];
    grid5x5[2][0] = swap;

    swap = grid5x5[0][3];
    grid5x5[0][3] = grid5x5[3][4];
    grid5x5[3][4] = grid5x5[4][1];
    grid5x5[4][1] = grid5x5[1][0];
    grid5x5[1][0] = swap;
}

bool TileData::CanConnect(const TileData &other, Direction from) const
{
    switch (from) {
    case Direction::North:
        return checkConnector(Direction::North)->type == other.checkConnector(Direction::South)->type;
    case Direction::East:
        return checkConnector(Direction::East)->type == other.checkConnector(Direction::West)->type;
    case Direction::South:
        return checkConnector(Direction::South)->type == other.checkConnector(Direction::North)->type;
    case Direction::West:
        return checkConnector(Direction::West)->type == other.checkConnector(Direction::East)->type;
    }

    qDebug() << "Unknown direction" << (int)from;
    return false;
}

TileObject::TileObject(std::shared_ptr<MapObjectData> _objPtr, std::vector<std::pair<int, int> > _location, TileData *_tile)
    : objPtr(_objPtr), location(_location), tile(_tile)
{
}

TileObject::TileObject(const TileObject &other)
    : objPtr(other.objPtr), location(other.location), tile(other.tile)
{
}

TileObject::TileObject(TileObject &&other)
    : objPtr(std::move(other.objPtr)), location(std::move(other.location)), tile(std::move(other.tile))
{
}

void TileData::Connect(TileData &other, Direction from, std::set<Tile*>& updatedTiles)
{
    // not checking the connection validity

    // merge objects
    std::shared_ptr<MapObjectData> connectorObject = getConnector(from);
    std::shared_ptr<MapObjectData> otherConnectorObject = other.getConnector(opposite(from));

    switch (otherConnectorObject->type) {
    case ObjectType::Town: {
        // update exits count, score
        mergeObjectShapes(connectorObject, otherConnectorObject);

        // merge ids
        connectorObject->mergeObject(otherConnectorObject, updatedTiles);

        checkCompletion(connectorObject);
        break;
    }
    case ObjectType::Field: {
        // merge ids
        connectorObject->mergeObject(otherConnectorObject, updatedTiles);
        break;
    }
    case ObjectType::Road: {
        // update exits count, score
        mergeObjectShapes(connectorObject, otherConnectorObject);

        // merge ids
        connectorObject->mergeObject(otherConnectorObject, updatedTiles);

        checkCompletion(connectorObject);

        // merge side fields
        auto [sideConnector1, sideConnector2] = getSideConnectors(from);
        auto [otherSideConnector1, otherSideConnector2] = other.getSideConnectors(opposite(from));

        sideConnector1->mergeObject(otherSideConnector1, updatedTiles);
        sideConnector2->mergeObject(otherSideConnector2, updatedTiles);

        break;
    }
    case ObjectType::Abbey: {
        break;
    }
    default:
        qDebug() << "Error: cannot connect" << ObjectTypeStrings[static_cast<int>(connectorObject->type)];
    }
}
