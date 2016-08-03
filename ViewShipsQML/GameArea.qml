import QtQuick 2.7
Rectangle {
    id: grid
    width : parent.width - 10
    height : parent.height / 2
//    Connections{
//        target: appCore
//        onCreateShip:{   //если сигнал sendToQml
//            appCore.addShip();
//        }
//    }
}
