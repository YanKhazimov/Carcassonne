#include "DataTypes.h"

TileSide opposite(TileSide side)
{
    return static_cast<TileSide>(TileSide::Last - side);
}

QVariantList playerColors = {
    QColor(255, 0, 0),
    QColor(0, 0, 255),
    QColor(0, 0, 0),
    QColor(200, 200, 0),
    "darkgreen",
    "pink"
};
