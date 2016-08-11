#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(750,590);          /// Задаем размеры виджета, то есть окна
    this->setFixedSize(750,590);    /// Фиксируем размеры виджета

    scene = new QGraphicsScene();//(QRectF(-100, -100, -300, 300));   /// Инициализируем графическую сцену

    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView

    ui->graphicsView->setFixedWidth(702);
    ui->graphicsView->setFixedHeight(502);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали
    ui->graphicsView->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
    ui->graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету
//ui->graphicsView->setbac
    ui->widgetMenu->setVisible(false);
    ui->OnVisibleAndWayBut->setDisabled(true);

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

    numOfWays=0;
    ways=new QVector<Way*>();
    QObject::connect(ship,SIGNAL(posChanged(double,double,double,double)),this,SLOT(addWay(double,double,double,double)));
    QObject::connect(this,SIGNAL(sizeOfShipChanged(int)),ship,SLOT(changeSizeOfShip(int)));
    QObject::connect(this,SIGNAL(updateShipsAndWays()),ship,SLOT(updateShips()));

    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, ship, &Ship::slotGameTimer);
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
   // ways->at(numOfWays)->wayID=numOfWays;
    newWay->size=sqrt((newx-oldx)*(newx-oldx)+(newy-oldy)*(newy-oldy));
    scene->addItem(newWay);//(ways->at(numOfWays));
    QObject::connect(this,SIGNAL(sizeOfWayChanged(int)),newWay,SLOT(changeSizeOfWays(int)));
    QObject::connect(this,SIGNAL(updateShipsAndWays()),newWay,SLOT(updateWays()));
    numOfWays++;
}

void MainWindow::addShip()
{
    qDebug()<<"AddShips()";
    int x=0,y=0,minX=-340,maxX=340,minY=-240,maxY=240;

    for(int i=0;i<Ship::numShips;i++){
        x=random(minX,maxX);
        y=random(minY,maxY);
        Ship* newship = new Ship();      // Инициализируем треугольник
        ships->append(newship);
        scene->addItem(newship);
        newship->setPos(x,y);
    }
}

