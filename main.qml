import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQml 2.15
import QmlPresenter 1.0
import "schematic"

Window {
    id: root

    width: 1280
    height: 980
    visible: true
    title: qsTr("Carcassonne")
    flags: Qt.Window | Qt.CustomizeWindowHint | Qt.WindowTitleHint |
           Qt.WindowSystemMenuHint | Qt.WindowMinimizeButtonHint | Qt.WindowCloseButtonHint

    Image {
        id: background
        source: "qrc:/img/startBackground.jpg"
        height: parent.height
        fillMode: Image.PreserveAspectFit
        visible: loader.source != "qrc:/GameWindow.qml" || loader.status == Loader.Loading
    }

    Loader {
        id: loader

        anchors.centerIn: parent
        source: "qrc:/SettingsWindow.qml"
        asynchronous: true
        visible: status == Loader.Ready
        onStatusChanged: engine.setWaitingCursor(status == Loader.Loading)
    }

    Image {
        id: loadingIndicator
        source: "qrc:/img/tileBack.png"
        width: 200
        height: 200
        anchors.centerIn: parent
        visible: loader.status == Loader.Loading

        PropertyAnimation {
            target: loadingIndicator
            property: "rotation"
            from: 0
            to: 360
            running: loadingIndicator.visible
            loops: Animation.Infinite
            duration: 500
        }
    }

    Connections {
        target: loader.item
        function onUrlRequested(urlAddress) {
            loader.source = urlAddress
        }
    }
}
