#include "DataTypes.h"

TileSide opposite(TileSide side)
{
    return static_cast<TileSide>(TileSide::Last - side);
}

QVariantList playerColors = {
    QColor(255, 0, 0),
    QColor(0, 0, 255),
    QColor(0, 0, 0),
    "darkgreen",
    "#800080",
    "#008080",
    "#808000"
};

QMap<QString, QMap<ObjectType, QString>> objectStrings = {
    { {"acc",
     {
      { ObjectType::None, "None" },
      { ObjectType::Town, "город" },
      { ObjectType::Road, "дорогу" },
      { ObjectType::Field, "поле" },
      { ObjectType::Monastery, "монастырь" },
      { ObjectType::Abbey, "аббатство" }
     }}
     }
};
