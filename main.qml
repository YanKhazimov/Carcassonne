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

    Loader {
        id: loader

        anchors.centerIn: parent
        source: "qrc:/SettingsWindow.qml"
    }

    Connections {
        target: loader.item
        function onUrlRequested(urlAddress) {
            loader.source = urlAddress
        }
    }
}
