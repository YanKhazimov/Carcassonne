import QtQuick 2.15
import QtQuick.Shapes 1.12
import "qrc:/"

Shape {
    id: root

    required property int currentId
    readonly property bool highlighted: engine.HighlightedObjectId === currentId
    readonly property int side: Constants.tileSize
    property bool mouseOn
    readonly property real town1eOffset: Constants.tileSize / 4
    readonly property real town1eRadius: (Constants.tileSize * Constants.tileSize) / (8 * town1eOffset) + town1eOffset / 2
    readonly property real halfRoadWidth: Constants.tileSize / 8 / 2
    readonly property real town2eOffset: Constants.tileSize * 35 / 100
    readonly property real town2eRadius: (Constants.tileSize * Constants.tileSize) / (8 * town2eOffset) + town2eOffset / 2

    Component.onCompleted: mouseOn = false

    width: side
    height: side
    containsMode: Shape.FillContains

    antialiasing: true
}
