#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QUrl>
#include "TileData.h"

class Tile : public QObject, public TileData
{
    Q_OBJECT

    Q_PROPERTY(bool Abbey READ hasAbbey NOTIFY layoutChanged)
    Q_PROPERTY(int AbbeyId READ abbeyId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool Monastery READ hasMonastery NOTIFY layoutChanged)
    Q_PROPERTY(int MonasteryId READ monasteryId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool RoadBlock READ hasRoadBlock NOTIFY layoutChanged)

    Q_PROPERTY(bool FieldWhole READ hasFieldWhole NOTIFY layoutChanged)
    Q_PROPERTY(int FieldWholeId READ fieldWholeId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool FieldNorth READ hasFieldHalfNorth NOTIFY layoutChanged)
    Q_PROPERTY(int FieldNorthId READ fieldHalfNorthId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldEast READ hasFieldHalfEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldEastId READ fieldHalfEastId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldSouth READ hasFieldHalfSouth NOTIFY layoutChanged)
    Q_PROPERTY(int FieldSouthId READ fieldHalfSouthId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldWest READ hasFieldHalfWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldWestId READ fieldHalfWestId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool FieldNorthEast READ hasFieldNorthEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldNorthEastId READ id_NE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldSouthEast READ hasFieldSouthEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldSouthEastId READ id_SE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldSouthWest READ hasFieldSouthWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldSouthWestId READ id_SW NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldNorthWest READ hasFieldNorthWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldNorthWestId READ id_NW NOTIFY objectIdsChanged)

    Q_PROPERTY(bool FieldArc3cNorthEast READ hasFieldArc3cNorthEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldArc3cNorthEastId READ fieldArc3cNorthEastId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldArc3cNorthWest READ hasFieldArc3cNorthWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldArc3cNorthWestId READ fieldArc3cNorthWestId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldArc3cSouthEast READ hasFieldArc3cSouthEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldArc3cSouthEastId READ fieldArc3cSouthEastId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldArc3cSouthWest READ hasFieldArc3cSouthWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldArc3cSouthWestId READ fieldArc3cSouthWestId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool FieldArcNorth READ hasFieldArc2cNorth NOTIFY layoutChanged)
    Q_PROPERTY(int FieldArcNorthId READ id_N NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldArcEast READ hasFieldArc2cEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldArcEastId READ id_E NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldArcSouth READ hasFieldArc2cSouth NOTIFY layoutChanged)
    Q_PROPERTY(int FieldArcSouthId READ id_S NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldArcWest READ hasFieldArc2cWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldArcWestId READ id_W NOTIFY objectIdsChanged)

    Q_PROPERTY(bool Field3qNoNorthEast READ hasField3qNoNorthEast NOTIFY layoutChanged)
    Q_PROPERTY(int Field3qNoNorthEastId READ field3qNoNorthEastId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Field3qNoNorthWest READ hasField3qNoNorthWest NOTIFY layoutChanged)
    Q_PROPERTY(int Field3qNoNorthWestId READ field3qNoNorthWestId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Field3qNoSouthEast READ hasField3qNoSouthEast NOTIFY layoutChanged)
    Q_PROPERTY(int Field3qNoSouthEastId READ field3qNoSouthEastId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Field3qNoSouthWest READ hasField3qNoSouthWest NOTIFY layoutChanged)
    Q_PROPERTY(int Field3qNoSouthWestId READ field3qNoSouthWestId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool FieldDiagonalNWSE READ hasFieldDiagonalNWSE NOTIFY layoutChanged)
    Q_PROPERTY(int FieldDiagonalNWSEId READ fieldDiagonalNWSEId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldDiagonalNESW READ hasFieldDiagonalNESW NOTIFY layoutChanged)
    Q_PROPERTY(int FieldDiagonalNESWId READ fieldDiagonalNESWId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool FieldLTriangleNorthEast READ hasFieldLTriangleNorthEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldLTriangleNorthEastId READ id_NE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldLTriangleNorthWest READ hasFieldLTriangleNorthWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldLTriangleNorthWestId READ id_NW NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldLTriangleSouthEast READ hasFieldLTriangleSouthEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldLTriangleSouthEastId READ id_SE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldLTriangleSouthWest READ hasFieldLTriangleSouthWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldLTriangleSouthWestId READ id_SW NOTIFY objectIdsChanged)

