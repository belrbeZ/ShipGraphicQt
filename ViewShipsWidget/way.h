#ifndef WAY_H
#define WAY_H
#include <QLine>
#include <QObject>
//#include <QGraphicsItem>
//#include <QPainter>
class Way: public QObject//, public QGraphicsItem
{
public:
    explicit Way(QObject *parent = 0);
    QLine* line;
//protected:
    //QRectF boundingRect() const;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // WAY_H
