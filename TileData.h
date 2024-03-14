#ifndef TILEDATA_H
#define TILEDATA_H

#include "DataTypes.h"
#include "TileObject.h"
#include <memory>
#include <vector>
#include <set>
#include <QJsonArray>

class TileData {
    std::shared_ptr<TileObject> grid5x5[5][5];

    std::pair<std::shared_ptr<TileObject>, std::shared_ptr<TileObject>> getSideConnectors(TileSide direction) const;
    std::shared_ptr<TileObject> getConnector(TileSide direction);
    void mergeObjectShapes(std::shared_ptr<TileObject> absorbingObject, std::shared_ptr<TileObject> absorbedObject) const;

public:
    void RotateClockwise();
    void RotateCounterclockwise();
    bool CanConnect(const TileData& other, TileSide from) const;
    void Connect(TileData& newTile, TileSide side, std::set<Tile*>& updatedTiles);
    std::shared_ptr<const TileObject> checkConnector(TileSide direction) const;
    TileData copy() const;
    TileData& rotateClockwise(int times = 1);
    void print() const;
    void markCentralObjectCompleted();
    bool hasCentralScorableObject() const;
    void getAdjacentTowns(const std::shared_ptr<TileObject>& object, std::set<std::shared_ptr<TileObject>> &towns) const;
    std::set<unsigned> getFieldObjectIds() const;
    unsigned NEBarnCornerId() const;
    unsigned NWBarnCornerId() const;
    unsigned SEBarnCornerId() const;
    unsigned SWBarnCornerId() const;
    bool isAbbeyTile() const;
    QJsonArray serialize() const;

    using ObjectLocation = std::vector<std::pair<int, int>>;

protected:
    std::set<std::shared_ptr<TileObject>> tileObjects;
    TileData(const std::vector<std::pair<std::shared_ptr<TileObject>, ObjectLocation>>& objects);
    TileData(const std::vector<std::vector<int>>& objectIds);
    TileData(const QJsonArray &json);
    virtual void checkObjectCompletion(std::shared_ptr<TileObject> object);

    std::shared_ptr<TileObject> NW() const;
    std::shared_ptr<TileObject> NNW() const;
    std::shared_ptr<TileObject> N() const;
    std::shared_ptr<TileObject> NNE() const;
    std::shared_ptr<TileObject> NE() const;
    std::shared_ptr<TileObject> NWW() const;
    std::shared_ptr<TileObject> NEE() const;
    std::shared_ptr<TileObject> W() const;
    std::shared_ptr<TileObject> C() const;
    std::shared_ptr<TileObject> E() const;
    std::shared_ptr<TileObject> SWW() const;
    std::shared_ptr<TileObject> SEE() const;
    std::shared_ptr<TileObject> SW() const;
    std::shared_ptr<TileObject> SSW() const;
    std::shared_ptr<TileObject> S() const;
    std::shared_ptr<TileObject> SSE() const;
    std::shared_ptr<TileObject> SE() const;

    // int id_NE() const;
    // int id_SE() const;
    // int id_SW() const;
    // int id_NW() const;

    // int id_NEE() const;
    // int id_SEE() const;
    // int id_SSE() const;
    // int id_SSW() const;
    // int id_SWW() const;
    // int id_NWW() const;
    // int id_NNW() const;
    // int id_NNE() const;

    // int id_N() const;
    // int id_S() const;
    // int id_E() const;
    // int id_W() const;

    bool hasAbbey() const;

    bool hasMonastery() const;

    bool hasRoadBlock() const;

    bool hasFieldWhole() const;

    bool hasFieldHalfNorth() const;
    bool hasFieldHalfEast() const;
    bool hasFieldHalfSouth() const;
    bool hasFieldHalfWest() const;

    bool hasFieldNorthEast() const;
    bool hasFieldSouthEast() const;
    bool hasFieldSouthWest() const;
    bool hasFieldNorthWest() const;

    bool hasFieldArc2cNorth() const;
    bool hasFieldArc2cEast() const;
    bool hasFieldArc2cSouth() const;
    bool hasFieldArc2cWest() const;

    bool hasFieldArc3cNorthEast() const;
    bool hasFieldArc3cSouthEast() const;
    bool hasFieldArc3cSouthWest() const;
    bool hasFieldArc3cNorthWest() const;

    bool hasField3qNoNorthEast() const;
    bool hasField3qNoNorthWest() const;
    bool hasField3qNoSouthEast() const;
    bool hasField3qNoSouthWest() const;

    bool hasFieldDiagonalNWSE() const;
    bool hasFieldDiagonalNESW() const;

    bool hasFieldLTriangleNorthEast() const;
    bool hasFieldLTriangleNorthWest() const;
    bool hasFieldLTriangleSouthEast() const;
    bool hasFieldLTriangleSouthWest() const;

