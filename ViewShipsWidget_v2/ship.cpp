#include "ship.h"
//#include "ui_mainwindow.h"
#define PI 3.14159265
int Ship::shipsSize=20;
int Ship::numShips=0;
bool Ship::visibleAndWay=true;
Ship::Ship(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    if(!image.load(":/res/ship.png"))
        qDebug()<<"Image is null!";
    else{
        qDebug()<<"scaling to "<<shipsSize;
        image=image.scaledToWidth(shipsSize);
    }

    angle = 0;     // Задаём угол поворота графического объекта
    setRotation(angle);     // Устанавилваем угол поворота графического объекта
    shipID="0";
    visibilityScopeLength=20;
    visibilityScopeAngle=89;
}

Ship::~Ship()
{

}

QRectF Ship::boundingRect() const
{

    double diagon = sqrt(shipsSize*shipsSize+image.height()*image.height());
    double visib=visibilityScopeLength*2/cos(visibilityScopeAngle * PI / 360);
    return QRectF(-((diagon<visib)?visib:diagon),-((diagon<visib)?visib:diagon),2*((diagon<visib)?visib:diagon),2*((diagon<visib)?visib:diagon));//(-25,-40,700,500);  /// Ограничиваем область, в которой лежит треугольник
    //return QRectF(-(image.height()+),-shipsSize,shipsSize+visibilityScopeAngle,image.height());
}

void Ship::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug()<<"paint:"<<shipID;
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawImage(-shipsSize/2,0,image);//-shipsSize/2+shipsSize/20,shipsSize/2

    painter->drawText(shipsSize/2+5,5,shipID);

    if(visibleAndWay){
            QPolygon polygon;   /// Используем класс полигона, чтобы отрисовать треугольник
            /// Помещаем координаты точек в полигональную модель
            polygon << QPoint(0,0) << QPoint(-visibilityScopeLength*2*tan(visibilityScopeAngle* PI / 360),-visibilityScopeLength*2/cos(visibilityScopeAngle* PI / 360)) << QPoint(visibilityScopeLength*2*tan(visibilityScopeAngle* PI / 360),-visibilityScopeLength*2/cos(visibilityScopeAngle* PI / 360));
            painter->setBrush(Qt::red);     /// Устанавливаем кисть, которой будем отрисовывать объект
            painter->drawPolygon(polygon);  /// Рисуем треугольник по полигональной модели
    }
    else{
        qDebug()<<"visibleAndWay==false";
    }