    Q_PROPERTY(bool FieldJTriangleNorthEast READ hasFieldJTriangleNorthEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldJTriangleNorthEastId READ id_NE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldJTriangleNorthWest READ hasFieldJTriangleNorthWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldJTriangleNorthWestId READ id_NW NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldJTriangleSouthEast READ hasFieldJTriangleSouthEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldJTriangleSouthEastId READ id_SE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldJTriangleSouthWest READ hasFieldJTriangleSouthWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldJTriangleSouthWestId READ id_SW NOTIFY objectIdsChanged)

    Q_PROPERTY(bool FieldLTrapezoidNorthEast READ hasFieldLTrapezoidNorthEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldLTrapezoidNorthEastId READ id_NE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldLTrapezoidNorthWest READ hasFieldLTrapezoidNorthWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldLTrapezoidNorthWestId READ id_NW NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldLTrapezoidSouthEast READ hasFieldLTrapezoidSouthEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldLTrapezoidSouthEastId READ id_SE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldLTrapezoidSouthWest READ hasFieldLTrapezoidSouthWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldLTrapezoidSouthWestId READ id_SW NOTIFY objectIdsChanged)

    Q_PROPERTY(bool FieldJTrapezoidNorthEast READ hasFieldJTrapezoidNorthEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldJTrapezoidNorthEastId READ id_NE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldJTrapezoidNorthWest READ hasFieldJTrapezoidNorthWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldJTrapezoidNorthWestId READ id_NW NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldJTrapezoidSouthEast READ hasFieldJTrapezoidSouthEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldJTrapezoidSouthEastId READ id_SE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldJTrapezoidSouthWest READ hasFieldJTrapezoidSouthWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldJTrapezoidSouthWestId READ id_SW NOTIFY objectIdsChanged)

    Q_PROPERTY(bool FieldHalfQuarterNEE READ hasFieldHalfQuarterNEE NOTIFY layoutChanged)
    Q_PROPERTY(int FieldHalfQuarterNEEId READ id_NEE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldHalfQuarterSEE READ hasFieldHalfQuarterSEE NOTIFY layoutChanged)
    Q_PROPERTY(int FieldHalfQuarterSEEId READ id_SEE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldHalfQuarterSSE READ hasFieldHalfQuarterSSE NOTIFY layoutChanged)
    Q_PROPERTY(int FieldHalfQuarterSSEId READ id_SSE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldHalfQuarterSSW READ hasFieldHalfQuarterSSW NOTIFY layoutChanged)
    Q_PROPERTY(int FieldHalfQuarterSSWId READ id_SSW NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldHalfQuarterSWW READ hasFieldHalfQuarterSWW NOTIFY layoutChanged)
    Q_PROPERTY(int FieldHalfQuarterSWWId READ id_SWW NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldHalfQuarterNWW READ hasFieldHalfQuarterNWW NOTIFY layoutChanged)
    Q_PROPERTY(int FieldHalfQuarterNWWId READ id_NWW NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldHalfQuarterNNW READ hasFieldHalfQuarterNNW NOTIFY layoutChanged)
    Q_PROPERTY(int FieldHalfQuarterNNWId READ id_NNW NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldHalfQuarterNNE READ hasFieldHalfQuarterNNE NOTIFY layoutChanged)
    Q_PROPERTY(int FieldHalfQuarterNNEId READ id_NNE NOTIFY objectIdsChanged)

    Q_PROPERTY(bool RoadLongNorth READ hasRoadLongNorth NOTIFY layoutChanged)
    Q_PROPERTY(int RoadLongNorthId READ id_N NOTIFY objectIdsChanged)
    Q_PROPERTY(bool RoadLongEast READ hasRoadLongEast NOTIFY layoutChanged)
    Q_PROPERTY(int RoadLongEastId READ id_E NOTIFY objectIdsChanged)
    Q_PROPERTY(bool RoadLongSouth READ hasRoadLongSouth NOTIFY layoutChanged)
    Q_PROPERTY(int RoadLongSouthId READ id_S NOTIFY objectIdsChanged)
    Q_PROPERTY(bool RoadLongWest READ hasRoadLongWest NOTIFY layoutChanged)
    Q_PROPERTY(int RoadLongWestId READ id_W NOTIFY objectIdsChanged)

