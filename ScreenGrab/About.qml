import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    Rectangle{
        anchors.fill: parent
        color: "white"
        Image {
            id: logo_
            width: 200
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 4
            source: "qrc:/logo.svg"
            fillMode: Image.PreserveAspectFit
        }

        TextArea {
            id: aboutText_
            anchors.top: logo_.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 4
            readOnly: true
            textFormat: TextArea.RichText
            selectByMouse: true
            width: 300
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            cursorDelegate: Rectangle{
                visible: aboutText_.cursorVisible
            }
            color: "black"
            text: "<h3>ScreenGrab</h3>" + mainController.version() + "<br><p>ScreenGrab is an OCR and screen capture program for Deskdop</p><br><p>This program comes with absolutely no warranty.
See the <a href='https://www.gnu.org/licenses/old-licenses/gpl-2.0.html'>GNU General Public License, version 2 or later</a> for details.</p><p>Created by <a href='mailto:ivanoscar@outlook.fr'>VAOHITA Ivan Oscar</a></p>"
            onLinkActivated:{
                Qt.openUrlExternally(link)
            }
            onLinkHovered: {

            }
        }
    }
}
