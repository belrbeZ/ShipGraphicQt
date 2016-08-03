#include "ship.h"

quint8 Ship::shipsNum = 0;
int Ship::shipsSize=10;
Ship::Ship(QQuickItem *parent){
qDebug("good!");
    shipsNum++;
    m_image=new QImage();
    if(m_image->load(":/res/ship.png")){
        (*m_image).scaledToHeight(shipsSize);
        (*m_image).scaledToWidth(shipsSize);
    }
    else{
        qDebug("image null!");
    }
qDebug("good!");

    m_shipID = QString(shipsNum);
    m_routingAngle = random(minRoutingAngle, maxRoutingAngle);
    m_shipVelocity = random(minShipVelocity, maxShipVelocity);
    m_visibilityScopeAngle = random(minVisibilityScopeAngle, maxVisibilityScopeAngle);
    m_visibilityScopeLength = random(minVisibilityScopeLength, maxVisibilityScopeLength);
    m_shipTotalDistance = 0;
    m_routingTime = QTime(0,0,0);
    m_point.setX(random(minShipPoint,maxShipPoint));
    m_point.setY(random(minShipPoint,maxShipPoint));

    m_lines=0;
    numLines=0;


    internalTimer = new QTimer(this);
    connect(internalTimer, &QTimer::timeout, [=](){
        qDebug()<<"Timer!";
        //move();
        //paint(painter);
        update();
    });

    qDebug()<<"shipCreated: "<<shipsNum
    <<m_shipID<<" "
    <<m_routingAngle<<" "
    <<m_shipVelocity<<" "
    <<m_visibilityScopeAngle<<" "
    <<m_visibilityScopeLength<<" "
    <<m_shipTotalDistance<<" "
    <<m_routingTime<<" "
    <<m_point.x()<<" "<<m_point.y();
    internalTimer->start(50);
}

Ship::Ship(QString sID, qint16 rAngle, quint8 sVelocity, quint8 vScopeAngles,
           quint8 vScopeLength, quint64 sTotalDistance, QTime rTime){
    shipsNum++;
    m_image=new QImage("ship.png");
    if(m_image==NULL){
        qDebug("null!");
    }
    (*m_image).scaledToHeight(shipsSize);
    (*m_image).scaledToWidth(shipsSize);
    m_shipID = sID;
    m_routingAngle = rAngle;
    m_shipVelocity = sVelocity;
    m_visibilityScopeAngle = vScopeAngles;
    m_visibilityScopeLength = vScopeLength;
    m_shipTotalDistance = sTotalDistance;
    m_routingTime = rTime;
    m_point.setX(random(minShipPoint,maxShipPoint));
    m_point.setY(random(minShipPoint,maxShipPoint));

    m_lines=0;
    numLines=0;

    internalTimer = new QTimer(this);

    connect(internalTimer, &QTimer::timeout, [=](){
        qDebug()<<"Timer!";
        update();//paint()
    });
    internalTimer->start(50);
}

Ship::Ship(const Ship& other): m_shipID(other.m_shipID), m_routingAngle(other.m_routingAngle),
    m_shipVelocity(other.m_shipVelocity), m_visibilityScopeAngle(other.m_visibilityScopeAngle),
    m_visibilityScopeLength(other.m_visibilityScopeLength), m_shipTotalDistance(other.m_shipTotalDistance),
    m_routingTime(other.m_routingTime){

    m_point.setX(random(minShipPoint,maxShipPoint));
    m_point.setY(random(minShipPoint,maxShipPoint));
    shipsNum++;

    m_image=new QImage("ship.png");
    if(m_image==NULL){
        qDebug("null!");
    }
    (*m_image).scaledToHeight(shipsSize);
    (*m_image).scaledToWidth(shipsSize);

    m_lines=0;
    numLines=0;

    internalTimer = new QTimer(this);
    connect(internalTimer, &QTimer::timeout, [=](){
        qDebug()<<"Timer!";
        update();//paint()
    });
    internalTimer->start(50);
}

Ship::~Ship(){
    shipsNum--;
}

quint8 Ship:: getShipsNum(){
    return shipsNum;
}

QString Ship::shipID() const
{
    return m_shipID;
}

qint16 Ship::routingAngle() const
{
    return m_routingAngle;
}

quint8 Ship::shipVelocity() const
{
    return m_shipVelocity;
}

quint8 Ship::visibilityScopeAngle() const
{
    return m_visibilityScopeAngle;
}

quint8 Ship::visibilityScopeLength() const
{
    return m_visibilityScopeLength;
}

quint64 Ship::shipTotalDistance() const
{
    return m_shipTotalDistance;
}

QTime Ship::routingTime() const
{
    return m_routingTime;
}

