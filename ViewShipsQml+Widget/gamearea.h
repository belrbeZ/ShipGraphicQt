#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <QWidget>
#include <QGraphicsScene>

#include <triangle.h>

namespace Ui {
class GameArea;
}
class GameArea : public QWidget
{
    Q_OBJECT
public:
    explicit GameArea(QWidget *parent = 0);
    ~GameArea();
signals:

public slots:

private:
    Ui::Widget      *ui;
    QGraphicsScene  *scene;     // Объявляем графическую сцену
    Triangle        *triangle;  // и треугольник
};

#endif // GAMEAREA_H
