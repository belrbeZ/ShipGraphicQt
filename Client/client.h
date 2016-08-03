#ifndef CLIENT_H
#define CLIENT_H
#define PORT_NUM 10

#include <QtNetwork>

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QObject *parent = 0);

private:
    void startConnection();

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
    quint8 visibilityScopeAnglel;
    quint8 visibilityScopeLength;
    quint64 shipTotalDistance;
    QTime routingTime;
};

#endif
