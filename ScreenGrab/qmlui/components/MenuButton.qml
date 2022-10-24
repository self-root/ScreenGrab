import QtQuick 2.15
import QtQuick.Controls 2.5

Item {
    id: btn
    //property alias iconSource: img.source
    property alias iconText: icn.text
    property alias labelText: txt.text
    signal clicked()
    FontLoader{
        id:awesome
        source: "qrc:/awesome.ttf"
    }
    width: 200
    height: 42
    Rectangle{
        id: rectBtn
        width: parent.width
        height: 40
        color: "transparent"
        Row{
            spacing: 8
            Label{
                id: icn
                width: 40
                height: 40
                font.family: awesome.name
                font.pointSize: 26
                color: "white"
                verticalAlignment: "AlignVCenter"
                horizontalAlignment: "AlignHCenter"
            }

            Label{
                id: txt
                height: parent.height
                verticalAlignment: "AlignVCenter"
                font.pointSize: 16
                color: "white"
            }
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: btn.clicked()
            onEntered:{

                rectBtn.color = txt.text === "Quit"? "#ff595e" : "#3a86ff"
            }

            onExited: {
                rectBtn.color = "transparent"
            }
        }
    }
}
