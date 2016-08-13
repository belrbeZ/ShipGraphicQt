#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
//#include "ship.h"
class AppCore : public QObject
{
    Q_OBJECT
public:
    explicit AppCore(QObject *parent = 0);
    //Qcomn targetComponent=Qt.createComponent("ship.h");
signals:
    void sendToQml(int count);
    //void createShip();
    //void shipsSizeChanged();
public slots:
    //void newGameState(QW gameArea,int windowWidth,int windowHeight);
    //void addShip(Item gameArea);
    void recieveFromQml();
    void recieveFromQmlSlider(int newCount);
private:
    int count;
};

#endif // APPCORE_H
