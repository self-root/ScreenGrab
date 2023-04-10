import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts
import QtQuick.Dialogs

Page {
    Material.theme: Material.Dark
    Material.accent: Material.Blue

    header: Rectangle{
        id: header
        height: 42
        color: "#3e3f40"
        //border.color: "#3a86ff"
        radius: 3

        Label{
            anchors.centerIn: parent
            text: "Saved"
            font.pixelSize: 16
            color: "white"
            font.bold: true
        }
        Rectangle{
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            color: "#3a86ff"
            height: 2
        }
    }

    ListView{
        id : recentList
        anchors.fill: parent
        model: mainController.recentImageModel
        delegate: ItemDelegate{
            id: deledate
            width: recentList.width
            height: 150
            contentItem: Pane{
                Material.elevation: 10
                height: contentHeight
                rightPadding: 3
                topPadding: 0
                bottomPadding: 3

                RowLayout{
                    anchors.fill: parent
                    clip: true
                    Image {
                        source: Qt.resolvedUrl("file:" + imagePath)
                        Layout.maximumWidth: deledate.height
                        Layout.maximumHeight: deledate.height
                        fillMode: Image.PreserveAspectFit
                    }

                    ColumnLayout{
                        Text {
                            text: imagePath
                            wrapMode: Text.Wrap
                            color: "white"
                        }

                        Text {
                            text: Qt.formatDateTime(imageDate, "dd MMM yyyy - hh:mm:s")
                            wrapMode: Text.Wrap
                            color: "white"
                        }
                    }
                }

                MouseArea{
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton | Qt.LeftButton
                    onClicked: {
                        if (mouse.button === Qt.LeftButton)
                            mainController.recentImageSelected(imageId, imagePath, imageText, imageDate);
                        else if(mouse.button === Qt.RightButton)
                        {
                            recentList.currentIndex = index
                            recentMenu.popup()
                        }
                    }
                }
            }
        }
    }

    Menu{
        id: recentMenu
        Material.accent: Material.Dark
        MenuItem{
            text: "View"
            onClicked: {
                mainController.recentImageSelected(recentList.currentIndex);
            }
        }

        MenuItem{
            text: "Delete entry"
            onClicked: {
                mainController.removeRecentImage(recentList.currentIndex)
            }
        }

        MenuItem{
            text: "Delete"
            onClicked: {
                deleteDialog.open()
            }
        }
    }

    Dialog{
        id: deleteDialog
        modal: true
        title: "Remove image"
        contentItem: Text {
            id: textContent
            wrapMode: Text.Wrap
        }

        standardButtons: Dialog.Ok | Dialog.Cancel

        onAboutToShow: {
            textContent.text = "This will remove: " + mainController.recentImageModel.imagePathAt(recentList.currentIndex) + " from the disc as well!"
        }

        onAccepted: {
            mainController.removeRecentImage(recentList.currentIndex, true)
        }
    }
}
