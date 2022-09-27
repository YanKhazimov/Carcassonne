#include "DataTypes.h"

Direction opposite(Direction direction)
{
    return static_cast<Direction>(Direction::Last - direction);
}

QVariantList playerColors = {
    QColor(255, 0, 0),
    QColor(0, 0, 255),
    QColor(0, 0, 0),
    QColor(200, 200, 0),
    "darkgreen",
    "pink"
};
