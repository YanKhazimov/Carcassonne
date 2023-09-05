import QtQuick 2.15

Item {
    id: root

    property int activeTab: 0
    readonly property bool handsTabActive: activeTab === 0
    readonly property bool remainingsTabActive: activeTab === 1
    readonly property bool logTabActive: activeTab === 2

    implicitWidth: 500
    height: childrenRect.height

    Row {
        id: tabsRow

        anchors.horizontalCenter: parent.horizontalCenter

        Repeater {
            id: tabsRepeater

            model: ["Раздача", "Остаток", "Журнал"]
            delegate: Rectangle {
                width: 150
                height: 40
                color: "#bb000000"

                Rectangle {
                    height: 4
                    width: parent.width
                    color: "white"
                    visible: root.activeTab === index
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: root.activeTab = index

                    MyText {
                        anchors.centerIn: parent
                        text: modelData
                        color: index === root.activeTab || parent.containsMouse ? "white" : "grey"
                        font.pixelSize: 20
                    }
                }
            }
        }
    }

    Rectangle {
        height: 10
        width: parent.width
        anchors.top: tabsRow.bottom
        color: "#bb000000"
    }
}
