#ifndef CLIENT_H
#define CLIENT_H
#define PORT_NUM 10

#include <QtNetwork>
#include <QObject>
class Client : public QObject
{
    Q_OBJECT

public:
    Client(QObject *parent = 0);

private:
    void startConnection();
signals:

    void infoFromServerTaked(quint8 shipsNum,QVector<QString> *shipIDVec , QVector<qint16> *routingAngleVec , QVector<quint8> *shipVelocityVec ,  QVector<quint8> *visibilityScopeAngleVec, QVector<quint8> *visibilityScopeLengthVec ,QVector<quint64> *shipTotalDistanceVec , QVector<QTime> *routingTimeVec);
private slots:
    void readShipInfo();
    void displayError();
    void sessionOpened();

private:
    QTcpSocket *tcpSocket;
    QNetworkSession *networkSession;
    quint16 blockSize;

    quint8 shipsNum;

    QString shipID;
    qint16 routingAngle;
    quint8 shipVelocity;
    quint8 visibilityScopeAngle;
    quint8 visibilityScopeLength;
    quint64 shipTotalDistance ;
    QTime routingTime;


    QVector<QString> *shipIDVec;
    QVector<qint16> *routingAngleVec;
    QVector<quint8> *shipVelocityVec;
    QVector<quint8> *visibilityScopeAngleVec;
    QVector<quint8> *visibilityScopeLengthVec;
    QVector<quint64> *shipTotalDistanceVec;
    QVector<QTime> *routingTimeVec;
};

#endif
