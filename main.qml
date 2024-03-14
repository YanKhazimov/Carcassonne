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

    SettingsWindow {
        gameWindowLoader: loader
    }

    Loader {
        id: loader

        active: false
        source: "qrc:/GameWindow.qml"
        asynchronous: true
        visible: status == Loader.Ready
        onStatusChanged: {
            engine.setWaitingCursor(status == Loader.Loading)
            if (status == Loader.Ready) {
                if (newGame && "onNewGameLoaded" in item)
                    item.onNewGameLoaded()
                else if (!newGame && "onOldGameLoaded" in item)
                    item.onOldGameLoaded()
            }
        }

        property bool newGame: true

        function loadNewGame() {
            newGame = true
            if (!active)
                active = true
        }

        function loadOldGame() {
            newGame = false
            if (!active)
                active = true
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
}
