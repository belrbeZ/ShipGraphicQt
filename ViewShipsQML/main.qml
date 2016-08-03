import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import Ship 1.0
ApplicationWindow {
    visible: true
    width: 640
    height: 480
    minimumHeight: 350
    minimumWidth: 350
    title: qsTr("Hello World")
    Connections{
        target: appCore
        onSendToQml:{   //если сигнал sendToQml
            labelCount.text = appCore.count
        }
        Component.onCompleted: appCore.newGameState(gameArea, ApplicationWindow.width, ApplicationWindow.height)
    }

    MainForm {
        anchors.fill: parent
        ColumnLayout {
            id: columnLayout1
            spacing: 2
            anchors.fill: parent
            Layout.minimumHeight: 420
            Layout.minimumWidth: 335
            Text {
                text: qsTr("Hello World")
                anchors.top: parent.top
                Layout.alignment: Qt.AlignCenter
            }
            GameArea{
                id: gameArea
                anchors.centerIn: parent
            }
            Text {
                id: labelCount
                parent: columnLayout1
                Layout.alignment: Qt.AlignCenter
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: "Hello, world!"
            }

            Button {
                id: dialogButtonOk
                Layout.alignment: Qt.AlignCenter
                width: parent.width / 2
                style: ButtonStyle {
                    background: Rectangle {
                        color: control.pressed ? "#E3F2FD" : "#0D47A1"
                        border.width: 2
                    }
                    label: Text {
                        text: qsTr("Ok")
                        color: "#34aadc"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
                onClicked: {
                    appCore.recieveFromQml()
                }
            }

            Row {
                id: row1
                height: sliderHorizontal1.height
                Layout.alignment: Qt.AlignCenter
                anchors.bottom: row2.top
                anchors.left: columnLayout1.left
                anchors.right: columnLayout1.right
                Rectangle {
                    width:5
                    anchors.top : parent.top
                    anchors.bottom : parent.bottom
                    color:"#d7d7d7"
                }
                Slider {
                    id: sliderHorizontal1
                    width: row1.width / 2 - 7.5
                    maximumValue: 25
                    onValueChanged: appCore.recieveFromQmlSlider(sliderHorizontal1.value)
                }
                Rectangle {
                    width:5
                    anchors.top : parent.top
                    anchors.bottom : parent.bottom
                    color:"#d7d7d7"
                }

                Slider {
                    id: sliderHorizontal2
                    width: row1.width / 2 - 7.5
                    height: sliderHorizontal1.height
                    maximumValue: 100
                    onValueChanged: appCore.recieveFromQmlSlider(sliderHorizontal2.value)
                }
                Rectangle {
                    width:5
                    anchors.top : parent.top
                    anchors.bottom : parent.bottom
                    color:"#d7d7d7"
                }
            }
            Row {
                id: row2
                height: 50
                Layout.alignment: Qt.AlignCenter
                anchors.left: columnLayout1.left
                anchors.right: columnLayout1.right
                anchors.bottom: columnLayout1.bottom
                Button {
                    id: button1
                    width: row2.width / 2
                    anchors.top:parent.top
                    anchors.bottom:parent.bottom
                    style: ButtonStyle {
                        background: Rectangle{
                            color: control.pressed ? "#E3F2FD" : "#0D47A1"
                            border.color: control.pressed ? "#0D47A1" : "#E3F2FD"
                            border.width: 2
                            radius: 5
                        }
                        label: Text {
                            text: qsTr("Press Me 1 please")
                            color: control.pressed ? "#0D47A1" : "#E3F2FD"
                        }
                    }
                    onClicked: messageDialog.show(qsTr("Button 1 pressed"))
                }

                Button {
                    id: button2
                    width: row2.width / 2
                    anchors.top:parent.top
                    anchors.bottom:parent.bottom
                    text: qsTr("Press Me 2")
                    onClicked: messageDialog.show(qsTr("Button 2 pressed"))
                }
            }
        }
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
