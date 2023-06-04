import QtQuick 2.15
import QtQuick.Shapes 1.15
import com.carcassonne.cppTypes 1.0
import QmlPresenter 1.0
import "qrc:/"

Shape {
    id: root

    required property int currentId
    readonly property bool highlighted: engine.HighlightedObjectId === currentId
    readonly property int side: parent.width
    readonly property real town1eOffset: side / 5
    readonly property real town1eRadius: (side * side) / (8 * town1eOffset) + town1eOffset / 2
    readonly property real halfRoadWidth: side / 8 / 2
    readonly property real town2eOffset: side * 35 / 100
    readonly property real town2eRadius: (side * side) / (8 * town2eOffset) + town2eOffset / 2
    property alias idLabel: idLabel
    required property TileData tileData
    readonly property int bonusSideIndex: (rotation + 360) % 360 / 90

    readonly property color fieldColor: (engine.GameState === GameEngine.GameEnd && engine.ScorableFields.includes(currentId))
                                        ? Constants.color.schematic.scorableField : Constants.color.schematic.field

    width: side
    height: side
    containsMode: Shape.FillContains
    antialiasing: true
    clip: true

    Text {
        id: idLabel
        text: currentId
        color: "black"
        rotation: -root.rotation
        font.pixelSize: 15
        visible: !root.parent.isPreview
    }
}
