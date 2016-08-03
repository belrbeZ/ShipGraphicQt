#include "appcore.h"

AppCore::AppCore(QObject *parent) : QObject(parent)
{
    count = 0;

}
void AppCore::recieveFromQml()
{
    count++;
    emit sendToQml(count);
}
void AppCore::recieveFromQmlSlider(int newCount)
{
    count=newCount;
    Ship::shipsSize=newCount;

        //image.scaledToHeight(shipsSize);
        //image.scaledToWidth(shipsSize);

    emit sendToQml(Ship::shipsSize);
}

void newGameState( gameArea,int windowWidth,int windowHeight)
{
    //emit createShip();
}

//void addShip()
//{

//}
