#ifndef SHIP_H
#define SHIP_H

#include <QTime>

class Ship
{

public:
    const static qint16 maxRoutingAngle = 180;
    const static quint8 maxShipVelocity = 4;
    const static quint8 maxVisibilityScopeAngle = 30;
    const static quint8 maxVisibilityScopeLength = 5;
    const static qint16 minRoutingAngle = -180;
    const static quint8 minShipVelocity = 0;
    const static quint8 minVisibilityScopeAngle = 0;
    const static quint8 minVisibilityScopeLength = 0;

private:
    static quint8 shipsNum;
    QString shipID;
    qint16 routingAngle;
    quint8 shipVelocity;
    quint8 visibilityScopeAngle;
    quint8 visibilityScopeLength;
    quint64 shipTotalDistance ;
    QTime routingTime;

public:
    Ship(QString sID, qint16 rAngle, quint8 sVelocity, quint8 vScopeAngles,
         quint8 vScopeLength, quint64 sTotalDistance, QTime rTime);
    Ship();
    Ship(const Ship& other);
    ~Ship();
    static quint8 getShipsNum();
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