    Q_PROPERTY(bool RoadNorth READ hasRoadNorth NOTIFY layoutChanged)
    Q_PROPERTY(int RoadNorthId READ id_N NOTIFY objectIdsChanged)
    Q_PROPERTY(bool RoadEast READ hasRoadEast NOTIFY layoutChanged)
    Q_PROPERTY(int RoadEastId READ id_E NOTIFY objectIdsChanged)
    Q_PROPERTY(bool RoadSouth READ hasRoadSouth NOTIFY layoutChanged)
    Q_PROPERTY(int RoadSouthId READ id_S NOTIFY objectIdsChanged)
    Q_PROPERTY(bool RoadWest READ hasRoadWest NOTIFY layoutChanged)
    Q_PROPERTY(int RoadWestId READ id_W NOTIFY objectIdsChanged)

    Q_PROPERTY(bool RoadNorthSouth READ hasRoadNorthSouth NOTIFY layoutChanged)
    Q_PROPERTY(int RoadNorthSouthId READ roadNorthSouthId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool RoadEastWest READ hasRoadEastWest NOTIFY layoutChanged)
    Q_PROPERTY(int RoadEastWestId READ roadEastWestId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool RoadDownThroughTownNorthSouth READ hasRoadDownThroughTownNorthSouth NOTIFY layoutChanged)
    Q_PROPERTY(int RoadDownThroughTownNorthSouthId READ roadDownThroughTownNorthSouthId() NOTIFY objectIdsChanged)
    Q_PROPERTY(bool RoadDownThroughTownEastWest READ hasRoadDownThroughTownEastWest() NOTIFY layoutChanged)
    Q_PROPERTY(int RoadDownThroughTownEastWestId READ roadDownThroughTownEastWestId() NOTIFY objectIdsChanged)
    Q_PROPERTY(bool RoadDownThroughTownSouthNorth READ hasRoadDownThroughTownSouthNorth() NOTIFY layoutChanged)
    Q_PROPERTY(int RoadDownThroughTownSouthNorthId READ roadDownThroughTownSouthNorthId() NOTIFY objectIdsChanged)
    Q_PROPERTY(bool RoadDownThroughTownWestEast READ hasRoadDownThroughTownWestEast() NOTIFY layoutChanged)
    Q_PROPERTY(int RoadDownThroughTownWestEastId READ roadDownThroughTownWestEastId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool T_NorthWestSouthRoad READ hasT_NorthWestSouthRoad NOTIFY layoutChanged)
    Q_PROPERTY(int T_NorthWestSouthRoadId READ T_NorthWestSouthRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool T_WestSouthEastRoad READ hasT_WestSouthEastRoad NOTIFY layoutChanged)
    Q_PROPERTY(int T_WestSouthEastRoadId READ T_WestSouthEastRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool T_SouthEastNorthRoad READ hasT_SouthEastNorthRoad NOTIFY layoutChanged)
    Q_PROPERTY(int T_SouthEastNorthRoadId READ T_SouthEastNorthRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool T_EastNorthWestRoad READ hasT_EastNorthWestRoad NOTIFY layoutChanged)
    Q_PROPERTY(int T_EastNorthWestRoadId READ T_EastNorthWestRoadId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool C_ToTown_NorthEastRoad READ hasC_ToTown_NorthEastRoad NOTIFY layoutChanged)
    Q_PROPERTY(int C_ToTown_NorthEastRoadId READ id_N NOTIFY objectIdsChanged)
    Q_PROPERTY(bool C_ToTown_NorthWestRoad READ hasC_ToTown_NorthWestRoad NOTIFY layoutChanged)
    Q_PROPERTY(int C_ToTown_NorthWestRoadId READ id_N NOTIFY objectIdsChanged)
    Q_PROPERTY(bool C_ToTown_SouthEastRoad READ hasC_ToTown_SouthEastRoad NOTIFY layoutChanged)
    Q_PROPERTY(int C_ToTown_SouthEastRoadId READ id_S NOTIFY objectIdsChanged)
    Q_PROPERTY(bool C_ToTown_SouthWestRoad READ hasC_ToTown_SouthWestRoad NOTIFY layoutChanged)
    Q_PROPERTY(int C_ToTown_SouthWestRoadId READ id_S NOTIFY objectIdsChanged)
    Q_PROPERTY(bool C_ToTown_EastNorthRoad READ hasC_ToTown_EastNorthRoad NOTIFY layoutChanged)
    Q_PROPERTY(int C_ToTown_EastNorthRoadId READ id_E NOTIFY objectIdsChanged)
    Q_PROPERTY(bool C_ToTown_WestNorthRoad READ hasC_ToTown_WestNorthRoad NOTIFY layoutChanged)
    Q_PROPERTY(int C_ToTown_WestNorthRoadId READ id_W NOTIFY objectIdsChanged)
    Q_PROPERTY(bool C_ToTown_EastSouthRoad READ hasC_ToTown_EastSouthRoad NOTIFY layoutChanged)
    Q_PROPERTY(int C_ToTown_EastSouthRoadId READ id_E NOTIFY objectIdsChanged)
    Q_PROPERTY(bool C_ToTown_WestSouthRoad READ hasC_ToTown_WestSouthRoad NOTIFY layoutChanged)
    Q_PROPERTY(int C_ToTown_WestSouthRoadId READ id_W NOTIFY objectIdsChanged)

