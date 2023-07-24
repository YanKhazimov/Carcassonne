import QtQuick 2.15
import EngineEnums 1.0

BaseMeeple {
    type: EngineEnums.MeepleBuilder
    imageWidth: Constants.smallMeepleSize
    imageHeight: 2 * Constants.smallMeepleSize
    imageSource: "qrc:/img/builder.png"
}
