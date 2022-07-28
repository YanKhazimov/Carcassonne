#ifndef TILE_H
#define TILE_H

#include <QObject>
#include "TileData.h"
#include <QQmlEngine>

class Tile : public QObject, public TileData
{
    Q_OBJECT

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

    Q_PROPERTY(bool FieldLTrapezoidNorthEast READ hasFieldLTrapezoidNorthEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldLTrapezoidNorthEastId READ id_NE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldLTrapezoidNorthWest READ hasFieldLTrapezoidNorthWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldLTrapezoidNorthWestId READ id_NW NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldLTrapezoidSouthEast READ hasFieldLTrapezoidSouthEast NOTIFY layoutChanged)
    Q_PROPERTY(int FieldLTrapezoidSouthEastId READ id_SE NOTIFY objectIdsChanged)
    Q_PROPERTY(bool FieldLTrapezoidSouthWest READ hasFieldLTrapezoidSouthWest NOTIFY layoutChanged)
    Q_PROPERTY(int FieldLTrapezoidSouthWestId READ id_SW NOTIFY objectIdsChanged)

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

    Q_PROPERTY(bool T_NorthWestSouthRoad READ hasT_NorthWestSouthRoad NOTIFY layoutChanged)
    Q_PROPERTY(int T_NorthWestSouthRoadId READ T_NorthWestSouthRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool T_WestSouthEastRoad READ hasT_WestSouthEastRoad NOTIFY layoutChanged)
    Q_PROPERTY(int T_WestSouthEastRoadId READ T_WestSouthEastRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool T_SouthEastNorthRoad READ hasT_SouthEastNorthRoad NOTIFY layoutChanged)
    Q_PROPERTY(int T_SouthEastNorthRoadId READ T_SouthEastNorthRoadId NOTIFY objectIdsChanged)
    Q_PROPERTY(bool T_EastNorthWestRoad READ hasT_EastNorthWestRoad NOTIFY layoutChanged)
    Q_PROPERTY(int T_EastNorthWestRoadId READ T_EastNorthWestRoadId NOTIFY objectIdsChanged)

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

    Q_PROPERTY(bool Town1eArcNorth READ hasTown1eArcNorth NOTIFY layoutChanged)
    Q_PROPERTY(int Town1eArcNorthId READ id_N NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1eArcEast READ hasTown1eArcEast NOTIFY layoutChanged)
    Q_PROPERTY(int Town1eArcEastId READ id_E NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1eArcSouth READ hasTown1eArcSouth NOTIFY layoutChanged)
    Q_PROPERTY(int Town1eArcSouthId READ id_S NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1eArcWest READ hasTown1eArcWest NOTIFY layoutChanged)
    Q_PROPERTY(int Town1eArcWestId READ id_W NOTIFY objectIdsChanged)

    Q_PROPERTY(bool Town1e4cNorth READ hasTown1e4cNorth NOTIFY layoutChanged)
    Q_PROPERTY(int Town1e4cNorthId READ id_N NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1e4cEast READ hasTown1e4cEast NOTIFY layoutChanged)
    Q_PROPERTY(int Town1e4cEastId READ id_E NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1e4cSouth READ hasTown1e4cSouth NOTIFY layoutChanged)
    Q_PROPERTY(int Town1e4cSouthId READ id_S NOTIFY objectIdsChanged)
    Q_PROPERTY(bool Town1e4cWest READ hasTown1e4cWest NOTIFY layoutChanged)
    Q_PROPERTY(int Town1e4cWestId READ id_W NOTIFY objectIdsChanged)

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


    Q_PROPERTY(int X MEMBER x NOTIFY indexChanged)
    Q_PROPERTY(int Y MEMBER y NOTIFY indexChanged)
    Q_PROPERTY(bool IsFixed READ fixed WRITE setFixed NOTIFY isFixedChanged)
    Q_PROPERTY(bool IsPlaced READ placed WRITE setPlaced NOTIFY isPlacedChanged)

    int x, y;
    bool isFixed;
    bool isPlaced;

    void setPlaced(bool placed);
    void setPosition(int x, int y);

public:
    explicit Tile(const std::vector<TileObject> &objects, QObject *parent = nullptr);
    Tile(Tile&& other) noexcept;
    Q_INVOKABLE void rotateClockwise();
    Q_INVOKABLE void rotateCounterclockwise();
    QPoint position() const;
    bool fixed() const;
    void setFixed(bool fixed);
    bool placed() const;
    Q_INVOKABLE void displace();
    Q_INVOKABLE void place(int x, int y);

signals:
    void layoutChanged();
    void indexChanged();
    void isFixedChanged();
    void isPlacedChanged();
    void objectIdsChanged();
};
Q_DECLARE_METATYPE(Tile*)

#endif // TILE_H
