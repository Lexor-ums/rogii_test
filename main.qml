import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import Common 1.0
import "ChatWindowCreation.js" as ChatWindowCreation

Window {
    id: mainWindow
    visible: true
    width: 250
    height: 640

    title: qsTr("Chat imitation")
    Window {
        visible: false
        minimumWidth: 300
        minimumHeight: 120
        id: addUserDialog
        modality : Qt.ApplicationModal
        title: qsTr("Add user")
        ColumnLayout{
            anchors.fill: parent
            id: addUserLayout
            Label{
                Layout.leftMargin: 8
                Layout.rightMargin: 8
                text: qsTr("Enter name")
            }
            StyledTextInput{
                id: nameInput
                Layout.leftMargin: 8
                Layout.rightMargin: 8
                Layout.fillWidth: true
            }
            Label{
                id: errorStr
                Layout.leftMargin: 8
                Layout.rightMargin: 8
                text: qsTr("")
                color: "red"
            }
            RowLayout{
                Layout.leftMargin: 8
                Layout.rightMargin: 8
                Layout.bottomMargin: 8
                Layout.fillWidth: true
                Item{
                    Layout.fillWidth: true
                }
                Button{
                    id: acceptButton
                    text: qsTr("Accept")
                    onClicked: {
                        var enteredName = nameInput.text;
                        if (!userModel.isNameExist(enteredName) && enteredName !== "") {
                            userModel.add(enteredName);
                            addUserDialog.visible = false;
                            errorStr.text = qsTr("")
                        }
                        else {
                            errorStr.text = qsTr("name exist or empty")
                        }
                    }
                }
                Button{
                    id: cancelButton
                    text: qsTr("Cansel")
                    onClicked: addUserDialog.visible = false
                }
            }
        }
    }
    ColumnLayout{
        id: mainLayout
        spacing: 8
        anchors.fill: parent
        Label {
            Layout.leftMargin: 8
            Layout.topMargin: 8

            id: usersLabel
            text: qsTr("Users:")
            font.bold: true
        }

        RowLayout{
            Layout.leftMargin: 8
            Button {
                id: addUserButton
                Layout.minimumWidth: Constants.buttonWidth
                Layout.minimumHeight: Constants.buttonheight
                Layout.maximumWidth: Constants.buttonWidth
                Layout.maximumHeight: Constants.buttonheight
                ToolTip.text: qsTr("Add user")
                ToolTip.visible: hovered

                Image {
                    anchors.fill: parent
                    id: addUserButtonImage
                    source: "qrc:/images/UserAdd_40960.png"
                }
                onClicked: {
                    addUserDialog.visible = true
                }
            }
            Button {
                id: removeUserButton
                Layout.minimumWidth: Constants.buttonWidth
                Layout.minimumHeight: Constants.buttonheight
                Layout.maximumWidth: Constants.buttonWidth
                Layout.maximumHeight: Constants.buttonheight
                ToolTip.text: qsTr("Remove user")
                ToolTip.visible: hovered
                Image {
                    anchors.fill: parent
                    id: removeUserButtonImage
                    source: "qrc:/images/UserRemove_40959.png"
                }
                onClicked: {
                    console.log(listView.currentIndex);
                    if(listView.currentIndex === -1){
                        ChatWindowCreation.createObjects("ErrorMessage.qml", mainWindow)

                    }
                    else{
                        controller.closeConnection(userModel.at(listView.currentIndex).name);
                        userModel.remove(listView.currentIndex);
                    }
                }
            }
            Item {
                Layout.fillWidth: true
            }
        }
        ListView{
            id: listView
            Layout.leftMargin: 8
            Layout.rightMargin: 8
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: userModel.data
            delegate: Rectangle {
                width: listView.width
                height: 40
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        listView.currentIndex = index
                        console.log(listView.currentIndex)
                    }
                    onDoubleClicked: {
                        controller.openNewChat(model.name)
                    }
                }

                Rectangle{
                    anchors.fill: parent
                    anchors.topMargin: 4
                    anchors.bottomMargin: 4
                    border.color: Constants.borderColor
                    border.width: 1
                    radius: 5
                    color: (listView.currentIndex === index) ? "#78fadc" : "#b6fafa"
                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 16
                        anchors.verticalCenter: parent.verticalCenter
                        renderType: Text.NativeRendering
                        font.pixelSize: 16
                        text: model.name
                    }
                }
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
