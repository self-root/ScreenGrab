import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Dialogs

Page {

    Material.theme: Material.Dark
    Material.accent: Material.Blue
    Connections{
        target: textResultController
        function onSelectionReady()
        {
            console.log("S: " + textResultController.selectionStart + " E: " + textResultController.selectionEnd);
            textResult.select(textResultController.selectionStart, textResultController.selectionEnd);
        }
    }

    FontLoader{
        id:awesome
        source: "qrc:/awesome.ttf"
    }

    TabBar{
        id: bar
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 0
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        currentIndex: swipeView.currentIndex

        TabButton{
            text: "Save file"
        }

        TabButton{
            text: "Image text"
        }
    }

    SwipeView {
        id: swipeView
        anchors.top: bar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        currentIndex: bar.currentIndex

        clip: true
        Item {
            id: save
            Slider{
                id: imageRotation
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.leftMargin: 4
                anchors.topMargin: 3
                from: -180
                to: 180

                onValueChanged: {
                    tmp.rotation = value

                }
                onPressedChanged: {
                     //mainController.rotateImage(value)
                    if(pressed)
                        mainController.imageProvider.aboutToRotate(value);
                    else
                        mainController.imageProvider.rotate(value);
                }

            }

            Flickable{
                id:scroller
                anchors.top: imageRotation.bottom
                anchors.bottom: fileNameEdit.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottomMargin: 3
                contentWidth: tmp.width
                contentHeight: tmp.height
                clip: true
                Rectangle{
                    width: Math.max(scroller.width, tmp.width)
                    height: Math.max(scroller.height, tmp.height)
                    Image {
                        id: tmp
                        anchors.centerIn: parent
                        cache: false

                        source: mainController.image.imageProviderPath
                        //width: tmp.width * 50
                        //height: tmp.height * 50

                    }
                }
            }

            TextField {
                id: fileNameEdit
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: saveButton.left
                anchors.leftMargin: 2
                anchors.rightMargin: 4
                anchors.bottomMargin: 3
                readOnly: true
                width: parent.width - saveButton.implicitWidth - 16
                text: mainController.image.imagePath
                selectByMouse: true
            }

            Button{
                id: saveButton
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.rightMargin: 4
                anchors.bottomMargin: 3

                text: "Save"
                onClicked: {
                    fileDialog.open()
                }
            }
        }

        Item{
            id: textView
            TextField{
                id: searchInput
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.leftMargin: 3
                anchors.topMargin: 4
                anchors.verticalCenter: langChoice.verticalCenter
                placeholderText: "Search..."
                Label{
                    anchors.right: parent.right
                    anchors.rightMargin: 1
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 16
                    font.family: awesome.name
                    text: "\uf002"
                }

                onAccepted: {
                    textResultController.next();
                }

                onTextChanged: {
                    console.log(searchInput.text);
                    textResultController.find(searchInput.text, textResult.text)
                }
            }

            ComboBox{
                id: langChoice
                textRole: "langName"
                valueRole: "lang"
                anchors.top: parent.top
                anchors.right: searchInput.left
                anchors.topMargin: 2
                anchors.rightMargin: 6
                model: mainController.langModel
                delegate: ItemDelegate{
                    id: itemDelegate
                    contentItem: Text {
                        width: itemDelegate.width
                        text: langName
                        color: "white"
                    }


                    background: Rectangle{
                        width: langChoice.width
                        color: itemDelegate.hovered ? "#3a86ff" : "#403d39"
                    }

                    onClicked: {
                        langChoice.currentIndex = index
                        mainController.onLangModelChange(langChoice.currentValue)
                    }
                }
            }
            Button{
                id: refreshBtn
                anchors.right: langChoice.left
                anchors.top: parent.top
                anchors.topMargin: 2
                anchors.rightMargin: 6
                font.pointSize: 16
                font.family: awesome.name
                text: "\u21bb"
                flat: true

                onClicked: {
                    mainController.startExtraction(langChoice.currentValue)
                }
            }

            Rectangle{
                width: animatedImg.width
                height: animatedImg.height
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.leftMargin: 1
                anchors.bottomMargin: 1
                color: "transparent"
                visible: mainController.isExtracting
                AnimatedImage{
                    id: animatedImg
                    source: "qrc:/cube.gif"
                    playing: mainController.isExtracting
                }
            }

            ScrollView{
                id: scrollView
                anchors.top: langChoice.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.leftMargin: 2
                anchors.rightMargin: 2
                anchors.bottomMargin: 2
                anchors.topMargin: 2
                TextEdit{
                    id: textResult
                    anchors.fill: parent
                    selectByMouse: true
                    focus: true
                    text: mainController.image.imageText
                    color: "white"


                    MouseArea{
                        anchors.fill: parent
                        acceptedButtons: Qt.RightButton
                        cursorShape: Qt.IBeamCursor
                        onClicked: {
                            editorMenu.popup()

                        }
                    }
                }
            }
        }
    }

    Menu{
        id: editorMenu
        MenuItem{
            text: "Save"
            onClicked: {
                mainController.image.imageText = textResult.text
                mainController.onSave()
            }
        }

        MenuItem{
            text: "Select all"
            onClicked: {
                textResult.selectAll()
            }
        }
        MenuItem
        {
            text: "Copy"
            onClicked: {
                textResult.copy()
            }

        }

        MenuItem{
            text: "Copy all"
            onClicked: {
                mainController.toClipboard(textResult.text)
            }
        }
    }

    FileDialog{
        id: fileDialog
        nameFilters: ["Images (*png *jpg *jepg)"]
        fileMode: FileDialog.SaveFile
        currentFile: Qt.resolvedUrl("file:" + (fileNameEdit.text === "newimage" ? mainController.imageDefaultName() : fileNameEdit.text))
        onAccepted:{
            mainController.image.imageText = textResult.text
            mainController.onSave(fileDialog.selectedFile)
        }
    }


}
