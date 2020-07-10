import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import Common 1.0


Window {
    property string userName: qsTr("")
    id: chatWindow
    width: 640
    height: 480
    visible: true
    title: userName
    function getNewMessage(time, sender, body){
        chatArea.append(time + " [" + sender + "] " +body);
    }

    onClosing: {
        controller.closeConnection(userName);
    }
    ColumnLayout{
        anchors.fill: parent
        spacing: 8
        TextArea{
            Layout.leftMargin: 8
            Layout.rightMargin: 8

            id: chatArea
            Layout.fillHeight: true
            Layout.fillWidth: true
            readOnly: true
            background: Rectangle{
                border.color: "black"
                border.width: 2
            }
        }
        RowLayout{
            spacing: 8
            Layout.leftMargin: 8
            Layout.rightMargin: 8
            Layout.bottomMargin: 8
            Layout.fillWidth: true
            StyledTextInput{
                backGroundVisible: true
                Layout.fillWidth: true
                id: messageInput
            }
            Button{
                background: Rectangle{
                    radius: 5
                    border.color: Constants.borderColor
                    border.width: 2
                }
                text : qsTr("Send")
                onClicked: {
                    controller.sendMessageToServer(userName, messageInput.text);
                    messageInput.clear()
                }
            }
        }
    }
}
