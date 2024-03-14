pragma Singleton
import QtQuick 2.15
import QtQuick.Window 2.15

QtObject {
    property real screenScale: Screen.width / 1920

    // readonly property int defaulttileSize: 192
    readonly property int tilePreviewSize: 96
    readonly property int tileSize: 192//defaulttileSize

    // readonly property int defaultSmallMeepleSize: 30
    readonly property int smallMeeplePreviewSize: 20
    readonly property int smallMeepleSize: 30//defaultSmallMeepleSize

    readonly property int smallMeepleTotal: 8
    readonly property int bigMeepleTotal: 2
    readonly property int barnTotal: 1
    readonly property int builderTotal: 1
    readonly property int pigTotal: 1

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
        readonly property color activeElement: "white"
    }
}
