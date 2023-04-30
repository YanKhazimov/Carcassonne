import QtQuick 2.15

BinarySwitch {
    id: root

    leftOption: "Картинки"
    rightOption: "Схемы"
    on: Preferences.schematicView
    callback: function() {
        Preferences.schematicView = !Preferences.schematicView
    }
}
