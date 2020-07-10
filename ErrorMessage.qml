import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.2

MessageDialog {
    title: "Error detected"
    text: "Nothink selecterd"
    informativeText: "Select a user before removing"
    Component.onCompleted: visible = true
}
