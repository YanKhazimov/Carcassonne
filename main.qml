import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQml 2.15
import QmlPresenter 1.0
import "schematic"

Window {
    id: root

    visible: true
    visibility: "FullScreen"

    Image {
        id: background
        source: "qrc:/img/startBackgroundGPT.jpg"
        anchors.fill: parent
        fillMode: Image.Stretch
    }

    Loader {
        id: loader

        source: "qrc:/SettingsWindow.qml"
        asynchronous: true
        visible: status == Loader.Ready
        onStatusChanged: {
            engine.setWaitingCursor(status == Loader.Loading)
            if (status == Loader.Ready && "onLoaded" in item)
                item.onLoaded()
        }
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
        function onExitRequested() {
            loader.source = ""
            Qt.quit()
        }
    }
}