void MainWindow::changeShipFieldsById(quint8 shipsNum,QVector<QString> *shipIDVec , QVector<qint16> *routingAngleVec , QVector<quint8> *shipVelocityVec ,  QVector<quint8> *visibilityScopeAngleVec, QVector<quint8> *visibilityScopeLengthVec ,QVector<quint64> *shipTotalDistanceVec , QVector<QTime> *routingTimeVec)
{
    qInfo()<<"data taked, shipsNum="<<shipsNum<<"\nshipId=";
    if(shipsNum==0)return;
    //info="shipsNum="+shipsNum;
    ui->TextInfo->clear();
    ui->TextInfo->clearHistory();
    if(ships->size()==0&&Ship::numShips==0){
        Ship::numShips=shipsNum;
        addShip();
        for(int i=0;i<ships->size();i++){
//            info+= "\nTaked from server: shipID=" + shipIDVec->at(i)+ "routingAngle="  + routingAngleVec->at(i)+ "shipVelocity="  + shipVelocityVec->at(i) + "visibilityScopeAnglel=" + visibilityScopeAngleVec->at(i)+ "visibilityScopeLength="  +
//                visibilityScopeLengthVec->at(i) + "shipTotalDistance=" + shipTotalDistanceVec->at(i) + "routingTime=" + routingTimeVec->at(i).toString();
       //ui->TextInfo->setUpdatesEnabled(false);
            ui->TextInfo->insertPlainText("\nTaked from server: shipID=" + (QString)shipIDVec->at(i)+ "routingAngle="  + QString::number(routingAngleVec->at(i))+ "shipVelocity="  + QString::number(shipVelocityVec->at(i)) + "visibilityScopeAnglel=" + QString::number(visibilityScopeAngleVec->at(i))+ "visibilityScopeLength="  +
                                                      QString::number(visibilityScopeLengthVec->at(i)) + "shipTotalDistance=" +QString::number(shipTotalDistanceVec->at(i)) + "routingTime=" + routingTimeVec->at(i).toString());
            //ui->TextInfo->setUpdatesEnabled(true);
            ships->at(i)->setShipID(shipIDVec->at(i));
            ships->at(i)->setRoutingAngle(routingAngleVec->at(i));
            ships->at(i)->setShipVelocity(shipVelocityVec->at(i));
            ships->at(i)->setVisibilityScopeAngle(visibilityScopeAngleVec->at(i));
            ships->at(i)->setVisibilityScopeLength(visibilityScopeLengthVec->at(i));
            ships->at(i)->setShipTotalDistance(shipTotalDistanceVec->at(i));
            ships->at(i)->setRoutingTime(routingTimeVec->at(i));
            QObject::connect(ships->at(i),SIGNAL(posChanged(double,double,double,double)),this,SLOT(addWay(double,double,double,double)));
            QObject::connect(this,SIGNAL(shipsFieldsChanged()),ships->at(i) ,SLOT(shipsFieldsChangedAction()));
            QObject::connect(this,SIGNAL(sizeOfShipChanged(int)),ships->at(i),SLOT(changeSizeOfShip(int)));
            QObject::connect(this,SIGNAL(updateShipsAndWays()),ships->at(i),SLOT(updateShips()));
        }
        //ui->TextInfo->setText(info);
    }
    else{
        for(int i=0;i<Ship::numShips;i++){
            //if(ships->at(i)->getShipID()==shipID){
                //qInfo()<< "Vectors from server: shipID=" << shipIDVec->at(i)<< "routingAngle="  << routingAngleVec->at(i)<< "shipVelocity="  << shipVelocityVec->at(i) << "visibilityScopeAnglel=" << visibilityScopeAngleVec->at(i)<< "visibilityScopeLength="  <<
                //visibilityScopeLengthVec->at(i) << "shipTotalDistance=" << shipTotalDistanceVec->at(i) << "routingTime=" << routingTimeVec->at(i).toString();
//                qInfo()<< "Before change: shipID=" << ships->at(i)->getShipID()<< "routingAngle="  << ships->at(i)->getRoutingAngle()<< "shipVelocity="  << ships->at(i)->getShipVelocity() << "visibilityScopeAnglel=" << ships->at(i)->getVisibilityScopeAngle()<< "visibilityScopeLength="  <<
//                    ships->at(i)->getVisibilityScopeLength() << "shipTotalDistance=" << ships->at(i)->getShipTotalDistance() << "routingTime=" << ships->at(i)->getRoutingTime().toString();
            //ui->TextInfo->setUpdatesEnabled(false);
                qDebug()<<"text changeShipFieldsById";
            ui->TextInfo->insertPlainText("\nTaked from server: shipID=" + shipIDVec->at(i)+ "routingAngle="  + QString::number(routingAngleVec->at(i))+ "shipVelocity="  + QString::number(shipVelocityVec->at(i)) + "visibilityScopeAnglel=" + QString::number(visibilityScopeAngleVec->at(i))+ "visibilityScopeLength="  +
                                                           QString::number(visibilityScopeLengthVec->at(i)) + "shipTotalDistance=" +QString::number(shipTotalDistanceVec->at(i)) + "routingTime=" + routingTimeVec->at(i).toString());
                qDebug()<<"text changeShipFieldsById";
            //ui->TextInfo->setUpdatesEnabled(true);

                 ships->at(i)->setRoutingAngle(routingAngleVec->at(i));
                ships->at(i)->setShipVelocity(shipVelocityVec->at(i));
                ships->at(i)->setVisibilityScopeAngle(visibilityScopeAngleVec->at(i));
                ships->at(i)->setVisibilityScopeLength(visibilityScopeLengthVec->at(i));
                ships->at(i)->setShipTotalDistance(shipTotalDistanceVec->at(i));
                ships->at(i)->setRoutingTime(routingTimeVec->at(i));
qDebug()<<" changeShipFieldsById";
//                info+= "\nTaked from server: shipID=" + shipIDVec->at(i)+ "routingAngle="  + routingAngleVec->at(i)+ "shipVelocity="  + shipVelocityVec->at(i) + "visibilityScopeAnglel=" + visibilityScopeAngleVec->at(i)+ "visibilityScopeLength="  +
//                    visibilityScopeLengthVec->at(i) + "shipTotalDistance=" + shipTotalDistanceVec->at(i) + "routingTime=" + routingTimeVec->at(i).toString();

//                qInfo()<< "After change: shipID=" << ships->at(i)->getShipID()<< "routingAngle="  << ships->at(i)->getRoutingAngle()<< "shipVelocity="  << ships->at(i)->getShipVelocity() << "visibilityScopeAnglel=" << ships->at(i)->getVisibilityScopeAngle()<< "visibilityScopeLength="  <<
//                    ships->at(i)->getVisibilityScopeLength() << "shipTotalDistance=" << ships->at(i)->getShipTotalDistance() << "routingTime=" << ships->at(i)->getRoutingTime().toString();

                //ships->at(i)->shipsFieldsChangedAction();
                //break;
            //}
        }
        //ui->TextInfo->setText(info);
        emit shipsFieldsChanged();//?
    }

}

void MainWindow::on_MenuBut_clicked()
{
    if(ui->widgetMenu->isVisible())
        ui->widgetMenu->setVisible(false);
    else
        ui->widgetMenu->setVisible(true);
}

void MainWindow::on_SliderSizeOfShip_valueChanged(int value)
{
    emit sizeOfShipChanged(value);
}

void MainWindow::on_SliderSizeOfWay_valueChanged(int value)
{
    emit sizeOfWayChanged(value);
}

void MainWindow::on_OnVisibleAndWayBut_clicked()
{
    Ship::visibleAndWay=true;
    ui->OffVisibleAndWayBut->setDisabled(false);
    ui->OnVisibleAndWayBut->setDisabled(true);
    emit updateShipsAndWays();
}

void MainWindow::on_OffVisibleAndWayBut_clicked()
{
    Ship::visibleAndWay=false;
    ui->OnVisibleAndWayBut->setDisabled(false);
    ui->OffVisibleAndWayBut->setDisabled(true);
    emit updateShipsAndWays();
}
