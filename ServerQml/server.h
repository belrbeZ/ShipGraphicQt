#ifndef SERVER
#define SERVER
#define PORT_NUM 10

#include <QtNetwork>

class Server : public QObject
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
signals:
    void sendToQml(int count);
public slots:
    void recieveFromQml();
private slots:
    void sessionOpened();
    void sendShipInfo();
private:
    QTcpServer *tcpServer;
    QNetworkSession *networkSession;
    int count;
};

#endif // SERVER

