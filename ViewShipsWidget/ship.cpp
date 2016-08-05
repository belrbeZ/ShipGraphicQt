#include "ship.h"
int Ship::shipsSize=50;
int Ship::numShips=5;
Ship::Ship(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    if(!image.load(":/res/ship.png"))
        qDebug()<<"null!";
    else{
        image.scaledToHeight(shipsSize);
        image.scaledToWidth(shipsSize);
    }

    angle = 0;     // Задаём угол поворота графического объекта
    setRotation(angle);     // Устанавилваем угол поворота графического объекта
    //numOfWays=0;
    //ways=new QVector<Way*>();
    //ways=(QLine*)malloc((numOfWays+1)* sizeof(QLine));

}

Ship::~Ship()
{

}

QRectF Ship::boundingRect() const
{//(shipsSize>80 ? shipsSize : 80)

    //double diagon = sqrt(2*shipsSize*shipsSize);
    return QRectF(-25,-40,700,500);//(-25,-40,2*diagon/3+2*diagon,diagon+2*diagon);   /// Ограничиваем область, в которой лежит треугольник
}

void Ship::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug()<<"paint";
    painter->drawImage(-shipsSize/2+shipsSize/20,shipsSize/2,image);
        QPolygon polygon;   /// Используем класс полигона, чтобы отрисовать треугольник
        /// Помещаем координаты точек в полигональную модель
        polygon << QPoint(0,shipsSize/2) << QPoint(shipsSize/3,-shipsSize/2) << QPoint(-shipsSize/3,-shipsSize/2);
        painter->setBrush(Qt::red);     /// Устанавливаем кисть, которой будем отрисовывать объект
        painter->drawPolygon(polygon);  /// Рисуем треугольник по полигональной модели
//        qDebug()<<ways->size();
//        if(ways->size()!=0)
//            for(int i=0;i<ways->size();i++){
//                    qDebug()<<ways->at(i)->line->x1()<<" "<<ways->at(i)->line->x2()<<" "<<ways->at(i)->line->y1()<<" "<<ways->at(i)->line->y2();
//                    painter->drawLine(*ways->at(i)->line);
//            }

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
//        if(ways->size()!=0)
//            for(int i=0;i<ways->size();i++){
//                    ways->at(i)->line->setLine();//cos(angle)
//            }
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
//        Way* newWay = new Way();
//       newWay->line->setLine(oldx,oldy,this->pos().x(),this->pos().y());
//       ways->append(newWay);
        //emit sgnPosChanged();
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

//        Way* newWay = new Way();
//        newWay->line->setLine(oldx,oldy,this->pos().x(),this->pos().y());
//        ways->append(newWay);
        //emit sgnPosChanged();
        emit  posChanged(oldx,oldy,this->pos().x(),this->pos().y());
    }
    else{
//        angle+=10;
//        setRotation(angle);
//        setPos(mapToParent(0, 5));
    }
    /* Проверка выхода за границы поля
     * Если объект выходит за заданные границы, то возвращаем его назад
     * */
    if(this->x() - 10 < -250){
        this->setX(-240);       // слева
    }
    if(this->x() + 10 > 250){
        this->setX(240);        // справа
    }

    if(this->y() - 10 < -250){
        this->setY(-240);       // сверху
    }
    if(this->y() + 10 > 250){
        this->setY(240);        // снизу
    }
}

//void Ship::addWay(double oldx,double oldy,double newx,double  newy )
//{
//    ways=(QLine*)realloc(ways,(numOfWays+1)* sizeof(QLine));

//    ways[numOfWays].setLine(oldx,oldy,newx,newy);
//    numOfWays++;
//}
