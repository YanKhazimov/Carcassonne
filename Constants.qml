pragma Singleton
import QtQuick 2.15

QtObject {
    readonly property real defaultTileSize: 144
    property int tileSize: 144
    readonly property int smallMeepleSize: 20

    readonly property var color: QtObject {
        readonly property var schematic: QtObject {
            readonly property color highlighter: "yellow"
        }
    }
}
