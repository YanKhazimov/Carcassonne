#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QUrl>
#include "TileData.h"

class Tile : public QObject, public TileData
{
    Q_OBJECT

    Q_PROPERTY(TileObject* Abbey READ abbeyObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* Monastery READ monasteryObject NOTIFY layoutChanged)

    Q_PROPERTY(bool HasRoadBlock READ hasRoadBlock NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* FieldWhole READ fieldWholeObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* FieldNorth READ fieldHalfNorthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldEast READ fieldHalfEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldSouth READ fieldHalfSouthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldWest READ fieldHalfWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* FieldNorthEast READ fieldNorthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldSouthEast READ fieldSouthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldSouthWest READ fieldSouthWestObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldNorthWest READ fieldNorthWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* FieldArc3cNorthEast READ fieldArc3cNorthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldArc3cNorthWest READ fieldArc3cNorthWestObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldArc3cSouthEast READ fieldArc3cSouthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldArc3cSouthWest READ fieldArc3cSouthWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* FieldArcNorth READ fieldArc2cNorthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldArcEast READ fieldArc2cEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldArcSouth READ fieldArc2cSouthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldArcWest READ fieldArc2cWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* Field3qNoNorthEast READ field3qNoNorthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Field3qNoNorthWest READ field3qNoNorthWestObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Field3qNoSouthEast READ field3qNoSouthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Field3qNoSouthWest READ field3qNoSouthWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* FieldDiagonalNWSE READ fieldDiagonalNWSEObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldDiagonalNESW READ fieldDiagonalNESWObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* FieldLTriangleNorthEast READ fieldLTriangleNorthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldLTriangleNorthWest READ fieldLTriangleNorthWestObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldLTriangleSouthEast READ fieldLTriangleSouthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldLTriangleSouthWest READ fieldLTriangleSouthWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* FieldJTriangleNorthEast READ fieldJTriangleNorthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldJTriangleNorthWest READ fieldJTriangleNorthWestObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldJTriangleSouthEast READ fieldJTriangleSouthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldJTriangleSouthWest READ fieldJTriangleSouthWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* FieldLTrapezoidNorthEast READ fieldLTrapezoidNorthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldLTrapezoidNorthWest READ fieldLTrapezoidNorthWestObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldLTrapezoidSouthEast READ fieldLTrapezoidSouthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldLTrapezoidSouthWest READ fieldLTrapezoidSouthWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* FieldJTrapezoidNorthEast READ fieldJTrapezoidNorthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldJTrapezoidNorthWest READ fieldJTrapezoidNorthWestObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldJTrapezoidSouthEast READ fieldJTrapezoidSouthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldJTrapezoidSouthWest READ fieldJTrapezoidSouthWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* FieldHalfQuarterNEE READ fieldNEEObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldHalfQuarterSEE READ fieldSEEObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldHalfQuarterSSE READ fieldSSEObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldHalfQuarterSSW READ fieldSSWObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldHalfQuarterSWW READ fieldSWWObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldHalfQuarterNWW READ fieldNWWObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldHalfQuarterNNW READ fieldNNWObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* FieldHalfQuarterNNE READ fieldNNEObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* RoadLongNorth READ roadLongNorthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* RoadLongEast READ roadLongEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* RoadLongSouth READ roadLongSouthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* RoadLongWest READ roadLongWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* RoadNorth READ roadNorthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* RoadEastObject READ roadEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* RoadSouthObject READ roadSouthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* RoadWestObject READ roadWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* RoadNorthSouth READ roadNorthSouthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* RoadEastWest READ roadEastWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* RoadDownThroughTownNorthSouth READ roadDownThroughTownNorthSouthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* RoadDownThroughTownEastWest READ roadDownThroughTownEastWestObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* RoadDownThroughTownSouthNorth READ roadDownThroughTownSouthNorthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* RoadDownThroughTownWestEast READ roadDownThroughTownWestEastObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* T_NorthWestSouthRoad READ T_NorthWestSouthRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* T_WestSouthEastRoad READ T_WestSouthEastRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* T_SouthEastNorthRoad READ T_SouthEastNorthRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* T_EastNorthWestRoad READ T_EastNorthWestRoadObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* C_ToTown_NorthEastRoad READ C_ToTownNorthEastRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* C_ToTown_NorthWestRoad READ C_ToTownNorthWestRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* C_ToTown_SouthEastRoad READ C_ToTownSouthEastRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* C_ToTown_SouthWestRoad READ C_ToTownSouthWestRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* C_ToTown_EastNorthRoad READ C_ToTownEastNorthRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* C_ToTown_WestNorthRoad READ C_ToTownWestNorthRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* C_ToTown_EastSouthRoad READ C_ToTownEastSouthRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* C_ToTown_WestSouthRoad READ C_ToTownWestSouthRoadObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* C_NorthEastRoad READ C_NorthEastRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* C_NorthWestRoad READ C_NorthWestRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* C_SouthEastRoad READ C_SouthEastRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* C_SouthWestRoad READ C_SouthWestRoadObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* L_NorthEastRoad READ L_NorthEastRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* L_NorthWestRoad READ L_NorthWestRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* L_SouthEastRoad READ L_SouthEastRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* L_SouthWestRoad READ L_SouthWestRoadObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* J_NorthWestRoad READ J_NorthWestRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* J_NorthEastRoad READ J_NorthEastRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* J_SouthWestRoad READ J_SouthWestRoadObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* J_SouthEastRoad READ J_SouthEastRoadObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* Town1eArcNorth READ town1eArcNorthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town1eArcEast READ town1eArcEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town1eArcSouth READ town1eArcSouthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town1eArcWest READ town1eArcWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* Town1eBridgeNorth READ town1eBridgeNorthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town1eBridgeEast READ town1eBridgeEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town1eBridgeSouth READ town1eBridgeSouthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town1eBridgeWest READ town1eBridgeWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* Town1e4cNorth READ town1e4cNorthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town1e4cEast READ town1e4cEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town1e4cSouth READ town1e4cSouthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town1e4cWest READ town1e4cWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* Town1e3cNorthToSouthEast READ town1e3cNorthToSouthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town1e3cEastToSouthWest READ town1e3cEastToSouthWestObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town1e3cSouthToNorthWest READ town1e3cSouthToNorthWestObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town1e3cWestToNorthEast READ town1e3cWestToNorthEastObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* Town2eNorthSouth READ town2eNorthSouthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town2eEastWest READ town2eEastWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* Town2e2cNorthEast READ town2e2cNorthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town2e2cNorthWest READ town2e2cNorthWestObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town2e2cSouthEast READ town2e2cSouthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town2e2cSouthWest READ town2e2cSouthWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* Town2e3cNorthEast READ town2e3cNorthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town2e3cNorthWest READ town2e3cNorthWestObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town2e3cSouthEast READ town2e3cSouthEastObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town2e3cSouthWest READ town2e3cSouthWestObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* Town3e4cNorthEastWest READ town3e4cNorthEastWestObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town3e4cEastNorthSouth READ town3e4cEastNorthSouthObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town3e4cSouthEastWest READ town3e4cSouthEastWestObject NOTIFY layoutChanged)
    Q_PROPERTY(TileObject* Town3e4cWestNorthSouth READ town3e4cWestNorthSouthObject NOTIFY layoutChanged)

