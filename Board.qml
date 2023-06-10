import QtQuick 2.15
import QmlPresenter 1.0
import QtGraphicalEffects 1.15

Rectangle {
    id: root

    color: "#444444"

    property int capacity
    readonly property int maxCapacity: engine ? engine.mapModel.MaxCapacity : 0
    readonly property bool maxCapacityReached: capacity === maxCapacity
    property real centerTileHOffset
    property real centerTileVOffset

    property real centerTileCenterHOffset: centerTileHOffset + 0.5
    property real centerTileCenterVOffset: centerTileVOffset + 0.5

    property bool activeDrag: false
    property var activeTile: null

    signal boardRepositioned()

    Component.onCompleted: {
        capacity = root.width / Constants.defaultTileSize
        centerTileHOffset = -0.5
        centerTileVOffset = -0.5
    }

    Connections {
        target: engine ? engine.mapModel : null
        function onMinMaxChanged() {
            // checking horizontal placement
            var mapCenterHOffset = (engine.mapModel.MinX + engine.mapModel.MaxX)/2 + centerTileCenterHOffset

            if (mapCenterHOffset >= 1)
            {
                slideWest()
            }
            else if (mapCenterHOffset <= -1)
            {
                slideEast()
            }

            var vCenter
            if (centerTileCenterHOffset + engine.mapModel.MinX === -capacity/2 + 0.5)
            {
                // inserting into the leftmost column - need to expand west
                if (!maxCapacityReached)
                {
                    vCenter = (engine.mapModel.MinY + engine.mapModel.MaxY)/2 + centerTileCenterVOffset
                    if (vCenter > 0)
                        expandSouthWest()
                    else
                        expandNorthWest()
                }
            }
            else if (centerTileCenterHOffset + engine.mapModel.MaxX === capacity/2 - 0.5)
            {
                // inserting into the rightmost column - need to expand east
                if (!maxCapacityReached)
                {
                    vCenter = (engine.mapModel.MinY + engine.mapModel.MaxY)/2 + centerTileCenterVOffset
                    if (vCenter > 0)
                        expandSouthEast()
                    else
                        expandNorthEast()
                }
            }

            // checking vertical placement
            var mapCenterVOffset = (engine.mapModel.MinY + engine.mapModel.MaxY)/2 + centerTileCenterVOffset

            if (mapCenterVOffset >= 1)
            {
                slideNorth()
            }
            else if (mapCenterVOffset <= -1)
            {
                slideSouth()
            }

            var hCenter
            if (centerTileCenterVOffset + engine.mapModel.MinY === -capacity/2 + 0.5)
            {
                // inserting into the topmost row - need to expand north
                if (!maxCapacityReached)
                {
                    hCenter = (engine.mapModel.MinX + engine.mapModel.MaxX)/2 + centerTileCenterHOffset
                    if (hCenter > 0)
                        expandNorthEast()
                    else
                        expandNorthWest()
                }
            }
            else if (centerTileCenterVOffset + engine.mapModel.MaxY === capacity/2 - 0.5)
            {
                // inserting into the bottommost column - need to expand south
                if (!maxCapacityReached)
                {
                    hCenter = (engine.mapModel.MinX + engine.mapModel.MaxX)/2 + centerTileCenterHOffset
                    if (hCenter > 0)
                        expandSouthEast()
                    else
                        expandSouthWest()
                }
            }
        }
    }

    onActiveTileChanged: {
        if (activeTile)
        {
            activeTile.tileData.layoutChanged.connect(updateActiveTileRotation)
        }
    }

    function updateActiveTileRotation() {
        if (activeTile)
        {
            var activeTileData = activeTile.tileData
            activeTile.properlyRotated = activeTileData.IsPlaced &&
                    engine.mapModel.isFreeAdjacent(activeTileData.X, activeTileData.Y) &&
                    engine.mapModel.canMergeAsIs(activeTileData.X, activeTileData.Y, activeTileData)
        }
    }

    function getX(xIndex) {
        return 0.5 * root.width + Constants.tileSize * (centerTileHOffset + xIndex)
    }

    function getY(yIndex) {
        return 0.5 * root.height + Constants.tileSize * (centerTileVOffset + yIndex)
    }

    function slideWest() {
        centerTileHOffset -= 1
        boardRepositioned()
    }

    function slideEast() {
        centerTileHOffset += 1
        boardRepositioned()
    }

    function slideNorth() {
        centerTileVOffset -= 1
        boardRepositioned()
    }

    function slideSouth() {
        centerTileVOffset += 1
        boardRepositioned()
    }

    function expandNorthWest() {
        capacity++
        Constants.tileSize = internal.boardLength / capacity
        centerTileHOffset += 0.5
        centerTileVOffset += 0.5

        boardRepositioned()
    }

    function expandNorthEast() {
        capacity++
        Constants.tileSize = internal.boardLength / capacity
        centerTileHOffset -= 0.5
        centerTileVOffset += 0.5

        boardRepositioned()
    }

    function expandSouthEast() {
        capacity++
        Constants.tileSize = internal.boardLength / capacity
        centerTileHOffset -= 0.5
        centerTileVOffset -= 0.5

        boardRepositioned()
    }

    function expandSouthWest() {
        capacity++
        Constants.tileSize = internal.boardLength / capacity
        centerTileHOffset += 0.5
        centerTileVOffset -= 0.5

        boardRepositioned()
    }

    Item {
        id: clipper
        anchors.fill: parent
        anchors.margins: maxCapacityReached ? 0 : 10

        clip: true

        QtObject {
            id: internal
            property int boardLength
        }

        Component.onCompleted: {
            internal.boardLength = capacity * Constants.defaultTileSize
        }

        Grid {
            id: grid

            property int size

            Component.onCompleted: {
                size = 1 + (maxCapacity - 1) * 2 + 2
            }

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: centerTileCenterHOffset * Constants.tileSize
            anchors.verticalCenterOffset: centerTileCenterVOffset * Constants.tileSize

            Behavior on anchors.horizontalCenterOffset { NumberAnimation { duration: 200 } }
            Behavior on anchors.verticalCenterOffset { NumberAnimation { duration: 200 } }

            columns: size
            rows: size

            Repeater {
                id: repeater
                model: grid.columns * grid.rows

                Rectangle {
                    width: Constants.tileSize
                    height: Constants.tileSize
                    color: !engine ||
                           (dropArea.yIndex >= engine.mapModel.MinPlayableY && dropArea.yIndex <= engine.mapModel.MaxPlayableY ||
                            !engine.mapModel.YRangeDefined) &&
                           (dropArea.xIndex >= engine.mapModel.MinPlayableX && dropArea.xIndex <= engine.mapModel.MaxPlayableX ||
                            !engine.mapModel.XRangeDefined)
                           ? "transparent" : "cyan"
                    border.color: activeTile && activeTile.dragActive ? "silver" : "transparent"

                    Behavior on width { NumberAnimation { duration: 200 } }
                    Behavior on height { NumberAnimation { duration: 200 } }

                    DropArea {
                        id: dropArea

                        readonly property int xIndex: index%grid.size - Math.floor(grid.size/2)
                        readonly property int yIndex: Math.floor(index/grid.size) - Math.floor(grid.size/2)
                        readonly property color activeHighlightColor: redHighlight.visible ? redHighlight.color
                                                                                           : greenHighlight.visible ? greenHighlight.color
                                                                                                                    : yellowHighlight.visible ? yellowHighlight.color
                                                                                                                                              : "transparent"

                        anchors.fill: parent
                        keys: ["tile"]

                        Rectangle {
                            anchors.fill: parent
                            color: "transparent"
                            clip: true
                            visible: parent.containsDrag && engine.mapModel.isFreeAdjacent(parent.xIndex, parent.yIndex) && activeTile

                            RadialGradient {
                                anchors.fill: parent
                                gradient: Gradient {
                                    GradientStop { position: 0.0; color: Qt.rgba(dropArea.activeHighlightColor.r,
                                                                                 dropArea.activeHighlightColor.g,
                                                                                 dropArea.activeHighlightColor.b,
                                                                                 0.5) }
                                    GradientStop { position: 0.5; color: "transparent" }
                                }
                            }
                        }

                        ColoredImage {
                            id: redHighlight
                            anchors.fill: parent
                            anchors.margins: parent.width/8
                            source: "qrc:/img/x_icon.png"
                            color: "red"
                            visible: root.activeDrag && engine.mapModel.isFreeAdjacent(parent.xIndex, parent.yIndex) &&
                                     !engine.mapModel.canMergeAsIs(parent.xIndex, parent.yIndex, root.activeTile.tileData) &&
                                     !engine.mapModel.canMergeRotated(parent.xIndex, parent.yIndex, root.activeTile.tileData)
                        }

                        ColoredImage {
                            id: greenHighlight
                            anchors.fill: parent
                            anchors.margins: parent.width/8
                            source: "qrc:/img/check_icon.png"
                            color: "green"
                            visible: root.activeDrag && engine.mapModel.isFreeAdjacent(parent.xIndex, parent.yIndex) &&
                                     engine.mapModel.canMergeAsIs(parent.xIndex, parent.yIndex, root.activeTile.tileData)
                        }

                        ColoredImage {
                            id: yellowHighlight
                            anchors.fill: parent
                            anchors.margins: parent.width/8
                            source: "qrc:/img/rotate_icon.png"
                            color: "yellow"
                            visible: root.activeDrag && engine.mapModel.isFreeAdjacent(parent.xIndex, parent.yIndex) &&
                                     !engine.mapModel.canMergeAsIs(parent.xIndex, parent.yIndex, root.activeTile.tileData) &&
                                     engine.mapModel.canMergeRotated(parent.xIndex, parent.yIndex, root.activeTile.tileData)
                        }

                        function acceptsActiveTile() {
                            return engine.mapModel.isFreeAdjacent(xIndex, yIndex) &&
                                    (engine.mapModel.canMergeAsIs(xIndex, yIndex, root.activeTile.tileData) ||
                                    engine.mapModel.canMergeRotated(xIndex, yIndex, root.activeTile.tileData))
                        }

                        onDropped: {
                            engine.mapModel.placeTile(drop.source.tileData, xIndex, yIndex)
                            engine.GameState = GameEngine.TilePlaced
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: engine.highlight(-1)
                    }
                }
            }
        }
    }
}
