#include "TileData.h"
#include <QDebug>

const int InvalidId = 0;

QString ObjectTypeStrings[] = {
    "x",
    "T",
    "R",
    "F",
    "M",
    "A"
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

// ! returns InvalidId in case the ids are not all equal, the id otherwise
template <typename ... T>
unsigned commonId(const std::shared_ptr<MapObjectData>& obj0, const T&... args)
{
    return (((obj0->currentObject()->initialId == args->currentObject()->initialId) ? obj0->currentObject()->initialId : InvalidId) & ...);
}

void TileData::print() const
{
    for (int i = 0; i < 5; ++i)
    {
        QString row;
       for (int j = 0; j < 5; ++j)
       {
           if (grid5x5[i][j])
           {
               row += ObjectTypeStrings[static_cast<int>(grid5x5[i][j]->currentObject()->type)] +
                       QString::number(grid5x5[i][j]->currentObject()->initialId) + " ";
           }
           else
           {
               row += "x0 ";
           }
       }
       qDebug() << row;
    }
    qDebug() << " ";
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

int TileData::id_NEE() const
{
    return NEE() ? NEE()->currentObject()->initialId : InvalidId;
}

int TileData::id_SEE() const
{
    return SEE() ? SEE()->currentObject()->initialId : InvalidId;
}

int TileData::id_SSE() const
{
    return SSE() ? SSE()->currentObject()->initialId : InvalidId;
}

int TileData::id_SSW() const
{
    return SSW() ? SSW()->currentObject()->initialId : InvalidId;
}

int TileData::id_SWW() const
{
    return SWW() ? SWW()->currentObject()->initialId : InvalidId;
}

int TileData::id_NWW() const
{
    return NWW() ? NWW()->currentObject()->initialId : InvalidId;
}

int TileData::id_NNW() const
{
    return NNW() ? NNW()->currentObject()->initialId : InvalidId;
}

int TileData::id_NNE() const
{
    return NNE() ? NNE()->currentObject()->initialId : InvalidId;
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

bool TileData::hasRoadBlock() const
{
    return (hasRoadNorth() && hasRoadSouth() || hasRoadWest() && hasRoadEast()) &&
            !C();
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
            !hasAnyL_Road() && !hasAnyJ_Road();
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
    return (hasTown2e2cSouthWest() || hasTown1e3cSouthToNorthWest()) &&
            sameType(ObjectType::Field, N()->type, E()->type);
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

bool TileData::hasFieldJTriangleNorthEast() const
{
    return copy().rotateClockwise(3).hasFieldJTriangleNorthWest();
}

bool TileData::hasFieldJTriangleNorthWest() const
{
    return NW() && NW()->type == ObjectType::Field &&
            hasJ_NorthEastRoad();
}

bool TileData::hasFieldJTriangleSouthEast() const
{
    return copy().rotateClockwise(2).hasFieldJTriangleNorthWest();
}

bool TileData::hasFieldJTriangleSouthWest() const
{
    return copy().rotateClockwise(1).hasFieldJTriangleNorthWest();
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

bool TileData::hasFieldJTrapezoidNorthEast() const
{
    return copy().rotateClockwise(3).hasFieldJTrapezoidNorthWest();
}

bool TileData::hasFieldJTrapezoidNorthWest() const
{
    return NW() && NW()->type == ObjectType::Field &&
            hasJ_NorthWestRoad();
}

bool TileData::hasFieldJTrapezoidSouthEast() const
{
    return copy().rotateClockwise(2).hasFieldJTrapezoidNorthWest();
}

bool TileData::hasFieldJTrapezoidSouthWest() const
{
    return copy().rotateClockwise(1).hasFieldJTrapezoidNorthWest();
}

bool TileData::hasFieldHalfQuarterNEE() const
{
    return NEE() && NEE()->type == ObjectType::Field;
}

bool TileData::hasFieldHalfQuarterSEE() const
{
    return SEE() && SEE()->type == ObjectType::Field;
}

bool TileData::hasFieldHalfQuarterSSE() const
{
    return SSE() && SSE()->type == ObjectType::Field;
}

bool TileData::hasFieldHalfQuarterSSW() const
{
    return SSW() && SSW()->type == ObjectType::Field;
}

bool TileData::hasFieldHalfQuarterSWW() const
{
    return SWW() && SWW()->type == ObjectType::Field;
}

bool TileData::hasFieldHalfQuarterNWW() const
{
    return NWW() && NWW()->type == ObjectType::Field;
}

bool TileData::hasFieldHalfQuarterNNW() const
{
    return NNW() && NNW()->type == ObjectType::Field;
}

bool TileData::hasFieldHalfQuarterNNE() const
{
    return NNE() && NNE()->type == ObjectType::Field;
}

bool TileData::hasTown1eArcNorth() const
{
    return N() && N()->type == ObjectType::Town && N()->initialValency == 1 &&
            SE()->initialId != N()->initialId &&
            SW()->initialId != N()->initialId &&
            !hasTown1eBridgeNorth();
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

bool TileData::hasTown1eBridgeNorth() const
{
    return N() && N()->type == ObjectType::Town && N()->initialValency == 1 &&
            hasTown2eEastWest() &&
            sameType(ObjectType::Field, NE()->type, NW()->type) &&
            !sameInitialId(NE(), NW());
}

bool TileData::hasTown1eBridgeEast() const
{
    return copy().rotateClockwise(3).hasTown1eBridgeNorth();
}

bool TileData::hasTown1eBridgeSouth() const
{
    return copy().rotateClockwise(2).hasTown1eBridgeNorth();
}

bool TileData::hasTown1eBridgeWest() const
{
    return copy().rotateClockwise(1).hasTown1eBridgeNorth();
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

bool TileData::hasTown1e3cNorthToSouthEast() const
{
    bool a1 = N() && N()->type == ObjectType::Town && N()->initialValency == 1;
    bool a2 = sameInitialId(SE(), N());
    bool a3 = hasFieldArc2cEast();
    bool a4 = sameInitialId(W(), S(), SW()) && sameType(ObjectType::Field, S()->type, W()->type, SW()->type);
    bool a5 = !sameInitialId(SW(), E());
    return a1 && a2 && a3 && a4 && a5;
}

bool TileData::hasTown1e3cEastToSouthWest() const
{
    return copy().rotateClockwise(3).hasTown1e3cNorthToSouthEast();
}

bool TileData::hasTown1e3cSouthToNorthWest() const
{
    return copy().rotateClockwise(2).hasTown1e3cNorthToSouthEast();
}

bool TileData::hasTown1e3cWestToNorthEast() const
{
    return copy().rotateClockwise(1).hasTown1e3cNorthToSouthEast();
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

bool TileData::hasTown3e4cNorthEastWest() const
{
    return N() && E() && W() &&
            sameType(ObjectType::Town, N()->type, E()->type, W()->type) &&
            sameInitialId(N(), E(), W()) &&
            !sameInitialId(N(), S());
}

int TileData::town3e4cNorthEastWestId() const
{
    return commonId(N(), E(), W());
}

bool TileData::hasTown3e4cEastNorthSouth() const
{
    return copy().rotateClockwise(3).hasTown3e4cNorthEastWest();
}

int TileData::town3e4cEastNorthSouthId() const
{
    return commonId(N(), E(), S());
}

bool TileData::hasTown3e4cSouthEastWest() const
{
    return copy().rotateClockwise(2).hasTown3e4cNorthEastWest();
}

int TileData::town3e4cSouthEastWestId() const
{
    return commonId(S(), E(), W());
}

bool TileData::hasTown3e4cWestNorthSouth() const
{
    return copy().rotateClockwise(1).hasTown3e4cNorthEastWest();
}

int TileData::town3e4cWestNorthSouthId() const
{
    return commonId(N(), S(), W());
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

bool TileData::isAbbeyTile() const
{
    return tileObjects.size() == 1 && tileObjects[0].objPtr->type == ObjectType::Abbey;
}

bool TileData::hasRoadNorth() const
{
    return N() &&
            N()->type == ObjectType::Road &&
            N()->initialValency == 1 &&
            !hasC_ToTown_NorthEastRoad() &&
            !hasC_ToTown_NorthWestRoad() &&
            !hasRoadLongNorth();
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

bool TileData::hasRoadLongNorth() const
{
    return N() && N()->type == ObjectType::Road && N()->initialValency == 1 &&
            S()->type == ObjectType::Town && S()->initialValency == 1 &&
            SW()->initialId != SE()->initialId &&
            !hasC_ToTown_NorthEastRoad() &&
            !hasC_ToTown_NorthWestRoad();
}

bool TileData::hasRoadLongEast() const
{
    return copy().rotateClockwise(3).hasRoadLongNorth();
}

bool TileData::hasRoadLongSouth() const
{
    return copy().rotateClockwise(2).hasRoadLongNorth();
}

bool TileData::hasRoadLongWest() const
{
    return copy().rotateClockwise(1).hasRoadLongNorth();
}

bool TileData::hasC_ToTown_NorthEastRoad() const
{
    return N() &&
            N()->type == ObjectType::Road &&
            N()->initialValency == 1 &&
            E() && E()->type == ObjectType::Town &&
            hasFieldNorthEast() &&
            (!C() || C()->type != ObjectType::Town);
}

bool TileData::hasC_ToTown_NorthWestRoad() const
{
    return N() &&
            N()->type == ObjectType::Road &&
            N()->initialValency == 1 &&
            W() && W()->type == ObjectType::Town &&
            hasFieldNorthWest() &&
            (!C() || C()->type != ObjectType::Town);
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

bool TileData::hasJ_NorthWestRoad() const
{
    return N() && W() &&
            sameType(ObjectType::Road, N()->type, W()->type) &&
            sameInitialId(N(), W()) &&
            N()->initialValency == 2 &&
            sameType(ObjectType::Field, NE()->type, SW()->type, SE()->type) &&
            !sameInitialId(NE(), SW()) &&
            sameInitialId(NE(), SE());
}

int TileData::J_NorthWestRoadId() const
{
    return commonId(W(), N());
}

bool TileData::hasJ_NorthEastRoad() const
{
    return copy().rotateClockwise(3).hasJ_NorthWestRoad();
}

int TileData::J_NorthEastRoadId() const
{
    return commonId(E(), N());
}

bool TileData::hasJ_SouthWestRoad() const
{
    return copy().rotateClockwise(1).hasJ_NorthWestRoad();
}

int TileData::J_SouthWestRoadId() const
{
    return commonId(S(), W());
}

bool TileData::hasJ_SouthEastRoad() const
{
    return copy().rotateClockwise(2).hasJ_NorthWestRoad();
}

int TileData::J_SouthEastRoadId() const
{
    return commonId(E(), S());
}

bool TileData::hasAnyJ_Road() const
{
    return hasJ_NorthEastRoad() ||
            hasJ_NorthWestRoad() ||
            hasJ_SouthEastRoad() ||
            hasJ_SouthWestRoad();
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

void TileData::checkObjectCompletion(std::shared_ptr<MapObjectData> object)
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

void TileData::markCentralObjectCompleted()
{
    grid5x5[2][2]->markCompleted();
    checkObjectCompletion(grid5x5[2][2]);
}

bool TileData::hasCentralScorableObject() const
{
    return hasAbbey() || hasMonastery();
}

void TileData::getAdjacentTowns(std::shared_ptr<MapObjectData> &object, std::set<std::shared_ptr<MapObjectData>>& towns) const
{
    for (auto& tileObject: tileObjects)
    {
        if (object == tileObject.objPtr)
        {
            auto checkInsert = [&towns](const std::shared_ptr<MapObjectData>& object) {
                if (object && object->type == ObjectType::Town && object->currentObject()->isCompleted())
                    towns.insert(object->currentObject());
            };

            std::vector<std::pair<int, int>> location;
            for (int i = 0; i < 5; ++i)
            {
                for (int j = 0; j < 5; ++j)
                {
                    if (grid5x5[i][j] == object)
                    {
                        location.push_back({i, j});
                    }
                }
            }

            for (auto& locationPoint: location)
            {
                switch(locationPoint.first) {
                case 0:
                    switch (locationPoint.second)
                    {
                    case 0: checkInsert(grid5x5[0][2]); checkInsert(grid5x5[2][0]); break;
                    case 1: checkInsert(grid5x5[0][0]); break;
                    case 2: checkInsert(grid5x5[0][0]); checkInsert(grid5x5[0][4]); break;
                    case 3: checkInsert(grid5x5[0][4]); break;
                    case 4: checkInsert(grid5x5[0][2]); checkInsert(grid5x5[2][4]); break;
                    }
                    break;
                case 1:
                    switch (locationPoint.second)
                    {
                    case 0: checkInsert(grid5x5[0][0]); break;
                    case 4: checkInsert(grid5x5[0][4]); break;
                    }
                case 2:
                    switch (locationPoint.second)
                    {
                    case 0: checkInsert(grid5x5[0][0]); checkInsert(grid5x5[4][0]); break;
                    case 4: checkInsert(grid5x5[0][4]); checkInsert(grid5x5[4][4]); break;
                    }
                    break;
                case 3:
                    switch (locationPoint.second)
                    {
                    case 0: checkInsert(grid5x5[4][0]); break;
                    case 4: checkInsert(grid5x5[4][4]); break;
                    }
                    break;
                case 4:
                    switch (locationPoint.second)
                    {
                    case 0: checkInsert(grid5x5[4][2]); checkInsert(grid5x5[2][0]); break;
                    case 1: checkInsert(grid5x5[4][0]); break;
                    case 2: checkInsert(grid5x5[4][0]); checkInsert(grid5x5[4][4]); break;
                    case 3: checkInsert(grid5x5[4][4]); break;
                    case 4: checkInsert(grid5x5[4][2]); checkInsert(grid5x5[2][4]); break;
                    }
                    break;
                }
            }
            return;
        }
    }
}

std::set<unsigned> TileData::getFieldObjectIds() const
{
    std::set<unsigned> result;
    for (auto& tileObject: tileObjects)
    {
        if (tileObject.objPtr->type == ObjectType::Field)
        {
            result.insert(tileObject.objPtr->currentObject()->initialId);
        }
    }

    return result;
}

unsigned TileData::NEBarnCornerId() const
{
    return NE()->type == ObjectType::Field &&
            N()->type != ObjectType::Town &&
            E()->type != ObjectType::Town ?
                NE()->currentObject()->initialId : InvalidId;
}

unsigned TileData::NWBarnCornerId() const
{
    return NW()->type == ObjectType::Field &&
            N()->type != ObjectType::Town &&
            W()->type != ObjectType::Town ?
                NW()->currentObject()->initialId : InvalidId;
}

unsigned TileData::SEBarnCornerId() const
{
    return SE()->type == ObjectType::Field &&
            S()->type != ObjectType::Town &&
            E()->type != ObjectType::Town ?
                SE()->currentObject()->initialId : InvalidId;
}

unsigned TileData::SWBarnCornerId() const
{
    return SW()->type == ObjectType::Field &&
            S()->type != ObjectType::Town &&
            W()->type != ObjectType::Town ?
                SW()->currentObject()->initialId : InvalidId;
}

TileData TileData::copy() const
{
    return *this;
}

TileData& TileData::rotateClockwise(int times)
{
    switch (times % 4)
    {
        case 3: {
            RotateCounterclockwise();
            break;
        }
        case 2: {
            RotateClockwise();
            RotateClockwise();
            break;
        }
        case 1: {
            RotateClockwise();
            break;
        }
    }

    return *this;
}

TileData::TileData(const std::vector<std::pair<TileObject, ObjectLocation>>& objects)
    : grid5x5 {
              {nullptr,nullptr,nullptr,nullptr,nullptr},
              {nullptr,nullptr,nullptr,nullptr,nullptr},
              {nullptr,nullptr,nullptr,nullptr,nullptr},
              {nullptr,nullptr,nullptr,nullptr,nullptr},
              {nullptr,nullptr,nullptr,nullptr,nullptr}
          }
{
    for (auto& tileObject: objects)
    {
        tileObjects.push_back(tileObject.first);

        for (auto& location: tileObject.second)
        {
            grid5x5[location.first][location.second] = tileObject.first.objPtr;
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

TileObject::TileObject(std::shared_ptr<MapObjectData> _objPtr, TileData *_tile)
    : objPtr(_objPtr), tile(_tile)
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
        // update exits count
        mergeObjectShapes(connectorObject, otherConnectorObject);

        // merge ids
        connectorObject->mergeObject(otherConnectorObject, updatedTiles);

        // check completion to score
        checkObjectCompletion(connectorObject);
        break;
    }
    case ObjectType::Field: {
        // merge ids
        connectorObject->mergeObject(otherConnectorObject, updatedTiles);
        break;
    }
    case ObjectType::Road: {
        // update exits count
        mergeObjectShapes(connectorObject, otherConnectorObject);

        // merge ids
        connectorObject->mergeObject(otherConnectorObject, updatedTiles);

        // check completion to score
        checkObjectCompletion(connectorObject);

        // merge side fields
        auto [sideConnector1, sideConnector2] = getSideConnectors(from);
        auto [otherSideConnector1, otherSideConnector2] = other.getSideConnectors(opposite(from));

        sideConnector1->mergeObject(otherSideConnector1, updatedTiles);
        sideConnector2->mergeObject(otherSideConnector2, updatedTiles);

        break;
    }
    case ObjectType::Abbey: {
        // update exits count of the adjacent object
        mergeObjectShapes(connectorObject, otherConnectorObject);

        // check completion of the adjacent object to score it
        checkObjectCompletion(connectorObject);
        break;
    }
    default:
        qDebug() << "Error: cannot connect" << ObjectTypeStrings[static_cast<int>(connectorObject->type)];
    }
}
