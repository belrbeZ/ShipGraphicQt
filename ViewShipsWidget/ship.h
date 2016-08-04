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
#include "ui_mainwindow.h"
#include "way.h"
class Ship : public QObject, public QGraphicsItem
{
public:
    explicit Ship(QObject *parent = 0);
    ~Ship();
    static int shipsSize;
    static int numShips;
signals:
    //void posChanged(Ui::MainWindow*,double oldx,double oldy,double newx,double  newy);
public slots:
    void slotGameTimer(); // Слот, который отвечает за обработку перемещения треугольника
    //void addWay(double oldx,double oldy,double newx,double  newy );
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal angle;
    QImage image;
    QVector<Way*> *ways;
    int numOfWays;
};

#endif // SHIP_H
