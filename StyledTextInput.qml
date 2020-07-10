import QtQuick 2.9
import QtQuick.Controls 2.2

TextField{
    id: input
    height: 24
    property bool backGroundVisible: false
    property var backgroundColor: "#F3F7FB"
    background: Rectangle {
        id: rect
        border.width: backGroundVisible ? 2 : 0
        color: input.backgroundColor
    }

    placeholderText: qsTr("Input name")
    verticalAlignment: Qt.AlignVCenter
    horizontalAlignment: Qt.AlignLeft
    leftPadding: 8
}