    Q_PROPERTY(bool C_NorthEastRoad READ hasC_NorthEastRoad NOTIFY layoutChanged)
    Q_PROPERTY(int C_NorthEastRoadId READ C_NorthEastRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool C_NorthWestRoad READ hasC_NorthWestRoad NOTIFY layoutChanged)
    Q_PROPERTY(int C_NorthWestRoadId READ C_NorthWestRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool C_SouthEastRoad READ hasC_SouthEastRoad NOTIFY layoutChanged)
    Q_PROPERTY(int C_SouthEastRoadId READ C_SouthEastRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool C_SouthWestRoad READ hasC_SouthWestRoad NOTIFY layoutChanged)
    Q_PROPERTY(int C_SouthWestRoadId READ C_SouthWestRoadId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool L_NorthEastRoad READ hasL_NorthEastRoad NOTIFY layoutChanged)
    Q_PROPERTY(int L_NorthEastRoadId READ L_NorthEastRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool L_NorthWestRoad READ hasL_NorthWestRoad NOTIFY layoutChanged)
    Q_PROPERTY(int L_NorthWestRoadId READ L_NorthWestRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool L_SouthEastRoad READ hasL_SouthEastRoad NOTIFY layoutChanged)
    Q_PROPERTY(int L_SouthEastRoadId READ L_SouthEastRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool L_SouthWestRoad READ hasL_SouthWestRoad NOTIFY layoutChanged)
    Q_PROPERTY(int L_SouthWestRoadId READ L_SouthWestRoadId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool J_NorthWestRoad READ hasJ_NorthWestRoad NOTIFY layoutChanged)
    Q_PROPERTY(int J_NorthWestRoadId READ J_NorthWestRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool J_NorthEastRoad READ hasJ_NorthEastRoad NOTIFY layoutChanged)
    Q_PROPERTY(int J_NorthEastRoadId READ J_NorthEastRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool J_SouthWestRoad READ hasJ_SouthWestRoad NOTIFY layoutChanged)
    Q_PROPERTY(int J_SouthWestRoadId READ J_SouthWestRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool J_SouthEastRoad READ hasJ_SouthEastRoad NOTIFY layoutChanged)
    Q_PROPERTY(int J_SouthEastRoadId READ J_SouthEastRoadId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool Town1eArcNorth READ hasTown1eArcNorth NOTIFY layoutChanged)
    Q_PROPERTY(int Town1eArcNorthId READ id_N NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1eArcEast READ hasTown1eArcEast NOTIFY layoutChanged)
    Q_PROPERTY(int Town1eArcEastId READ id_E NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1eArcSouth READ hasTown1eArcSouth NOTIFY layoutChanged)
    Q_PROPERTY(int Town1eArcSouthId READ id_S NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1eArcWest READ hasTown1eArcWest NOTIFY layoutChanged)
    Q_PROPERTY(int Town1eArcWestId READ id_W NOTIFY objectIdsChanged)

    Q_PROPERTY(bool Town1eBridgeNorth READ hasTown1eBridgeNorth NOTIFY layoutChanged)
    Q_PROPERTY(int Town1eBridgeNorthId READ id_N NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1eBridgeEast READ hasTown1eBridgeEast NOTIFY layoutChanged)
    Q_PROPERTY(int Town1eBridgeEastId READ id_E NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1eBridgeSouth READ hasTown1eBridgeSouth NOTIFY layoutChanged)
    Q_PROPERTY(int Town1eBridgeSouthId READ id_S NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1eBridgeWest READ hasTown1eBridgeWest NOTIFY layoutChanged)
    Q_PROPERTY(int Town1eBridgeWestId READ id_W NOTIFY objectIdsChanged)

    Q_PROPERTY(bool Town1e4cNorth READ hasTown1e4cNorth NOTIFY layoutChanged)
    Q_PROPERTY(int Town1e4cNorthId READ id_N NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1e4cEast READ hasTown1e4cEast NOTIFY layoutChanged)
    Q_PROPERTY(int Town1e4cEastId READ id_E NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1e4cSouth READ hasTown1e4cSouth NOTIFY layoutChanged)
    Q_PROPERTY(int Town1e4cSouthId READ id_S NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1e4cWest READ hasTown1e4cWest NOTIFY layoutChanged)
    Q_PROPERTY(int Town1e4cWestId READ id_W NOTIFY objectIdsChanged)

