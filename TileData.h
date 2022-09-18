#ifndef TILEDATA_H
#define TILEDATA_H
#include "DataTypes.h"
#include "MapObjectData.h"
#include <memory>
#include <vector>
#include <set>

class TileData;

struct TileObject {
    std::shared_ptr<MapObjectData> objPtr;
    std::vector<std::pair<int, int>> location;
    TileData* tile;

    TileObject(std::shared_ptr<MapObjectData> objPtr, std::vector<std::pair<int, int>> location, TileData* tile = nullptr);
    TileObject(const TileObject& other);
    TileObject(TileObject&& other);
};

class TileData {
    std::shared_ptr<MapObjectData> grid5x5[5][5];

    std::pair<std::shared_ptr<MapObjectData>, std::shared_ptr<MapObjectData>> getSideConnectors(Direction direction) const;
    std::shared_ptr<MapObjectData> getConnector(Direction direction);
    void mergeObjectShapes(std::shared_ptr<MapObjectData> absorbingObject, std::shared_ptr<MapObjectData> absorbedObject) const;

public:
    void RotateClockwise();
    void RotateCounterclockwise();
    bool CanConnect(const TileData& other, Direction from) const;
    void Connect(TileData& other, Direction from, std::set<Tile*>& updatedTiles);
    TileData copy() const;
    TileData& rotateClockwise(int times = 1);
    void print() const;
    void markCentralObjectCompleted();
    bool hasCentralScorableObject() const;
    void getAdjacentTowns(std::shared_ptr<MapObjectData>& object, std::set<std::shared_ptr<MapObjectData>> &towns) const;
    std::set<unsigned> getFieldObjectIds() const;

protected:
    std::vector<TileObject> tileObjects;
    TileData(std::vector<TileObject> &&objects);
    std::shared_ptr<const MapObjectData> checkConnector(Direction direction) const;
    virtual void checkObjectCompletion(std::shared_ptr<MapObjectData> object);

    const std::shared_ptr<MapObjectData> NW() const;
    const std::shared_ptr<MapObjectData> NNW() const;
    const std::shared_ptr<MapObjectData> N() const;
    const std::shared_ptr<MapObjectData> NNE() const;
    const std::shared_ptr<MapObjectData> NE() const;
    const std::shared_ptr<MapObjectData> NWW() const;
    const std::shared_ptr<MapObjectData> NEE() const;
    const std::shared_ptr<MapObjectData> W() const;
    const std::shared_ptr<MapObjectData> C() const;
    const std::shared_ptr<MapObjectData> E() const;
    const std::shared_ptr<MapObjectData> SWW() const;
    const std::shared_ptr<MapObjectData> SEE() const;
    const std::shared_ptr<MapObjectData> SW() const;
    const std::shared_ptr<MapObjectData> SSW() const;
    const std::shared_ptr<MapObjectData> S() const;
    const std::shared_ptr<MapObjectData> SSE() const;
    const std::shared_ptr<MapObjectData> SE() const;

    int id_NE() const;
    int id_SE() const;
    int id_SW() const;
    int id_NW() const;

    int id_N() const;
    int id_S() const;
    int id_E() const;
    int id_W() const;

    bool hasAbbey() const;
    int abbeyId() const;

    bool hasMonastery() const;
    int monasteryId() const;

    bool hasRoadBlock() const;

    bool hasFieldWhole() const;
    int fieldWholeId() const;

    bool hasFieldHalfNorth() const;
    int fieldHalfNorthId() const;
    bool hasFieldHalfEast() const;
    int fieldHalfEastId() const;
    bool hasFieldHalfSouth() const;
    int fieldHalfSouthId() const;
    bool hasFieldHalfWest() const;
    int fieldHalfWestId() const;

    bool hasFieldNorthEast() const;
    bool hasFieldSouthEast() const;
    bool hasFieldSouthWest() const;
    bool hasFieldNorthWest() const;

    bool hasFieldArc2cNorth() const;
    bool hasFieldArc2cEast() const;
    bool hasFieldArc2cSouth() const;
    bool hasFieldArc2cWest() const;

    bool hasFieldArc3cNorthEast() const;
    int fieldArc3cNorthEastId() const;
    bool hasFieldArc3cSouthEast() const;
    int fieldArc3cSouthEastId() const;
    bool hasFieldArc3cSouthWest() const;
    int fieldArc3cSouthWestId() const;
    bool hasFieldArc3cNorthWest() const;
    int fieldArc3cNorthWestId() const;

