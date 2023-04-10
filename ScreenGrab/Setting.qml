import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts
import QtQuick.Dialogs


Page {
    id: page
    Material.theme: Material.Dark
    Material.accent: Material.Blue
    ColumnLayout{
        anchors.fill: parent
        spacing: 6
        Layout.margins: 6
        Pane{
            id: pane
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 200
            Layout.minimumHeight: 200

            Material.elevation: 16
            RowLayout{
                Rectangle{
                    Layout.preferredHeight: 176
                    Layout.preferredWidth: pane.width - addLangBtn.width - 30
                    color: "#2c2c2c"
                    border.color: "#3a86ff"
                    ListView{
                        id: langList
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        anchors.margins: 3
                        model: mainController.langModel
                        clip: true
                        delegate: SwipeDelegate{
                            id: itemDelegate
                            width: parent.width

                            contentItem: Text {
                                text: lang + " : " + langName
                                color: "white"
                            }
                            background: Rectangle{
                                color: itemDelegate.hovered? "#3a86ff" : "#464646"
                                height: parent.height - 3

                            }
                            swipe.right: Label{
                                id: deleteLabel
                                text: "Delete"
                                anchors.right: parent.right
                                anchors.verticalCenter: parent.verticalCenter
                                height: itemDelegate.height
                                verticalAlignment: Label.AlignVCenter
                                SwipeDelegate.onClicked: {
                                    console.log(index);
                                    mainController.langModel.removeLang(index);
                                }

                                background: Rectangle{
                                    color: deleteLabel.SwipeDelegate.pressed? Qt.darker("red",  1.5) : "red"
                                }
                            }
                        }
                    }
                }


                ColumnLayout{
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    Layout.rightMargin: 8
                    TextField{
                        id: langNameInput
                        Layout.preferredWidth: addLangBtn.width
                        placeholderText: "New language"
                    }

                    Button{
                        id: addLangBtn
                        text: "Add language model"

                        onClicked: {
                            if (langNameInput.text !== "")
                            {
                                fileDialog.open();
                            }
                        }
                    }
                }
            }
        }
    }

    FileDialog{
        id: fileDialog
        nameFilters: ["Tessdata (*.traineddata)"]
        fileMode: FileDialog.OpenFile
        currentFolder: Qt.resolvedUrl("file:" + mainController.homeDir())
        onAccepted: {
            console.log(selectedFile);
            mainController.addNewLanguage(selectedFile, langNameInput.text);
            langNameInput.text = "";
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