QPoint Ship::point() const
{
    return m_point;
}

QLine* Ship::lines() const
{
    return m_lines;
}

void Ship::setShipID(QString shipID)
{
    if (m_shipID == shipID)
        return;

    m_shipID = shipID;
    emit shipIDChanged(shipID);
}

void Ship::setRoutingAngle(qint16 routingAngle)
{
    if (m_routingAngle == routingAngle)
        return;

    m_routingAngle = routingAngle;
    emit routingAngleChanged(routingAngle);
}

void Ship::setShipVelocity(quint8 shipVelocity)
{
    if (m_shipVelocity == shipVelocity)
        return;

    m_shipVelocity = shipVelocity;
    emit shipVelocityChanged(shipVelocity);
}

void Ship::setVisibilityScopeAngle(quint8 visibilityScopeAngle)
{
    if (m_visibilityScopeAngle == visibilityScopeAngle)
        return;

    m_visibilityScopeAngle = visibilityScopeAngle;
    emit visibilityScopeAngleChanged(visibilityScopeAngle);
}

void Ship::setVisibilityScopeLength(quint8 visibilityScopeLength)
{
    if (m_visibilityScopeLength == visibilityScopeLength)
        return;

    m_visibilityScopeLength = visibilityScopeLength;
    emit visibilityScopeLengthChanged(visibilityScopeLength);
}

void Ship::setShipTotalDistance(quint64 shipTotalDistance)
{
    if (m_shipTotalDistance == shipTotalDistance)
        return;

    m_shipTotalDistance = shipTotalDistance;
    emit shipTotalDistanceChanged(shipTotalDistance);
}

void Ship::setRoutingTime(QTime routingTime)
{
    if (m_routingTime == routingTime)
        return;

    m_routingTime = routingTime;
    emit routingTimeChanged(routingTime);
}

void Ship::setPoint(QPoint point)
{
    if (m_point == point)
        return;

    m_point = point;
    emit pointChanged(point);
}

void Ship::paint(QPainter *painter)
{
    qDebug()<<"paint";
    if(m_shipVelocity!=0){
        QColor brushColor(Qt::black);
        QBrush activeBrush(brushColor);
        //painter->begin(this);//viewport()
        painter->setPen(Qt::NoPen);
        painter->setRenderHints(QPainter::Antialiasing, true);

        painter->setBrush(activeBrush);
        if(m_image!=NULL){
            painter->drawImage(m_point,(*m_image));
        }
        else
            qDebug()<<"null";
        qDebug()<<"point:"<<m_point.x()<<" "<<m_point.y();
        int oldx = m_point.x();
        int oldy = m_point.y();
        move();
        if(numLines==0){
            m_lines=(QLine*)malloc((numLines+1)* sizeof(QLine));
        }
        else{
            m_lines=(QLine*)realloc(m_lines,(numLines+1)* sizeof(QLine));
        }
        m_lines[numLines].setLine(oldx,oldy,m_point.x(),m_point.y());
        painter->drawLine( m_lines[numLines]);
        numLines++;
        painter->end();

    }
    paintTriangle(painter);
    //QDebug("Painted");//<<"Painted";
    return;
}

void Ship::move()
{
    setPoint(QPoint((m_point.x()+m_shipVelocity*cos(m_routingAngle)),(m_point.y()+m_shipVelocity*sin(m_routingAngle))));
}

void Ship::paintTriangle(QPainter *painter)
{

    if(numLines==0){
        m_lines=(QLine*)malloc((numLines+3)* sizeof(QLine));
    }
    else{
        m_lines=(QLine*)realloc(m_lines,(numLines+3)* sizeof(QLine));
    }
    int x1,x2,x3,y1,y2,y3;
    x1=m_point.x();
    y1=m_point.y();
    x2=m_point.x()+m_shipVelocity*cos(m_routingAngle+10);
    y2=m_point.y()+m_shipVelocity*sin(m_routingAngle+10);
    x3=m_point.x()+m_shipVelocity*cos(m_routingAngle-10);
    y3=m_point.y()+m_shipVelocity*sin(m_routingAngle-10);

    m_lines[numLines].setPoints(QPoint(x1,y1),QPoint(x2,y2));
    painter->drawLine( m_lines[numLines]);
    m_lines[numLines+1].setPoints(QPoint(x2,y2),QPoint(x3,y3));
    painter->drawLine( m_lines[numLines+1]);
    m_lines[numLines+2].setPoints(QPoint(x3,y3),QPoint(x1,y1));
    painter->drawLine( m_lines[numLines+2]);
    numLines+=3;
}

void Ship::changeShipsSize()
{
    (*m_image).scaledToHeight(shipsSize);
    (*m_image).scaledToWidth(shipsSize);
}
