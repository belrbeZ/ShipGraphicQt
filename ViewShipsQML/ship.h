#ifndef SHIP_H
#define SHIP_H

#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <QBrush>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include "randomvaluegenerator.h"
class Ship : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString shipID READ shipID WRITE setShipID NOTIFY shipIDChanged)
    Q_PROPERTY(qint16 routingAngle READ routingAngle WRITE setRoutingAngle NOTIFY routingAngleChanged)
    Q_PROPERTY(quint8 shipVelocity READ shipVelocity  WRITE setShipVelocity  NOTIFY shipVelocityChanged)
    Q_PROPERTY(quint8 visibilityScopeAngle READ visibilityScopeAngle WRITE setVisibilityScopeAngle NOTIFY visibilityScopeAngleChanged)
    Q_PROPERTY(quint8 visibilityScopeLength READ visibilityScopeLength WRITE setVisibilityScopeLength NOTIFY visibilityScopeLengthChanged)
    Q_PROPERTY(quint64 shipTotalDistance READ shipTotalDistance WRITE setShipTotalDistance NOTIFY shipTotalDistanceChanged)
    Q_PROPERTY(QTime routingTime READ routingTime WRITE setRoutingTime NOTIFY routingTimeChanged)
    Q_PROPERTY(QPoint point READ point WRITE setPoint NOTIFY pointChanged)
    Q_PROPERTY(QLine* lines READ lines)
private:
    static quint8 shipsNum;


    QString m_shipID;
    qint16 m_routingAngle;
    quint8 m_shipVelocity;
    quint8 m_visibilityScopeAngle;
    quint8 m_visibilityScopeLength;
    quint64 m_shipTotalDistance;
    QTime m_routingTime;

    QPoint m_point;
    QTimer *internalTimer;

    QImage image="ship.jpg";


    QLine* m_lines;
    int numLines;
public:
    const static qint16 maxRoutingAngle = 180;
    const static quint8 maxShipVelocity = 4;
    const static quint8 maxVisibilityScopeAngle = 30;
    const static quint8 maxVisibilityScopeLength = 5;
    const static qint16 minRoutingAngle = -180;
    const static quint8 minShipVelocity = 0;
    const static quint8 minVisibilityScopeAngle = 0;
    const static quint8 minVisibilityScopeLength = 0;
    const static quint8 minShipSize = 10;
    const static quint8 maxShipSize = 20;
    const static quint8 minShipPoint = 0;
    const static quint16 maxShipPoint = 640;

    explicit Ship(QString sID, qint16 rAngle, quint8 sVelocity, quint8 vScopeAngles,
    quint8 vScopeLength, quint64 sTotalDistance, QTime rTime);
    explicit Ship(QQuickItem *parent =0);
    explicit Ship(const Ship& other);
    ~Ship();

    //Q_INVOKABLE start();
    //Q_INVOKABLE stop();

    static quint8 getShipsNum();
    static int shipsSize;

    void paint(QPainter *painter) override;
    void paintTriangle(QPainter *painter);

    QString shipID() const;
    qint16 routingAngle() const;
    quint8 shipVelocity() const;
    quint8 visibilityScopeAngle() const;
    quint8 visibilityScopeLength() const;
    quint64 shipTotalDistance() const;
    QTime routingTime() const;
    QPoint point() const;
    int size() const;

    QLine* lines() const;

public slots:
    void move();

    void setShipID(QString shipID);
    void setRoutingAngle(qint16 routingAngle);
    void setShipVelocity(quint8 shipVelocity);
    void setVisibilityScopeAngle(quint8 visibilityScopeAngle);
    void setVisibilityScopeLength(quint8 visibilityScopeLength);
    void setShipTotalDistance(quint64 shipTotalDistance);
    void setRoutingTime(QTime routingTime);
    void setPoint(QPoint point);

    Q_INVOKABLE void changeShipsSize();
signals:
    void shipIDChanged(QString shipID);
    void routingAngleChanged(qint16 routingAngle);
    void shipVelocityChanged(quint8 shipVelocity);
    void visibilityScopeAngleChanged(quint8 visibilityScopeAngle);
    void visibilityScopeLengthChanged(quint8 visibilityScopeLength);
    void shipTotalDistanceChanged(quint64 shipTotalDistance);
    void routingTimeChanged(QTime routingTime);
    //    void colorOfShipChanged(QColor colorOfShip);
    void pointChanged(QPoint point);
};

#endif // SHIP_H
