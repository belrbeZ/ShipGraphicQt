#include "client.h"
#include <QDebug>

Client::Client(QObject *parent)
:   QObject(parent), networkSession(0)
{
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readShipInfo()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError()));

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        qInfo() << "Opening network session.";
        networkSession->open();
    }
    else {
            sessionOpened();
        }
}

void Client::startConnection()
{
    tcpSocket->connectToHost(QHostAddress::LocalHost,PORT_NUM);
    blockSize = 0;
}

void Client::readShipInfo()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> blockSize;
    }

    if (tcpSocket->bytesAvailable() < blockSize)
        return;

    //QString nextShipInfo;
    //in >> nextShipInfo;

    /*if (nextShipInfo == currentShipInfo) {
        QTimer::singleShot(0, this, SLOT(requestNewFortune()));
        //возможно добавить проверку на корректность сгенерированных координат
        return;
    }*/

    //currentShipInfo = nextShipInfo;
    //qInfo() << currentShipInfo;

    in >> shipsNum;
    for(quint8 i = 0; i < shipsNum; i++){
        in >> shipID >> routingAngle >> shipVelocity >> visibilityScopeAnglel
                >> visibilityScopeLength >> shipTotalDistance >> routingTime;
        qInfo() << shipID << routingAngle << shipVelocity << visibilityScopeAnglel <<
            visibilityScopeLength << shipTotalDistance << routingTime.toString();
    }
    qInfo() << '\n';
    blockSize = 0;
}

void Client::displayError()
{
    qDebug() << "The following error occurred: " << tcpSocket->errorString();
}

void Client::sessionOpened()
{
    // Save the used configuration
    if (networkSession) {
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
    }
    startConnection();
}
