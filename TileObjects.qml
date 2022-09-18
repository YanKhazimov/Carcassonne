import QtQuick 2.15
import "schematic"
import com.carcassonne.cppTypes 1.0

Item {
    id: root

    property TileData tileData

    Field_Whole {
        tileData: root.tileData
    }

    Field_Half_North {
        tileData: root.tileData
    }

    Field_Half_East {
        tileData: root.tileData
    }

    Field_Half_South {
        tileData: root.tileData
    }

    Field_Half_West {
        tileData: root.tileData
    }

    Field_Quarter_NorthEast {
        tileData: root.tileData
    }

    Field_Quarter_NorthWest {
        tileData: root.tileData
    }

    Field_Quarter_SouthEast {
        tileData: root.tileData
    }

    Field_Quarter_SouthWest {
        tileData: root.tileData
    }

    Field_Arc3c_NorthEast {
        tileData: root.tileData
    }

    Field_Arc3c_NorthWest {
        tileData: root.tileData
    }

    Field_Arc3c_SouthEast {
        tileData: root.tileData
    }

    Field_Arc3c_SouthWest {
        tileData: root.tileData
    }

    Field_Arc_North {
        tileData: root.tileData
    }

    Field_Arc_East {
        tileData: root.tileData
    }

    Field_Arc_South {
        tileData: root.tileData
    }

    Field_Arc_West {
        tileData: root.tileData
    }

    Field_3quarters_noNorthEast {
        tileData: root.tileData
    }

    Field_3quarters_noSouthEast {
        tileData: root.tileData
    }

    Field_3quarters_noSouthWest {
        tileData: root.tileData
    }

    Field_3quarters_noNorthWest {
        tileData: root.tileData
    }

    Field_Diagonal_NorthWest_SouthEast {
        tileData: root.tileData
    }

    Field_Diagonal_NorthEast_SouthWest {
        tileData: root.tileData
    }

    Field_LTriangle_NorthEast {
        tileData: root.tileData
    }

    Field_LTriangle_NorthWest {
        tileData: root.tileData
    }

    Field_LTriangle_SouthEast {
        tileData: root.tileData
    }

    Field_LTriangle_SouthWest {
        tileData: root.tileData
    }

    Field_LTrapezoid_NorthEast {
        tileData: root.tileData
    }

    Field_LTrapezoid_NorthWest {
        tileData: root.tileData
    }

    Field_LTrapezoid_SouthEast {
        tileData: root.tileData
    }

    Field_LTrapezoid_SouthWest {
        tileData: root.tileData
    }

    Road_North {
        tileData: root.tileData
    }

    Road_East {
        tileData: root.tileData
    }

    Road_South {
        tileData: root.tileData
    }

    Road_West {
        tileData: root.tileData
    }

    Road_NorthSouth {
        tileData: root.tileData
        z: currentId
    }

    Road_EastWest {
        tileData: root.tileData
        z: currentId
    }

    Road_DownThroughTown_NorthSouth {
        tileData: root.tileData
        z: town_2e_EastWest.z + 1
    }

    Road_DownThroughTown_EastWest {
        tileData: root.tileData
        z: town_2e_NorthSouth.z + 1
    }

    Road_DownThroughTown_SouthNorth {
        tileData: root.tileData
        z: town_2e_EastWest.z + 1
    }

    Road_DownThroughTown_WestEast {
        tileData: root.tileData
        z: town_2e_NorthSouth.z + 1
    }

    Road_T_NorthWestSouth {
        tileData: root.tileData
    }

    Road_T_WestSouthEast {
        tileData: root.tileData
    }

    Road_T_SouthEastNorth {
        tileData: root.tileData
    }

    Road_T_EastNorthWest {
        tileData: root.tileData
    }

    Road_C_ToTown_NorthEast {
        tileData: root.tileData
    }

    Road_C_ToTown_NorthWest {
        tileData: root.tileData
    }

    Road_C_ToTown_SouthEast {
        tileData: root.tileData
    }

    Road_C_ToTown_SouthWest {
        tileData: root.tileData
    }

    Road_C_ToTown_EastNorth {
        tileData: root.tileData
    }

    Road_C_ToTown_WestNorth {
        tileData: root.tileData
    }

    Road_C_ToTown_EastSouth {
        tileData: root.tileData
    }

    Road_C_ToTown_WestSouth {
        tileData: root.tileData
    }

    Road_C_NorthEast {
        tileData: root.tileData
    }

    Road_C_NorthWest {
        tileData: root.tileData
    }

    Road_C_SouthEast {
        tileData: root.tileData
    }

    Road_C_SouthWest {
        tileData: root.tileData
    }

    Road_L_NorthEast {
        tileData: root.tileData
    }

    Road_L_NorthWest {
        tileData: root.tileData
    }

    Road_L_SouthEast {
        tileData: root.tileData
    }

    Road_L_SouthWest {
        tileData: root.tileData
    }

    Town_1eArc_North {
        tileData: root.tileData
    }

    Town_1eArc_East {
        tileData: root.tileData
    }

    Town_1eArc_South {
        tileData: root.tileData
    }

    Town_1eArc_West {
        tileData: root.tileData
    }

    Town_1e4c_North {
        tileData: root.tileData
    }

    Town_1e4c_East {
        tileData: root.tileData
    }

    Town_1e4c_South {
        tileData: root.tileData
    }

    Town_1e4c_West {
        tileData: root.tileData
    }

    Town_2e_NorthSouth {
        id: town_2e_NorthSouth
        tileData: root.tileData
        z: currentId
    }

    Town_2e_EastWest {
        id: town_2e_EastWest
        tileData: root.tileData
        z: currentId
    }

    Town_2e2c_NorthEast {
        tileData: root.tileData
    }

    Town_2e2c_NorthWest {
        tileData: root.tileData
    }

    Town_2e2c_SouthEast {
        tileData: root.tileData
    }

    Town_2e2c_SouthWest {
        tileData: root.tileData
    }

    Town_2e3c_NorthEast {
        tileData: root.tileData
    }

    Town_2e3c_NorthWest {
        tileData: root.tileData
    }

    Town_2e3c_SouthEast {
        tileData: root.tileData
    }

    Town_2e3c_SouthWest {
        tileData: root.tileData
    }

    Town_Whole {
        tileData: root.tileData
    }

    Abbey {
        tileData: root.tileData
    }

    Monastery {
        tileData: root.tileData
        z: currentId
    }

    RoadBlock {
        tileData: root.tileData
    }
}
