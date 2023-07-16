pragma Singleton
import QtQuick 2.15

QtObject {
    readonly property real defaultTileSize: 192
    property int tilePreviewSize: 120
    property int tileSize: 192
    readonly property int smallMeepleSize: 20

    property var color: QtObject {
        readonly property var schematic: QtObject {
            property color highlighter: "yellow"
            readonly property color highlighterRight: "green"
            readonly property color highlighterWrong: "red"

            readonly property color field: "lightgreen"
            readonly property color road: "grey"
            readonly property color roadBorder: "darkslategrey"
            readonly property color town: "chocolate"
            readonly property color townBorder: "brown"

            property color scorableField: "lightgreen"
            SequentialAnimation on scorableField {
                loops: Animation.Infinite

                ColorAnimation  {
                    from: color.schematic.field
                    to: color.activeElement
                    duration: 500
                }
                ColorAnimation  {
                    from: color.activeElement
                    to: color.schematic.field
                    duration: 500
                }
            }
        }
        readonly property color activeElement: "grey"
    }
}
