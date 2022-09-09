import QtQuick 2.15
import EngineEnums 1.0

BaseMeeple {
    type: EngineEnums.MeepleBuilder
    width: Constants.smallMeepleSize
    height: 2 * Constants.smallMeepleSize

    ColoredImage {
        source: "qrc:/img/builder.png"
        color: playerColor
    }
}