    Q_PROPERTY(TileObject* TownWhole READ townWholeObject NOTIFY layoutChanged)


    Q_PROPERTY(QUrl Picture MEMBER imageUrl CONSTANT)
    Q_PROPERTY(int ImageRotation READ getImageRotation WRITE setImageRotation NOTIFY imageRotationChanged)
    Q_PROPERTY(int X MEMBER x NOTIFY indexChanged)
    Q_PROPERTY(int Y MEMBER y NOTIFY indexChanged)
    Q_PROPERTY(bool IsFixed READ fixed WRITE setFixed NOTIFY isFixedChanged)
    Q_PROPERTY(bool IsPlaced READ placed WRITE setPlaced NOTIFY isPlacedChanged)

    Q_PROPERTY(QList<int> BonusTypes MEMBER bonusTypes NOTIFY tileBonusesChanged)

    const QUrl imageUrl;
    int imageRotation;
    int x, y;
    bool isFixed;
    bool isPlaced;
    QList<int> bonusTypes;

    int getImageRotation() const;
    void setImageRotation(int rotation);
    void setPlaced(bool placed);
    void setPosition(int x, int y);

    void checkObjectCompletion(std::shared_ptr<TileObject> object) override;

    TileObject* abbeyObject() const;

    TileObject* monasteryObject() const;

