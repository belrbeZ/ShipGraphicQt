#ifndef WAY_H
#define WAY_H
#include <QLine>
#include <QObject>
#include <QDebug>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <windows.h>
class Way: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Way(QObject *parent = 0);
    QLine* line;
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // WAY_H