    Q_PROPERTY(bool Town1e3cNorthToSouthEast READ hasTown1e3cNorthToSouthEast NOTIFY layoutChanged)
    Q_PROPERTY(int Town1e3cNorthToSouthEastId READ id_N NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1e3cEastToSouthWest READ hasTown1e3cEastToSouthWest NOTIFY layoutChanged)
    Q_PROPERTY(int Town1e3cEastToSouthWestId READ id_E NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1e3cSouthToNorthWest READ hasTown1e3cSouthToNorthWest NOTIFY layoutChanged)
    Q_PROPERTY(int Town1e3cSouthToNorthWestId READ id_S NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1e3cWestToNorthEast READ hasTown1e3cWestToNorthEast NOTIFY layoutChanged)
    Q_PROPERTY(int Town1e3cWestToNorthEastId READ id_W NOTIFY objectIdsChanged)

    Q_PROPERTY(bool Town2eNorthSouth READ hasTown2eNorthSouth NOTIFY layoutChanged)
    Q_PROPERTY(int Town2eNorthSouthId READ town2eNorthSouthId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town2eEastWest READ hasTown2eEastWest NOTIFY layoutChanged)
    Q_PROPERTY(int Town2eEastWestId READ town2eEastWestId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool Town2e2cNorthEast READ hasTown2e2cNorthEast NOTIFY layoutChanged)
    Q_PROPERTY(int Town2e2cNorthEastId READ town2e2cNorthEastId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town2e2cNorthWest READ hasTown2e2cNorthWest NOTIFY layoutChanged)
    Q_PROPERTY(int Town2e2cNorthWestId READ town2e2cNorthWestId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town2e2cSouthEast READ hasTown2e2cSouthEast NOTIFY layoutChanged)
    Q_PROPERTY(int Town2e2cSouthEastId READ town2e2cSouthEastId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town2e2cSouthWest READ hasTown2e2cSouthWest NOTIFY layoutChanged)
    Q_PROPERTY(int Town2e2cSouthWestId READ town2e2cSouthWestId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool Town2e3cNorthEast READ hasTown2e3cNorthEast NOTIFY layoutChanged)
    Q_PROPERTY(int Town2e3cNorthEastId READ town2e3cNorthEastId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town2e3cNorthWest READ hasTown2e3cNorthWest NOTIFY layoutChanged)
    Q_PROPERTY(int Town2e3cNorthWestId READ town2e3cNorthWestId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town2e3cSouthEast READ hasTown2e3cSouthEast NOTIFY layoutChanged)
    Q_PROPERTY(int Town2e3cSouthEastId READ town2e3cSouthEastId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town2e3cSouthWest READ hasTown2e3cSouthWest NOTIFY layoutChanged)
    Q_PROPERTY(int Town2e3cSouthWestId READ town2e3cSouthWestId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool Town3e4cNorthEastWest READ hasTown3e4cNorthEastWest NOTIFY layoutChanged)
    Q_PROPERTY(int Town3e4cNorthEastWestId READ town3e4cNorthEastWestId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town3e4cEastNorthSouth READ hasTown3e4cEastNorthSouth NOTIFY layoutChanged)
    Q_PROPERTY(int Town3e4cEastNorthSouthId READ town3e4cEastNorthSouthId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town3e4cSouthEastWest READ hasTown3e4cSouthEastWest NOTIFY layoutChanged)
    Q_PROPERTY(int Town3e4cSouthEastWestId READ town3e4cSouthEastWestId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town3e4cWestNorthSouth READ hasTown3e4cWestNorthSouth NOTIFY layoutChanged)
    Q_PROPERTY(int Town3e4cWestNorthSouthId READ town3e4cWestNorthSouthId NOTIFY objectIdsChanged)

    Q_PROPERTY(bool TownWhole READ hasTownWhole NOTIFY layoutChanged)
    Q_PROPERTY(int TownWholeId READ townWholeId NOTIFY objectIdsChanged)


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

    void checkObjectCompletion(std::shared_ptr<MapObjectData> object) override;

public:
    explicit Tile(std::vector<TileObject> &&objects, QString imageName, int imageRotation, QObject *parent = nullptr);
    Tile(Tile&& other) noexcept;
    Q_INVOKABLE void rotateClockwise();
    Q_INVOKABLE void rotateCounterclockwise();
    QPoint position() const;
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