    bool hasField3qNoNorthEast() const;
    int field3qNoNorthEastId() const;
    bool hasField3qNoNorthWest() const;
    int field3qNoNorthWestId() const;
    bool hasField3qNoSouthEast() const;
    int field3qNoSouthEastId() const;
    bool hasField3qNoSouthWest() const;
    int field3qNoSouthWestId() const;

    bool hasFieldDiagonalNWSE() const;
    int fieldDiagonalNWSEId() const;
    bool hasFieldDiagonalNESW() const;
    int fieldDiagonalNESWId() const;

    bool hasFieldLTriangleNorthEast() const;
    bool hasFieldLTriangleNorthWest() const;
    bool hasFieldLTriangleSouthEast() const;
    bool hasFieldLTriangleSouthWest() const;

    bool hasFieldLTrapezoidNorthEast() const;
    bool hasFieldLTrapezoidNorthWest() const;
    bool hasFieldLTrapezoidSouthEast() const;
    bool hasFieldLTrapezoidSouthWest() const;

    bool hasRoadNorth() const;
    bool hasRoadEast() const;
    bool hasRoadSouth() const;
    bool hasRoadWest() const;

    bool hasC_ToTown_NorthEastRoad() const;
    bool hasC_ToTown_NorthWestRoad() const;
    bool hasC_ToTown_SouthEastRoad() const;
    bool hasC_ToTown_SouthWestRoad() const;
    bool hasC_ToTown_EastNorthRoad() const;
    bool hasC_ToTown_EastSouthRoad() const;
    bool hasC_ToTown_WestNorthRoad() const;
    bool hasC_ToTown_WestSouthRoad() const;

    bool hasRoadNorthSouth() const;
    int roadNorthSouthId() const;
    bool hasRoadEastWest() const;
    int roadEastWestId() const;

    bool hasRoadDownThroughTownNorthSouth() const;
    int roadDownThroughTownNorthSouthId() const;
    bool hasRoadDownThroughTownEastWest() const;
    int roadDownThroughTownEastWestId() const;
    bool hasRoadDownThroughTownSouthNorth() const;
    int roadDownThroughTownSouthNorthId() const;
    bool hasRoadDownThroughTownWestEast() const;
    int roadDownThroughTownWestEastId() const;

    bool hasT_NorthWestSouthRoad() const;
    int T_NorthWestSouthRoadId() const;
    bool hasT_WestSouthEastRoad() const;
    int T_WestSouthEastRoadId() const;
    bool hasT_SouthEastNorthRoad() const;
    int T_SouthEastNorthRoadId() const;
    bool hasT_EastNorthWestRoad() const;
    int T_EastNorthWestRoadId() const;

    bool hasC_NorthEastRoad() const;
    int C_NorthEastRoadId() const;
    bool hasC_NorthWestRoad() const;
    int C_NorthWestRoadId() const;
    bool hasC_SouthEastRoad() const;
    int C_SouthEastRoadId() const;
    bool hasC_SouthWestRoad() const;
    int C_SouthWestRoadId() const;

    bool hasL_NorthEastRoad() const;
    int L_NorthEastRoadId() const;
    bool hasL_NorthWestRoad() const;
    int L_NorthWestRoadId() const;
    bool hasL_SouthEastRoad() const;
    int L_SouthEastRoadId() const;
    bool hasL_SouthWestRoad() const;
    int L_SouthWestRoadId() const;

    bool hasAnyL_Road() const;

    bool hasTown1eArcNorth() const;
    bool hasTown1eArcEast() const;
    bool hasTown1eArcSouth() const;
    bool hasTown1eArcWest() const;

    bool hasTown1e4cNorth() const;
    bool hasTown1e4cEast() const;
    bool hasTown1e4cSouth() const;
    bool hasTown1e4cWest() const;

    bool hasTown2eNorthSouth() const;
    int town2eNorthSouthId() const;
    bool hasTown2eEastWest() const;
    int town2eEastWestId() const;

    bool hasTown2e2cNorthEast() const;
    int town2e2cNorthEastId() const;
    bool hasTown2e2cNorthWest() const;
    int town2e2cNorthWestId() const;
    bool hasTown2e2cSouthEast() const;
    int town2e2cSouthEastId() const;
    bool hasTown2e2cSouthWest() const;
    int town2e2cSouthWestId() const;

    bool hasTown2e3cNorthEast() const;
    int town2e3cNorthEastId() const;
    bool hasTown2e3cNorthWest() const;
    int town2e3cNorthWestId() const;
    bool hasTown2e3cSouthEast() const;
    int town2e3cSouthEastId() const;
    bool hasTown2e3cSouthWest() const;
    int town2e3cSouthWestId() const;

    bool hasTownWhole() const;
    int townWholeId() const;

public:
    const bool isAbbeyTile;
};

#endif // TILEDATA_H
