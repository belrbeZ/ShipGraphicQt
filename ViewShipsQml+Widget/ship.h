#ifndef SHIP_H
#define SHIP_H

#include <QDebug>
#include <QTimer>
#include <QImage>
#include <QLine>
#include <QPainter>
#include <QPaintEvent>
class Ship
{
public:
    Ship();
    ~Ship();
//    void paintEvent(QPaintEvent *);
private:
    QString m_shipID;
    qint16 m_routingAngle;
    quint8 m_shipVelocity;
    quint8 m_visibilityScopeAngle;
    quint8 m_visibilityScopeLength;
    quint64 m_shipTotalDistance;
    QTime m_routingTime;

    QPoint m_point;
    QTimer *internalTimer;

    QLine* m_ways;
    int numWays;
    QLine* m_triangle;
    QImage* m_image;

public:
    const static qint16 maxRoutingAngle = 180;
    const static quint8 maxShipVelocity = 4;
    const static quint8 maxVisibilityScopeAngle = 30;
    const static quint8 maxVisibilityScopeLength = 5;
    const static qint16 minRoutingAngle = -180;
    const static quint8 minShipVelocity = 1;
    const static quint8 minVisibilityScopeAngle = 0;
    const static quint8 minVisibilityScopeLength = 0;
    const static quint8 minShipSize = 10;
    const static quint8 maxShipSize = 20;
    const static qint32 minShipPoint = 0;
    const static qint32 maxShipPoint = 640;

//public slots:
//    void painting();
};

#endif // SHIP_H
