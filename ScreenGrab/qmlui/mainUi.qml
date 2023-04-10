import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Dialogs
//import "." as Cm
import "components" // Turns ou, the import path follows the ui.qrc prefix/dir structure
// And must add project root dir to the QML_IMPORT_PATH variable

Item {
    id: rootItem
    anchors.fill: parent
    //Material.theme: Material.Dark
    //Material.accent: Material.Blue
    Connections{
        target: mainController

        function onImageView(){
            stackView.push("ImageView.qml")
        }
    }

    Rectangle{
        id: navigation
        anchors.left: parent.left
        anchors.right: mainContent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0

        color: '#212226'
        width: 200

        Column{
            anchors.fill: parent
            spacing: 12
            Image {
                id: logo
                width: parent.width
                source: "qrc:/logo.svg"
                fillMode: Image.PreserveAspectFit

            }

            MenuButton{
                id: homeButton
                iconText: "\uf015"
                labelText: "Home"
                onClicked: stackView.push("Recent.qml")
            }

            MenuButton{
                id: selectionButton
                iconText: "\uf5cb"
                labelText: "Selection"
                onClicked: mainController.selection()
            }

            MenuButton{
                id: fromImageButton
                iconText: "\uf03e"
                labelText: "From Image"
                onClicked: fileDialog.open()
            }

            MenuButton{
                id: wholeScreenButton
                iconText: "\uf108"
                labelText: "Entire Screen"
                onClicked: mainController.captureScreen()
            }

            MenuButton{
                id: setting
                iconText: "\uf1de"
                labelText: "Settings"
                onClicked: stackView.push("Setting.qml")
            }

            MenuButton{
                id: quit
                iconText: "\u23fb"
                labelText: "Quit"
                onClicked: mainController.quit()
            }
        }


        Rectangle{
            id: about
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottomMargin: 0
            width: aboutText.width
            height: 30
            color: "transparent"

            Text {
                id: aboutText
                text: "About..."
                color: "white"

                states: [
                    State {
                        name: "colorChange"
                        when: mouseArea.containsMouse === true
                        PropertyChanges {
                            target: aboutText
                            color: "#3a86ff"
                        }
                    }
                ]
            }
            MouseArea{
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    aboutText.color = "#3a86ff"
                    cursorShape = Qt.PointingHandCursor
                }
                onClicked: {
                    stackView.push("qrc:/About.qml")
                }
            }
        }
    }

    Rectangle{
        id: mainContent
        anchors.left: navigation.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        color: '#16171b'

        StackView {
            id: stackView
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.topMargin: 0
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            clip: true
            initialItem: "Recent.qml"


        }
    }

    FileDialog{
        id: fileDialog
        nameFilters: ["Images (*png *jpg *jepg)"]
        fileMode: FileDialog.OpenFile
        currentFolder: Qt.resolvedUrl("file:" + mainController.pictureFolder())
        onAccepted: mainController.onImageSelected(fileDialog.selectedFile)
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
