import QtQuick 2.15
import "schematic"
import com.app.abc 1.0

Item {
    id: root

    required property TileData tileData

    Field_Whole {
        currentId: tileData.FieldWholeId
        visible: tileData.FieldWhole
    }

    Field_Half_North {
        currentId: tileData.FieldNorthId
        visible: tileData.FieldNorth
    }

    Field_Half_East {
        currentId: tileData.FieldEastId
        visible: tileData.FieldEast
    }

    Field_Half_South {
        currentId: tileData.FieldSouthId
        visible: tileData.FieldSouth
    }

    Field_Half_West {
        currentId: tileData.FieldWestId
        visible: tileData.FieldWest
    }

    Field_Quarter_NorthEast {
        currentId: tileData.FieldNorthEastId
        visible: tileData.FieldNorthEast
    }

    Field_Quarter_NorthWest {
        currentId: tileData.FieldNorthWestId
        visible: tileData.FieldNorthWest
    }

    Field_Quarter_SouthEast {
        currentId: tileData.FieldSouthEastId
        visible: tileData.FieldSouthEast
    }

    Field_Quarter_SouthWest {
        currentId: tileData.FieldSouthWestId
        visible: tileData.FieldSouthWest
    }

    Field_Arc3c_NorthEast {
        currentId: tileData.FieldArc3cNorthEastId
        visible: tileData.FieldArc3cNorthEast
    }

    Field_Arc3c_NorthWest {
        currentId: tileData.FieldArc3cNorthWestId
        visible: tileData.FieldArc3cNorthWest
    }

    Field_Arc3c_SouthEast {
        currentId: tileData.FieldArc3cSouthEastId
        visible: tileData.FieldArc3cSouthEast
    }

    Field_Arc3c_SouthWest {
        currentId: tileData.FieldArc3cSouthWestId
        visible: tileData.FieldArc3cSouthWest
    }

    Field_Arc_North {
        currentId: tileData.FieldArcNorthId
        visible: tileData.FieldArcNorth
    }

    Field_Arc_East {
        currentId: tileData.FieldArcEastId
        visible: tileData.FieldArcEast
    }

    Field_Arc_South {
        currentId: tileData.FieldArcSouthId
        visible: tileData.FieldArcSouth
    }

    Field_Arc_West {
        currentId: tileData.FieldArcWestId
        visible: tileData.FieldArcWest
    }

    Field_3quarters_noNorthEast {
        currentId: tileData.Field3qNoNorthEastId
        visible: tileData.Field3qNoNorthEast
    }

    Field_3quarters_noSouthEast {
        currentId: tileData.Field3qNoSouthEastId
        visible: tileData.Field3qNoSouthEast
    }

    Field_3quarters_noSouthWest {
        currentId: tileData.Field3qNoSouthWestId
        visible: tileData.Field3qNoSouthWest
    }

    Field_3quarters_noNorthWest {
        currentId: tileData.Field3qNoNorthWestId
        visible: tileData.Field3qNoNorthWest
    }

    Field_Diagonal_NorthWest_SouthEast {
        currentId: tileData.FieldDiagonalNWSEId
        visible: tileData.FieldDiagonalNWSE
    }

    Field_Diagonal_NorthEast_SouthWest {
        currentId: tileData.FieldDiagonalNESWId
        visible: tileData.FieldDiagonalNESW
    }

    Field_LTriangle_NorthEast {
        currentId: tileData.FieldLTriangleNorthEastId
        visible: tileData.FieldLTriangleNorthEast
    }

    Field_LTriangle_NorthWest {
        currentId: tileData.FieldLTriangleNorthWestId
        visible: tileData.FieldLTriangleNorthWest
    }

    Field_LTriangle_SouthEast {
        currentId: tileData.FieldLTriangleSouthEastId
        visible: tileData.FieldLTriangleSouthEast
    }

    Field_LTriangle_SouthWest {
        currentId: tileData.FieldLTriangleSouthWestId
        visible: tileData.FieldLTriangleSouthWest
    }

    Field_LTrapezoid_NorthEast {
        currentId: tileData.FieldLTrapezoidNorthEastId
        visible: tileData.FieldLTrapezoidNorthEast
    }

    Field_LTrapezoid_NorthWest {
        currentId: tileData.FieldLTrapezoidNorthWestId
        visible: tileData.FieldLTrapezoidNorthWest
    }

    Field_LTrapezoid_SouthEast {
        currentId: tileData.FieldLTrapezoidSouthEastId
        visible: tileData.FieldLTrapezoidSouthEast
    }

    Field_LTrapezoid_SouthWest {
        currentId: tileData.FieldLTrapezoidSouthWestId
        visible: tileData.FieldLTrapezoidSouthWest
    }

    Road_North {
        visible: tileData.RoadNorth
        currentId: tileData.RoadNorthId
    }

    Road_East {
        visible: tileData.RoadEast
        currentId: tileData.RoadEastId
    }

    Road_South {
        visible: tileData.RoadSouth
        currentId: tileData.RoadSouthId
    }

    Road_West {
        visible: tileData.RoadWest
        currentId: tileData.RoadWestId
    }

    Road_NorthSouth {
        currentId: tileData.RoadNorthSouthId
        visible: tileData.RoadNorthSouth
        z: currentId
    }

    Road_EastWest {
        currentId: tileData.RoadEastWestId
        visible: tileData.RoadEastWest
        z: currentId
    }

    Road_T_NorthWestSouth {
        currentId: tileData.T_NorthWestSouthRoadId
        visible: tileData.T_NorthWestSouthRoad
    }

    Road_T_WestSouthEast {
        currentId: tileData.T_WestSouthEastRoadId
        visible: tileData.T_WestSouthEastRoad
    }

    Road_T_SouthEastNorth {
        currentId: tileData.T_SouthEastNorthRoadId
        visible: tileData.T_SouthEastNorthRoad
    }

    Road_T_EastNorthWest {
        currentId: tileData.T_EastNorthWestRoadId
        visible: tileData.T_EastNorthWestRoad
    }

    Road_C_NorthEast {
        currentId: tileData.C_NorthEastRoadId
        visible: tileData.C_NorthEastRoad
    }

    Road_C_NorthWest {
        currentId: tileData.C_NorthWestRoadId
        visible: tileData.C_NorthWestRoad
    }

    Road_C_SouthEast {
        currentId: tileData.C_SouthEastRoadId
        visible: tileData.C_SouthEastRoad
    }

    Road_C_SouthWest {
        currentId: tileData.C_SouthWestRoadId
        visible: tileData.C_SouthWestRoad
    }

    Road_L_NorthEast {
        currentId: tileData.L_NorthEastRoadId
        visible: tileData.L_NorthEastRoad
    }

    Road_L_NorthWest {
        currentId: tileData.L_NorthWestRoadId
        visible: tileData.L_NorthWestRoad
    }

    Road_L_SouthEast {
        currentId: tileData.L_SouthEastRoadId
        visible: tileData.L_SouthEastRoad
    }

    Road_L_SouthWest {
        currentId: tileData.L_SouthWestRoadId
        visible: tileData.L_SouthWestRoad
    }

    Town_1eArc_North {
        currentId: tileData.Town1eArcNorthId
        visible: tileData.Town1eArcNorth
    }

    Town_1eArc_East {
        currentId: tileData.Town1eArcEastId
        visible: tileData.Town1eArcEast
    }

    Town_1eArc_South {
        currentId: tileData.Town1eArcSouthId
        visible: tileData.Town1eArcSouth
    }

    Town_1eArc_West {
        currentId: tileData.Town1eArcWestId
        visible: tileData.Town1eArcWest
    }

    Town_1e4c_North {
        currentId: tileData.Town1e4cNorthId
        visible: tileData.Town1e4cNorth
    }

    Town_1e4c_East {
        currentId: tileData.Town1e4cEastId
        visible: tileData.Town1e4cEast
    }

    Town_1e4c_South {
        currentId: tileData.Town1e4cSouthId
        visible: tileData.Town1e4cSouth
    }

    Town_1e4c_West {
        currentId: tileData.Town1e4cWestId
        visible: tileData.Town1e4cWest
    }

    Town_2e_NorthSouth {
        currentId: tileData.Town2eNorthSouthId
        visible: tileData.Town2eNorthSouth
        z: currentId
    }

    Town_2e_EastWest {
        currentId: tileData.Town2eEastWestId
        visible: tileData.Town2eEastWest
        z: currentId
    }

    Town_2e2c_NorthEast {
        currentId: tileData.Town2e2cNorthEastId
        visible: tileData.Town2e2cNorthEast
    }

    Town_2e2c_NorthWest {
        currentId: tileData.Town2e2cNorthWestId
        visible: tileData.Town2e2cNorthWest
    }

    Town_2e2c_SouthEast {
        currentId: tileData.Town2e2cSouthEastId
        visible: tileData.Town2e2cSouthEast
    }

    Town_2e2c_SouthWest {
        currentId: tileData.Town2e2cSouthWestId
        visible: tileData.Town2e2cSouthWest
    }

    Town_2e3c_NorthEast {
        currentId: tileData.Town2e3cNorthEastId
        visible: tileData.Town2e3cNorthEast
    }

    Town_2e3c_NorthWest {
        currentId: tileData.Town2e3cNorthWestId
        visible: tileData.Town2e3cNorthWest
    }

    Town_2e3c_SouthEast {
        currentId: tileData.Town2e3cSouthEastId
        visible: tileData.Town2e3cSouthEast
    }

    Town_2e3c_SouthWest {
        currentId: tileData.Town2e3cSouthWestId
        visible: tileData.Town2e3cSouthWest
    }
}
