#include "ship.h"

Ship::Ship()
{
    shipsNum++;
    m_image=new QImage();
    if(m_image->load(":/res/ship.png")){
        (*m_image).scaledToHeight(shipsSize);
        (*m_image).scaledToWidth(shipsSize);
    }
    else{
        qDebug("image null!");
    }
    m_shipID = QString(shipsNum);
    m_routingAngle = random(minRoutingAngle, maxRoutingAngle);
    m_shipVelocity = random(minShipVelocity, maxShipVelocity);
    m_visibilityScopeAngle = random(minVisibilityScopeAngle, maxVisibilityScopeAngle);
    m_visibilityScopeLength = random(minVisibilityScopeLength, maxVisibilityScopeLength);
    m_shipTotalDistance = 0;
    m_routingTime = QTime(0,0,0);
    m_point.setX(random(minShipPoint,maxShipPoint));
    m_point.setY(random(minShipPoint,maxShipPoint));

    m_ways=0;
    numWays=0;

    m_triangle=new QLine[3];
    int x1,x2,x3,y1,y2,y3;
    x1=m_point.x();
    y1=m_point.y();
    x2=m_point.x()+m_shipVelocity*cos(m_routingAngle+10);
    y2=m_point.y()+m_shipVelocity*sin(m_routingAngle+10);
    x3=m_point.x()+m_shipVelocity*cos(m_routingAngle-10);
    y3=m_point.y()+m_shipVelocity*sin(m_routingAngle-10);

    m_lines[0].setPoints(QPoint(x1,y1),QPoint(x2,y2));
    m_lines[1].setPoints(QPoint(x2,y2),QPoint(x3,y3));
    m_lines[2].setPoints(QPoint(x3,y3),QPoint(x1,y1));

}

void Ship::step()
{
    int oldx = m_point.x();
    int oldy = m_point.y();
    setPoint(QPoint((m_point.x()+m_shipVelocity*cos(m_routingAngle)),(m_point.y()+m_shipVelocity*sin(m_routingAngle))));
    if(numWays==0){
        m_ways=(QLine*)malloc((numWays+1)* sizeof(QLine));
    }
    else{
        m_ways=(QLine*)realloc(m_lines,(numWays+1)* sizeof(QLine));
    }
    m_ways[numWays].setLine(oldx,oldy,m_point.x(),m_point.y());
    changeTriangle();
    numWays++;
}

void Ship::changeTriangle()
{
    int x1,x2,x3,y1,y2,y3;
    x1=m_point.x();
    y1=m_point.y();
    x2=m_point.x()+m_shipVelocity*cos(m_routingAngle+10);
    y2=m_point.y()+m_shipVelocity*sin(m_routingAngle+10);
    x3=m_point.x()+m_shipVelocity*cos(m_routingAngle-10);
    y3=m_point.y()+m_shipVelocity*sin(m_routingAngle-10);

    m_triangle[0].setPoints(QPoint(x1,y1),QPoint(x2,y2));
    m_triangle[1].setPoints(QPoint(x2,y2),QPoint(x3,y3));
    m_triangle[2].setPoints(QPoint(x3,y3),QPoint(x1,y1));
}

//void Ship::paintEvent(QPaintEvent *ev)
//{
//    QPainter p;
//    p.begin(this);
//    p.setPen(Qt::black);
//    p.drawImage(m_point,(*m_image));
//    p.drawEllipse(ev->rect());
//    p.end();

//    ev->accept();
//}
