import QtQuick 2.15
import EngineEnums 1.0

BaseMeeple {
    type: EngineEnums.MeeplePig
    width: 2 * Constants.smallMeepleSize
    height: Constants.smallMeepleSize

    ColoredImage {
        source: "qrc:/img/pig.png"
        color: playerColor
    }
}