    // bool hasRoadBlock() const;

    TileObject* fieldWholeObject() const;

    TileObject* fieldHalfNorthObject() const;
    TileObject* fieldHalfEastObject() const;
    TileObject* fieldHalfSouthObject() const;
    TileObject* fieldHalfWestObject() const;

    TileObject* fieldNorthEastObject() const;
    TileObject* fieldSouthEastObject() const;
    TileObject* fieldSouthWestObject() const;
    TileObject* fieldNorthWestObject() const;

    TileObject* fieldArc2cNorthObject() const;
    TileObject* fieldArc2cEastObject() const;
    TileObject* fieldArc2cSouthObject() const;
    TileObject* fieldArc2cWestObject() const;

    TileObject* fieldArc3cNorthEastObject() const;
    TileObject* fieldArc3cSouthEastObject() const;
    TileObject* fieldArc3cSouthWestObject() const;
    TileObject* fieldArc3cNorthWestObject() const;

    TileObject* field3qNoNorthEastObject() const;
    TileObject* field3qNoNorthWestObject() const;
    TileObject* field3qNoSouthEastObject() const;
    TileObject* field3qNoSouthWestObject() const;

    TileObject* fieldDiagonalNWSEObject() const;
    TileObject* fieldDiagonalNESWObject() const;

    TileObject* fieldLTriangleNorthEastObject() const;
    TileObject* fieldLTriangleNorthWestObject() const;
    TileObject* fieldLTriangleSouthEastObject() const;
    TileObject* fieldLTriangleSouthWestObject() const;

    TileObject* fieldJTriangleNorthEastObject() const;
    TileObject* fieldJTriangleNorthWestObject() const;
    TileObject* fieldJTriangleSouthEastObject() const;
    TileObject* fieldJTriangleSouthWestObject() const;

    TileObject* fieldLTrapezoidNorthEastObject() const;
    TileObject* fieldLTrapezoidNorthWestObject() const;
    TileObject* fieldLTrapezoidSouthEastObject() const;
    TileObject* fieldLTrapezoidSouthWestObject() const;

    TileObject* fieldJTrapezoidNorthEastObject() const;
    TileObject* fieldJTrapezoidNorthWestObject() const;
    TileObject* fieldJTrapezoidSouthEastObject() const;
    TileObject* fieldJTrapezoidSouthWestObject() const;

    TileObject* fieldNEEObject() const;
    TileObject* fieldSEEObject() const;
    TileObject* fieldSSEObject() const;
    TileObject* fieldSSWObject() const;
    TileObject* fieldSWWObject() const;
    TileObject* fieldNWWObject() const;
    TileObject* fieldNNWObject() const;
    TileObject* fieldNNEObject() const;

    TileObject* roadNorthObject() const;
    TileObject* roadEastObject() const;
    TileObject* roadSouthObject() const;
    TileObject* roadWestObject() const;

    TileObject* roadLongNorthObject() const;
    TileObject* roadLongEastObject() const;
    TileObject* roadLongSouthObject() const;
    TileObject* roadLongWestObject() const;

    TileObject* C_ToTownNorthEastRoadObject() const;
    TileObject* C_ToTownNorthWestRoadObject() const;
    TileObject* C_ToTownSouthEastRoadObject() const;
    TileObject* C_ToTownSouthWestRoadObject() const;
    TileObject* C_ToTownEastNorthRoadObject() const;
    TileObject* C_ToTownEastSouthRoadObject() const;
    TileObject* C_ToTownWestNorthRoadObject() const;
    TileObject* C_ToTownWestSouthRoadObject() const;

