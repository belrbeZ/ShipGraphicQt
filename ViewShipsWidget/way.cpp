#include "way.h"

Way::Way(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    line = new QLine();
}

QRectF Way::boundingRect() const
{
    return QRectF(-25,-40,700,500);
}

void Way::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug()<<"drawLine";
    painter->setBrush(Qt::black);
    painter->drawLine(*line);
}
