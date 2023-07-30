pragma Singleton
import QtQuick 2.15

Item {
    FontLoader {
        id: gravtrac_compressed_bd
        source: "qrc:/fonts/gravtrac_compressed_bd.otf"
    }
    FontLoader {
        id: zekton
        source: "qrc:/fonts/zekton_rg.otf"
    }
    FontLoader {
        id: engry
        source: "qrc:/fonts/engry.otf"
    }
    FontLoader {
        id: inglobal
        source: "qrc:/fonts/inglobal.ttf"
    }
    FontLoader {
        id: remissis_sb
        source: "qrc:/fonts/remissis_sb.otf"
    }
    FontLoader {
        id: minaeff_Ect_bold
        source: "qrc:/fonts/Minaeff_Ect-Bold.ttf"
    }
    FontLoader {
        id: zeroCool
        source: "qrc:/fonts/ZeroCool.otf"
    }

    readonly property string font1: zekton.name
    readonly property string font2: engry.name
    readonly property string bonuses: inglobal.name
    readonly property string font4: remissis_sb.name
    readonly property string font5: gravtrac_compressed_bd.name
    readonly property string font6: minaeff_Ect_bold.name
    readonly property string font7: zeroCool.name
}
