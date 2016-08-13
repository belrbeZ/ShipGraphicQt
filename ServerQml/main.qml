import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4

Window {
    visible: true
    width: 640
    height: 480
    minimumHeight: 100
    minimumWidth: 200
    title: qsTr("Server for ships")

    Connections{
        target: server
        onSendToQml:{   //если сигнал sendToQml
            labelCount.text = count
            if(count>0){
                startBut.enabled = false
                startBut.opacity = 50
            }
            else{
                startBut.enabled= true
                startBut.opacity = 100
            }
        }
    }

    MouseArea {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height/2

        onClicked: {
            Qt.quit();
        }

        Text {
            id: labelCount
            anchors.centerIn: parent
    //        verticalAlignment: Text.AlignVCenter
    //        horizontalAlignment: Text.AlignHCenter
            text: "Hello, world!"
        }
    }

    Button {
        id: startBut
        //anchors.fill: parent
        //anchors.flo : parent.top
        anchors.bottom : parent.bottom
        width: parent.width
        height: parent.height/2
        style: ButtonStyle {
            background: Rectangle {
                color: control.pressed ? "#E3F2FD" : "#0D47A1"
                border.width: 2
            }
            label: Text {
                text: qsTr("Start")
                color: "#34aadc"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
        onClicked: {
            server.recieveFromQml()
        }
    }
}
