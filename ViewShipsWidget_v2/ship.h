#ifndef SHIP_H
#define SHIP_H
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <windows.h>
#include <QImage>
#include <QDebug>
#include <QLine>
#include <QVector>
#include <QTime>
//#include "ui_mainwindow.h"

class Ship : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Ship(QObject *parent = 0);
    ~Ship();
    static int shipsSize;
    static int numShips;
    static bool visibleAndWay;
    //void shipsFieldsChangedAction()
signals:
    void posChanged(double oldx,double oldy,double newx,double  newy);
public slots:
    void shipsFieldsChangedAction();
    void slotGameTimer(); // Слот, который отвечает за обработку перемещения треугольника
    void changeSizeOfShip(int);
    void updateShips();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal angle;
    QImage image;

    QString shipID;
    qint16 routingAngle;
    quint8 shipVelocity;
    quint8 visibilityScopeAngle;
    quint8 visibilityScopeLength;
    quint64 shipTotalDistance ;
    QTime routingTime;
public:
    QString getShipID();
    qint16 getRoutingAngle();
    quint8 getShipVelocity();
    quint8 getVisibilityScopeAngle();
    quint8 getVisibilityScopeLength();
    quint64 getShipTotalDistance();
    QTime getRoutingTime();

    void setShipID(QString sID);
    void setRoutingAngle(qint16 rAngle);
    void setShipVelocity(quint8 sVelocity);
    void setVisibilityScopeAngle(quint8 vScopeAngle);
    void setVisibilityScopeLength(quint8 vScopeLength);
    void setShipTotalDistance(quint64 sTotalDistance);
    void setRoutingTime(QTime rTime);
};

#endif // SHIP_H