//    painter->setBrush(Qt::NoBrush);
//        double diagon = sqrt(shipsSize*shipsSize+image.height()*image.height());
//        double visib=visibilityScopeLength/cos(visibilityScopeAngle* PI / 180);
//        painter->drawRect(QRectF(-((diagon<visib)?visib:diagon),-((diagon<visib)?visib:diagon),2*((diagon<visib)?visib:diagon),2*((diagon<visib)?visib:diagon)));
//       double heightTriangl=sqrt(4*visibilityScopeLength/cos(visibilityScopeAngle* PI / 180)*visibilityScopeLength/cos(visibilityScopeAngle* PI / 180));
//    painter->drawRect(QRectF(-((image.height()>heightTriangl)?image.height():heightTriangl),-(shipsSize+visibilityScopeAngle),shipsSize+visibilityScopeAngle,((image.height()>heightTriangl)?image.height():heightTriangl)));

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Ship::slotGameTimer()
{
    /* Поочерёдно выполняем проверку на нажатие клавиш
     * с помощью функции асинхронного получения состояния клавиш,
     * которая предоставляется WinAPI
     * */

    if(GetAsyncKeyState(VK_LEFT)){
        angle -= 10;        // Задаём поворот на 10 градусов влево
        setRotation(angle); // Поворачиваем объект

    }
    else if(GetAsyncKeyState(VK_RIGHT)){
        angle += 10;        // Задаём поворот на 10 градусов вправо
        setRotation(angle); // Поворачиваем объект
    }
    else if(GetAsyncKeyState(VK_UP)){
        double oldx = this->pos().x();
        double oldy = this->pos().y();
        qDebug()<<this->pos().x()<<" "<<this->pos().y();
        setPos(mapToParent(0, -5));     /* Продвигаем объект на 5 пискселей вперёд
                                         * перетранслировав их в координатную систему
                                         * графической сцены
                                         * */

        qDebug()<<this->pos().x()<<" "<<this->pos().y();
        emit posChanged(oldx,oldy,this->pos().x(),this->pos().y());
    }
    else if(GetAsyncKeyState(VK_DOWN)){
        double oldx = this->pos().x();
        double oldy = this->pos().y();
        qDebug()<<this->pos().x()<<" "<<this->pos().y();
        setPos(mapToParent(0, 5));      /* Продвигаем объект на 5 пискселей назад
                                         * перетранслировав их в координатную систему
                                         * графической сцены
                                         * */
        qDebug()<<this->pos().x()<<" "<<this->pos().y();
        emit  posChanged(oldx,oldy,this->pos().x(),this->pos().y());
    }
    else{
    }
    /* Проверка выхода за границы поля
     * Если объект выходит за заданные границы, то возвращаем его назад
     * */
    if(this->x() - shipsSize/2 < -350){
        this->setX(-340);       // слева
    }
    if(this->x() + shipsSize/2 > 350){
        this->setX(340);        // справа
    }

    if(this->y() - shipsSize/2 < -250){
        this->setY(-240);       // сверху
    }
    if(this->y() + shipsSize/2 > 250){
        this->setY(240);        // снизу
    }
}
void Ship::shipsFieldsChangedAction()
{
    double oldx = this->pos().x();
    double oldy = this->pos().y();
    qDebug()<<"\nShip"<<getShipID()<<":fieldes changed!";
    setRotation(routingAngle);
    setPos(mapToParent(0, -shipVelocity));

    if(this->x() - shipsSize/2 < -350){
        qInfo()<<"exit from borders";
        this->setX(-340);       // слева
    }
     if(this->x() + shipsSize/2 > 350){
        qInfo()<<"exit from borders";
        this->setX(340);        // справа
    }

     if(this->y() - shipsSize/2 < -250){
        qInfo()<<"exit from borders";
        this->setY(-240);       // сверху
    }
     if(this->y() + shipsSize/2 > 250){
        qInfo()<<"exit from borders";
        this->setY(240);        // снизу
    }

        emit  posChanged(oldx,oldy,this->pos().x(),this->pos().y());
    //...timer start...
}

void Ship::changeSizeOfShip(int newSize)
{

    if(image.isNull())
        qDebug()<<"Image is null!";
    else{
        qDebug()<<"scaling from "<< shipsSize <<" to "<<newSize;
        shipsSize=newSize;
        QImage imageNew;
        if(imageNew.load(":/res/ship.png")){
            //image=imageNew.scaledToHeight(shipsSize/2, Qt::TransformationMode::FastTransformation);
            image=imageNew.scaledToWidth(shipsSize);
            update();
        }
    }
}

void Ship::updateShips()
{
    update();
}

QString Ship:: getShipID(){
    return shipID;
}

qint16 Ship:: getRoutingAngle(){
    return routingAngle;
}

quint8 Ship::getShipVelocity(){
    return shipVelocity;
}

quint8 Ship::getVisibilityScopeAngle(){
    return visibilityScopeAngle;
}

quint8 Ship::getVisibilityScopeLength(){
    return visibilityScopeLength;
}

quint64 Ship::getShipTotalDistance(){
    return shipTotalDistance;
}

QTime Ship::getRoutingTime(){
    return routingTime;
}

void Ship::setShipID(QString sID){
    shipID = sID;

}

void Ship::setRoutingAngle(qint16 rAngle){
    routingAngle = rAngle;
}

void Ship::setShipVelocity(quint8 sVelocity){
    shipVelocity = sVelocity;
}

void Ship::setVisibilityScopeAngle(quint8 vScopeAngle){
    visibilityScopeAngle = vScopeAngle;
}

void Ship::setVisibilityScopeLength(quint8 vScopeLength){
    visibilityScopeLength = vScopeLength;
}

void Ship::setShipTotalDistance(quint64 sTotalDistance){
    shipTotalDistance = sTotalDistance;
}

void Ship::setRoutingTime(QTime rTime){
    routingTime = rTime;
}
