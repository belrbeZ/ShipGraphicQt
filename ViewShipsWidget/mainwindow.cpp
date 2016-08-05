#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1000,600);          /// Задаем размеры виджета, то есть окна
    this->setFixedSize(1000,600);    /// Фиксируем размеры виджета

    scene = new QGraphicsScene();   /// Инициализируем графическую сцену

    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setFixedWidth(700);
    ui->graphicsView->setFixedHeight(500);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали

    scene->setSceneRect(-350,-250,700,500); /// Устанавливаем область графической сцены

    scene->addLine(-350,0,350,0,QPen(Qt::black));   /// Добавляем горизонтальную линию через центр
    scene->addLine(0,-250,0,250,QPen(Qt::black));   /// Добавляем вертикальную линию через центр

    /* Дополнительно нарисуем органичение территории в графической сцене */
    scene->addLine(-350,-250, 350,-250, QPen(Qt::black));
    scene->addLine(-350, 250, 350, 250, QPen(Qt::black));
    scene->addLine(-350,-250,-350, 250, QPen(Qt::black));
    scene->addLine( 350,-250, 350, 250, QPen(Qt::black));

    ship=new Ship();
    scene->addItem(ship);   /// Добавляем на сцену треугольник
    ship->setPos(0,0);
    ships=new QVector<Ship*>();
    addShip();
    numOfWays=0;
    ways=new QVector<Way*>();
    //QObject::connect(ship,SIGNAL(sgnPosChanged()),this,SLOT(addWay2()));
    QObject::connect(ship,SIGNAL(posChanged(double,double,double,double)),this,SLOT(addWay(double,double,double,double)));

    for(int i=0;i<ships->size();i++)
        QObject::connect(ships->at(i),SIGNAL(posChanged(double,double,double,double)),this,SLOT(addWay(double,double,double,double)));
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, ship, &Ship::slotGameTimer);
    //QObject::connect(timer, &QTimer::timeout, ship, &Ship::slotGameTimer);
//    connect(timer, &QTimer::timeout, ways, &Ship::slotGameTimer);
    timer->start(1000 / 50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addWay(double oldx,double oldy,double newx,double  newy )
{
    qDebug()<<"add line";
    Way* newWay = new Way();
    newWay->line->setLine(oldx,oldy,newx,newy);
    ways->append(newWay);

    scene->addItem(newWay);//(ways->at(numOfWays));
    //newWay->setPos(0,0);
    numOfWays++;
}

void MainWindow::addShip()
{
    int x=0,y=0;
    for(int i=0;i<Ship::numShips;i++){
        x+=10;
        y+=10;
        Ship* newship = new Ship();      // Инициализируем треугольник
        ships->append(newship);
        scene->addItem(newship);
        newship->setPos(x,y);
    }
}
