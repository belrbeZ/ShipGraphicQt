#include "client.h"
#include <QDebug>

Client::Client(QObject *parent)
:   QObject(parent), networkSession(0)
{
    tcpSocket = new QTcpSocket(this);

    shipIDVec=new QVector<QString>();
    routingAngleVec=new QVector<qint16>();
    shipVelocityVec=new QVector<quint8>();
    visibilityScopeAngleVec=new QVector<quint8>();
    visibilityScopeLengthVec=new QVector<quint8>();
    shipTotalDistanceVec=new QVector<quint64>();
    routingTimeVec=new QVector<QTime>();


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
        in >> shipID >> routingAngle >> shipVelocity >> visibilityScopeAngle
                >> visibilityScopeLength >> shipTotalDistance >> routingTime;

        shipIDVec->append(shipID);
        routingAngleVec->append(routingAngle);
        shipVelocityVec->append(shipVelocity);
        visibilityScopeAngleVec->append(visibilityScopeAngle);
        visibilityScopeLengthVec->append(visibilityScopeLength);
        shipTotalDistanceVec->append(shipTotalDistance);
        routingTimeVec->append(routingTime);
        qInfo()<< "-----------------------------\nTaked from server: shipID=" << shipID<< "routingAngle="  << routingAngle<< "shipVelocity="  << shipVelocity << "visibilityScopeAnglel=" << visibilityScopeAngle<< "visibilityScopeLength="  <<
            visibilityScopeLength << "shipTotalDistance=" << shipTotalDistance << "routingTime=" << routingTime.toString();

    }
    emit infoFromServerTaked(shipsNum,shipIDVec , routingAngleVec , shipVelocityVec , visibilityScopeAngleVec
                             , visibilityScopeLengthVec , shipTotalDistanceVec , routingTimeVec);
    shipIDVec->clear();
    routingAngleVec->clear();
    shipVelocityVec->clear();
    visibilityScopeAngleVec->clear();
    visibilityScopeLengthVec->clear();
    shipTotalDistanceVec->clear();
    routingTimeVec->clear();
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
