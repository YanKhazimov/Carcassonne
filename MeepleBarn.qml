import QtQuick 2.15
import EngineEnums 1.0

BaseMeeple {
    type: EngineEnums.MeepleBarn
    width: 2 * Constants.smallMeepleSize
    height: 2 * Constants.smallMeepleSize

    ColoredImage {
        source: "qrc:/img/barn.png"
        color: playerColor
    }
}
