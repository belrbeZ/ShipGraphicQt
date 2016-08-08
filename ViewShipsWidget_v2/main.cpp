#include "mainwindow.h"
#include <QApplication>
#include "client.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w=new MainWindow();
    Client *client=new Client();
    QObject::connect(client,SIGNAL(infoFromServerTaked(quint8 ,QVector<QString>*  , QVector<qint16> *, QVector<quint8> * ,  QVector<quint8> * , QVector<quint8> * , QVector<quint64> * , QVector<QTime> *)),
                     w,SLOT(changeShipFieldsById(quint8 ,QVector<QString>*  , QVector<qint16>*  , QVector<quint8>*  ,  QVector<quint8>* , QVector<quint8> * , QVector<quint64> * , QVector<QTime>* )));
    w->show();

    return a.exec();
}
