#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QVector>
#include "ship.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene  *scene;     /// Объявляем графическую сцену
    QVector<Ship*> *ships;  /// и треугольник
    Ship *ship;
    QTimer          *timer;
    QVector<Way*> *ways;
    int numOfWays;
public slots:
    void addShip();
    void addWay(double oldx,double oldy,double newx,double  newy );
};

#endif // MAINWINDOW_H
