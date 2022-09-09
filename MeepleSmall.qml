import QtQuick 2.15
import EngineEnums 1.0

BaseMeeple {
    type: EngineEnums.MeepleSmall
    width: Constants.smallMeepleSize
    height: Constants.smallMeepleSize

    ColoredImage {
        source: "qrc:/img/smallMeeple.png"
        color: playerColor
    }
}