    TileObject* roadNorthSouthObject() const;
    TileObject* roadEastWestObject() const;

    TileObject* roadDownThroughTownNorthSouthObject() const;
    TileObject* roadDownThroughTownEastWestObject() const;
    TileObject* roadDownThroughTownSouthNorthObject() const;
    TileObject* roadDownThroughTownWestEastObject() const;

    TileObject* T_NorthWestSouthRoadObject() const;
    TileObject* T_WestSouthEastRoadObject() const;
    TileObject* T_SouthEastNorthRoadObject() const;
    TileObject* T_EastNorthWestRoadObject() const;

    TileObject* C_NorthEastRoadObject() const;
    TileObject* C_NorthWestRoadObject() const;
    TileObject* C_SouthEastRoadObject() const;
    TileObject* C_SouthWestRoadObject() const;

    TileObject* L_NorthEastRoadObject() const;
    TileObject* L_NorthWestRoadObject() const;
    TileObject* L_SouthEastRoadObject() const;
    TileObject* L_SouthWestRoadObject() const;

    TileObject* J_NorthWestRoadObject() const;
    TileObject* J_NorthEastRoadObject() const;
    TileObject* J_SouthWestRoadObject() const;
    TileObject* J_SouthEastRoadObject() const;

    TileObject* town1eArcNorthObject() const;
    TileObject* town1eArcEastObject() const;
    TileObject* town1eArcSouthObject() const;
    TileObject* town1eArcWestObject() const;

    TileObject* town1eBridgeNorthObject() const;
    TileObject* town1eBridgeEastObject() const;
    TileObject* town1eBridgeSouthObject() const;
    TileObject* town1eBridgeWestObject() const;

    TileObject* town1e4cNorthObject() const;
    TileObject* town1e4cEastObject() const;
    TileObject* town1e4cSouthObject() const;
    TileObject* town1e4cWestObject() const;

    TileObject* town1e3cNorthToSouthEastObject() const;
    TileObject* town1e3cEastToSouthWestObject() const;
    TileObject* town1e3cSouthToNorthWestObject() const;
    TileObject* town1e3cWestToNorthEastObject() const;

    TileObject* town2eNorthSouthObject() const;
    TileObject* town2eEastWestObject() const;

    TileObject* town2e2cNorthEastObject() const;
    TileObject* town2e2cNorthWestObject() const;
    TileObject* town2e2cSouthEastObject() const;
    TileObject* town2e2cSouthWestObject() const;

    TileObject* town2e3cNorthEastObject() const;
    TileObject* town2e3cNorthWestObject() const;
    TileObject* town2e3cSouthEastObject() const;
    TileObject* town2e3cSouthWestObject() const;

    TileObject* town3e4cNorthEastWestObject() const;
    TileObject* town3e4cEastNorthSouthObject() const;
    TileObject* town3e4cSouthEastWestObject() const;
    TileObject* town3e4cWestNorthSouthObject() const;

    TileObject* townWholeObject() const;

public:
    explicit Tile(const std::vector<std::pair<std::shared_ptr<TileObject>, TileData::ObjectLocation>>& objects, const QUrl& imageUrl, int imageRotation, QObject *parent = nullptr);
    Tile(Tile&& other) noexcept;
    Q_INVOKABLE void rotateClockwise();
    Q_INVOKABLE void rotateCounterclockwise();
    int getX() const;
    int getY() const;
    bool fixed() const;
    void setFixed(bool fixed);
    bool placed() const;
    Q_INVOKABLE void displace();
    Q_INVOKABLE void place(int x, int y);
    std::tuple<int, int, int> resources() const;

signals:
    void layoutChanged();
    void indexChanged();
    void isFixedChanged();
    void isPlacedChanged();
    void objectIdsChanged();
    void tileBonusesChanged();
    void objectCompleted(unsigned objectId);
    void meepleReset();
    void imageRotationChanged();

private slots:
    void updateBonuses();
};
Q_DECLARE_METATYPE(Tile*)

#endif // TILE_H
