pragma Singleton
import QtQuick 2.15

QtObject {
    readonly property real defaultTileSize: 144
    property int tilePreviewSize: 120
    property int tileSize: 144
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
        }
    }
}
