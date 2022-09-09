#include "DataTypes.h"

Direction opposite(Direction direction)
{
    return static_cast<Direction>(Direction::Last - direction);
}

QColor playerColors[] = {
    "red", "blue", "black", "yellow", "green"
};