    bool hasFieldJTriangleNorthEast() const;
    bool hasFieldJTriangleNorthWest() const;
    bool hasFieldJTriangleSouthEast() const;
    bool hasFieldJTriangleSouthWest() const;

    bool hasFieldLTrapezoidNorthEast() const;
    bool hasFieldLTrapezoidNorthWest() const;
    bool hasFieldLTrapezoidSouthEast() const;
    bool hasFieldLTrapezoidSouthWest() const;

    bool hasFieldJTrapezoidNorthEast() const;
    bool hasFieldJTrapezoidNorthWest() const;
    bool hasFieldJTrapezoidSouthEast() const;
    bool hasFieldJTrapezoidSouthWest() const;

    bool hasFieldHalfQuarterNEE() const;
    bool hasFieldHalfQuarterSEE() const;
    bool hasFieldHalfQuarterSSE() const;
    bool hasFieldHalfQuarterSSW() const;
    bool hasFieldHalfQuarterSWW() const;
    bool hasFieldHalfQuarterNWW() const;
    bool hasFieldHalfQuarterNNW() const;
    bool hasFieldHalfQuarterNNE() const;

    bool hasRoadNorth() const;
    bool hasRoadEast() const;
    bool hasRoadSouth() const;
    bool hasRoadWest() const;

    bool hasRoadLongNorth() const;
    bool hasRoadLongEast() const;
    bool hasRoadLongSouth() const;
    bool hasRoadLongWest() const;

    bool hasC_ToTown_NorthEastRoad() const;
    bool hasC_ToTown_NorthWestRoad() const;
    bool hasC_ToTown_SouthEastRoad() const;
    bool hasC_ToTown_SouthWestRoad() const;
    bool hasC_ToTown_EastNorthRoad() const;
    bool hasC_ToTown_EastSouthRoad() const;
    bool hasC_ToTown_WestNorthRoad() const;
    bool hasC_ToTown_WestSouthRoad() const;

    bool hasRoadNorthSouth() const;
    bool hasRoadEastWest() const;

    bool hasRoadDownThroughTownNorthSouth() const;
    bool hasRoadDownThroughTownEastWest() const;
    bool hasRoadDownThroughTownSouthNorth() const;
    bool hasRoadDownThroughTownWestEast() const;

    bool hasT_NorthWestSouthRoad() const;
    bool hasT_WestSouthEastRoad() const;
    bool hasT_SouthEastNorthRoad() const;
    bool hasT_EastNorthWestRoad() const;

    bool hasC_NorthEastRoad() const;
    bool hasC_NorthWestRoad() const;
    bool hasC_SouthEastRoad() const;
    bool hasC_SouthWestRoad() const;

    bool hasL_NorthEastRoad() const;
    bool hasL_NorthWestRoad() const;
    bool hasL_SouthEastRoad() const;
    bool hasL_SouthWestRoad() const;

    bool hasAnyL_Road() const;

    bool hasJ_NorthWestRoad() const;
    bool hasJ_NorthEastRoad() const;
    bool hasJ_SouthWestRoad() const;
    bool hasJ_SouthEastRoad() const;

    bool hasAnyJ_Road() const;

    bool hasTown1eArcNorth() const;
    bool hasTown1eArcEast() const;
    bool hasTown1eArcSouth() const;
    bool hasTown1eArcWest() const;

    bool hasTown1eBridgeNorth() const;
    bool hasTown1eBridgeEast() const;
    bool hasTown1eBridgeSouth() const;
    bool hasTown1eBridgeWest() const;

    bool hasTown1e4cNorth() const;
    bool hasTown1e4cEast() const;
    bool hasTown1e4cSouth() const;
    bool hasTown1e4cWest() const;

    bool hasTown1e3cNorthToSouthEast() const;
    bool hasTown1e3cEastToSouthWest() const;
    bool hasTown1e3cSouthToNorthWest() const;
    bool hasTown1e3cWestToNorthEast() const;

    bool hasTown2eNorthSouth() const;
    bool hasTown2eEastWest() const;

    bool hasTown2e2cNorthEast() const;
    bool hasTown2e2cNorthWest() const;
    bool hasTown2e2cSouthEast() const;
    bool hasTown2e2cSouthWest() const;

    bool hasTown2e3cNorthEast() const;
    bool hasTown2e3cNorthWest() const;
    bool hasTown2e3cSouthEast() const;
    bool hasTown2e3cSouthWest() const;

    bool hasTown3e4cNorthEastWest() const;
    bool hasTown3e4cEastNorthSouth() const;
    bool hasTown3e4cSouthEastWest() const;
    bool hasTown3e4cWestNorthSouth() const;

    bool hasTownWhole() const;
};

#endif // TILEDATA_H
