import QtQuick 2.0
import Ship 1.0
Rectangle {
    id: grid
    width : parent.width - 10
    height : parent.height -10
    Ship{
        id: ship1
        anchors.horizontalCenterOffset: ship1.point.x
        anchors.verticalCenterOffset: ship1.point.y
    }
}
