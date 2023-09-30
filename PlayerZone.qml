import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15 as QGE
import QtQuick.Shapes 1.15
import com.carcassonne.cppTypes 1.0
import QmlPresenter 1.0
import EngineEnums 1.0

Item {
    id: root

    required property int playerIndex
    readonly property Player playerData: engine ? engine.getPlayer(playerIndex) : null
    readonly property color activeColor: playerData ? playerData.Color : "transparent"
    readonly property real bannerEnd: bannerImage.y + bannerImage.height
    readonly property bool ready: !activationAnimation.running
    property int smallMeepleCount: 0
    property int bigMeepleCount: 0
    property int barnCount: 0
    property int builderCount: 0
    property int pigCount: 0

    function addMeeple(meepleType, diff) {
        switch (meepleType) {
        case EngineEnums.MeepleSmall: smallMeepleCount += diff; break;
        case EngineEnums.MeepleBig: bigMeepleCount += diff; break;
        case EngineEnums.MeepleBarn: barnCount += diff; break;
        case EngineEnums.MeeplePig: pigCount += diff; break;
        case EngineEnums.MeepleBuilder: builderCount += diff; break;
        }
    }

    function getMeeplePosition(meepleType) {
        let positionInsideComponent = handGroup.item.getMeeplePosition(meepleType)
        let itemPosition = handGroup.getItemPosition()
        let x = handGroup.x + itemPosition.x + positionInsideComponent.x
        let y = handGroup.y + itemPosition.y + positionInsideComponent.y
        return Qt.point(x, y)
    }

    function getAbbeyTilePosition() {
        let positionInsideComponent = handGroup.item.getAbbeyTilePosition()
        let itemPosition = handGroup.getItemPosition()
        let x = handGroup.x + itemPosition.x + positionInsideComponent.x
        let y = handGroup.y + itemPosition.y + positionInsideComponent.y
        return Qt.point(x, y)
    }

    implicitWidth: bannerImage.width
    implicitHeight: 200

    Item {
        id: fade
        visible: false

        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 40
        anchors.top: bannerImage.verticalCenter
        height: playerData && playerData.IsActive ? parent.height - bannerImage.height/2 : 0

        Behavior on height {
            NumberAnimation {
                id: activationAnimation

                duration: 300
            }
        }

        QGE.LinearGradient {
            anchors.fill: parent
            start: Qt.point(0, 0)
            end: Qt.point(0, parent.height)
            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(activeColor.r, activeColor.g, activeColor.b, 0.5) }
                GradientStop { position: 1.0; color: "transparent" }
            }
        }
    }

    QGE.OpacityMask {
        source: bannerImage
        anchors.fill: fade
        maskSource: fade
    }

    Image {
        id: bannerImage

        source: "qrc:/img/banner.png"

        ColoredImage {
            source: "qrc:/img/banner.png"
            color: activeColor
            opacity: 0.5
        }
    }

    Shape {
        id: playerNameShape
        anchors.top: parent.top; anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 20
        height: playerName.height

        ShapePath {
            startX: 0
            startY: 0
            fillColor: "white"
            strokeColor: "black"
            strokeWidth: 1

            PathLine {
                x: playerNameShape.width
                y: 0
            }

            PathLine {
                x: playerNameShape.width - 20
                y: playerNameShape.height/2
            }

            PathLine {
                x: playerNameShape.width
                y: playerNameShape.height
            }

            PathLine {
                x: 0
                y: playerNameShape.height
            }

            PathLine {
                x: 20
                y: playerNameShape.height/2
            }

            PathLine {
                x: 0
                y: 0
            }
        }
    }

    TextEdit {
        id: playerName

        anchors.centerIn: playerNameShape
        font.pixelSize: 20
        font.family: Fonts.font6
        text: playerData ? playerData.Name : ""
        selectByMouse: true
        Keys.onEscapePressed: focus = false
        color: activeColor
    }

    Binding {
        target: playerData
        property: "Name"
        value: playerName.text
        when: playerData
    }

    ItemGroup {
        id: bonusesGroup

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: playerNameShape.bottom; anchors.topMargin: 5
        title.text: "БОНУСЫ"
        color: activeColor

        myContent: ColumnLayout {
            spacing: 10

            Row {
                id: resourcesColumn

                Layout.alignment: Qt.AlignHCenter
                spacing: 10

                Row {
                    GreyedOutImage {
                        anchors.verticalCenter: parent.verticalCenter
                        opacityValue: 0.4
                        active: !(playerData && playerData.BarrelsLead)
                        imageSource: TileBonusIndicator {
                            source: "qrc:/img/barrel.png"
                            width: 32
                            height: 32
                        }
                    }
                    MyText {
                        text: playerData ? " x" + playerData.Barrels : ""
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Row {
                    GreyedOutImage {
                        anchors.verticalCenter: parent.verticalCenter
                        opacityValue: 0.4
                        active: !(playerData && playerData.WheatLead)
                        imageSource: TileBonusIndicator {
                            source: "qrc:/img/wheat.png"
                            width: 32
                            height: 32
                        }
                    }
                    MyText {
                        text: playerData ? " x" + playerData.Wheat : ""
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Row {
                    GreyedOutImage {
                        anchors.verticalCenter: parent.verticalCenter
                        opacityValue: 0.4
                        active: !(playerData && playerData.ClothLead)
                        imageSource: TileBonusIndicator {
                            source: "qrc:/img/cloth.png"
                            width: 32
                            height: 32
                        }
                    }
                    MyText {
                        text: playerData ? " x" + playerData.Cloth : ""
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }

            Row {
                Layout.alignment: Qt.AlignHCenter
                spacing: 10

                Row {
                    spacing: 5

                    GreyedOutImage {
                        opacityValue: 0.4
                        active: !(playerData && playerData.TownLead)
                        imageSource: TileBonusIndicator {
                            source: "qrc:/img/king.png"
                            width: 64
                            height: 64
                        }
                    }
                    MyText {
                        text: playerData ? playerData.BiggestTown  : ""
                        font.pixelSize: 20
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Row {
                    spacing: 5

                    GreyedOutImage {
                        opacityValue: 0.4
                        active: !(playerData && playerData.RoadLead)
                        imageSource: TileBonusIndicator {
                            source: "qrc:/img/chieftain.png"
                            width: 64
                            height: 64
                        }
                    }

                    MyText {
                        text: playerData ? playerData.BiggestRoad : ""
                        font.pixelSize: 20
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }

        }
    }

    MyText {
        id: widthReference

        text: "x8"
        font.pixelSize: 20
        visible: false
    }

    ItemGroup {
        id: handGroup

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: bonusesGroup.bottom
        title.text: "ФИШКИ"
        color: activeColor

        myContent: ColumnLayout {
            id: handGroupComponent

            spacing: 10

            function getMeeplePosition(meepleType) {
                let meepleItems = [null, smallMeeplePlaceholder, bigMeeplePlaceholder, barnPlaceholder, builderPlaceholder, pigPlaceholder]
                return meepleItems[meepleType].mapToItem(handGroupComponent, 0, 0)
            }

            function getAbbeyTilePosition() {
                return abbeyPlaceholder.mapToItem(handGroupComponent, 0, 0)
            }

            RowLayout {
                spacing: 10
                Layout.alignment: Qt.AlignHCenter

                Row {
                    spacing: 5
                    Layout.alignment: Qt.AlignVCenter

                    MeepleSmall {
                        id: smallMeeplePlaceholder
                        draggable: false
                        opacity: 0.2
                        playerIndex: root.playerIndex
                    }

                    MyText {
                        text: "x" + smallMeepleCount
                        font.pixelSize: 20
                        anchors.verticalCenter: smallMeeplePlaceholder.verticalCenter
                        width: widthReference.width
                    }
                }

                Row {
                    spacing: 5
                    Layout.alignment: Qt.AlignVCenter

                    MeepleBig {
                        id: bigMeeplePlaceholder
                        draggable: false
                        opacity: 0.2
                        playerIndex: root.playerIndex
                    }
                    MyText {
                        text: "x" + bigMeepleCount
                        font.pixelSize: 20
                        anchors.verticalCenter: bigMeeplePlaceholder.verticalCenter
                        width: widthReference.width
                    }
                }

                Row {
                    spacing: 5
                    Layout.alignment: Qt.AlignVCenter

                    MeepleBuilder {
                        id: builderPlaceholder
                        draggable: false
                        opacity: 0.2
                        playerIndex: root.playerIndex
                    }
                    MyText {
                        text: "x" + builderCount
                        font.pixelSize: 20
                        anchors.verticalCenter: builderPlaceholder.verticalCenter
                        width: widthReference.width
                    }
                }
            }

            RowLayout {
                spacing: 10
                Layout.alignment: Qt.AlignHCenter

                Row {
                    spacing: 5
                    Layout.alignment: Qt.AlignVCenter

                    MeeplePig {
                        id: pigPlaceholder
                        draggable: false
                        opacity: 0.2
                        playerIndex: root.playerIndex
                    }
                    MyText {
                        text: "x" + pigCount
                        font.pixelSize: 20
                        anchors.verticalCenter: pigPlaceholder.verticalCenter
                        width: widthReference.width
                    }
                }

                Row {
                    spacing: 5
                    Layout.alignment: Qt.AlignVCenter

                    MeepleBarn {
                        id: barnPlaceholder
                        draggable: false
                        opacity: 0.2
                        playerIndex: root.playerIndex
                    }
                    MyText {
                        text: "x" + barnCount
                        font.pixelSize: 20
                        anchors.verticalCenter: barnPlaceholder.verticalCenter
                        width: widthReference.width
                    }
                }
            }

            Rectangle {
                id: abbeyPlaceholder

                Layout.alignment: Qt.AlignHCenter
                width: Constants.tilePreviewSize
                height: Constants.tilePreviewSize
                color: "transparent"
                border.width: 2
                border.color: "grey"

                ColoredImage {
                    anchors.centerIn: parent
                    source: "qrc:/img/x_icon.png"
                    color: "grey"
                }
            }
        }
    }
}
