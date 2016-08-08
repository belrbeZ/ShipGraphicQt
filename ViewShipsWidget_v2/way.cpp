#include "way.h"
int Way::waySize=3;
Way::Way(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    line = new QLine();
    color=(Qt::red);
    size=1;
    //setRotation(0);
}

QRectF Way::boundingRect() const
{
    double diagon=sqrt(2*size*size);
    return QRectF(-diagon,-diagon,2*diagon,2*diagon);
}

void Way::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(Ship::visibleAndWay){
        //qDebug()<<"drawLine";
        painter->setRenderHint(QPainter::Antialiasing, true);
        //painter->setBrush(color);
        painter->setPen(QPen(Qt::black, waySize, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));

//        double diagon=sqrt(2*waySize*waySize);
//        painter->drawRect(QRectF(-diagon,-diagon,2*diagon,2*diagon));

        painter->drawLine(*line);
    }
    else{
        //qDebug()<<"visibleAndWay==false";
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Way::changeSizeOfWays(int newSize)
{
    //qDebug()<<"changing size of way number "<<wayID;
    waySize=newSize;
    update();
}

void Way::updateWays()
{
    update();
}
