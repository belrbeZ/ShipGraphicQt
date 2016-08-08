#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QVector>
#include <QTextBrowser>
#include "way.h"
#include "randomvaluegenerator.h"

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

    //QString info;
signals:
    void shipsFieldsChanged();
    void sizeOfShipChanged(int);
    void sizeOfWayChanged(int);
    void updateShipsAndWays();
public slots:
    void addShip();
    void addWay(double oldx,double oldy,double newx,double  newy );
    void changeShipFieldsById(quint8 shipsNum,QVector<QString> *shipIDVec , QVector<qint16> *routingAngleVec , QVector<quint8> *shipVelocityVec ,  QVector<quint8> *visibilityScopeAngleVec, QVector<quint8> *visibilityScopeLengthVec ,QVector<quint64> *shipTotalDistanceVec , QVector<QTime> *routingTimeVec);
private slots:
    void on_MenuBut_clicked();
    void on_SliderSizeOfShip_valueChanged(int value);
    void on_SliderSizeOfWay_valueChanged(int value);
    void on_OnVisibleAndWayBut_clicked();
    void on_OffVisibleAndWayBut_clicked();
};

#endif // MAINWINDOW_H
