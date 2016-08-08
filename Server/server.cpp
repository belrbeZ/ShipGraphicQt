#include "server.h"
#include "ship.h"
#include "randomvaluegenerator.h"
#include <QDebug>

Server::Server(QObject *parent)
:   QObject(parent), tcpServer(0), networkSession(0)
{
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
    } else {
        sessionOpened();
    }

        connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendShipInfo()));
}

void Server::sessionOpened()
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

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::LocalHost, PORT_NUM)) {
        qDebug()<< "Unable to start the server: " << tcpServer->errorString();
        return;
    }
}

void Server::sendShipInfo()
{
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()),
            clientConnection, SLOT(deleteLater()));

    QList <Ship> ships;
    quint8 maxShipsNum = 4; //std::numeric_limits<quint8>::max()
    for(int i = 0; i < random(1,maxShipsNum); i++){
        ships.append(Ship());
    }

    QTime initialTime;
    initialTime.start();

    while(clientConnection->state() == QAbstractSocket::ConnectedState ){
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_0);
        out << (quint16)0;
        out << ships.size();
        for(quint8 i = 0; i < ships.size(); i++){
            out << ships[i].getShipID() << ships[i].getRoutingAngle() << ships[i].getShipVelocity() <<
                   ships[i].getVisibilityScopeAngle() << ships[i].getVisibilityScopeLength() <<
                   ships[i].getShipTotalDistance() << ships[i].getRoutingTime().addMSecs(initialTime.elapsed());

            // random changes in time
            quint8 diff = 30;
            //total distance change
            ships[i].setShipTotalDistance(ships[i].getShipTotalDistance() + ships[i].getShipVelocity());

            //routing angle change
            if(ships[i].getRoutingAngle() < Ship::maxRoutingAngle &&
                    ships[i].getRoutingAngle() > Ship::minRoutingAngle){
                ships[i].setRoutingAngle(random(ships[i].getRoutingAngle() - diff,
                                                ships[i].getRoutingAngle() + diff));
            }
            else{
                ships[i].setRoutingAngle(random(Ship:: minRoutingAngle , Ship::maxRoutingAngle));
            }

            //velocity change
            if(ships[i].getShipVelocity() < Ship::maxShipVelocity &&
                    ships[i].getShipVelocity() > Ship::minShipVelocity){
                ships[i].setShipVelocity(random(ships[i].getShipVelocity() - diff,
                                                ships[i].getShipVelocity() + diff));
            }
            else{
                ships[i].setShipVelocity(random(Ship::minShipVelocity, Ship::maxShipVelocity));
            }

            //visibility scope change
            if(ships[i].getVisibilityScopeLength() < Ship::maxVisibilityScopeLength
                    && ships[i].getVisibilityScopeLength() > Ship::minVisibilityScopeLength){
                ships[i].setVisibilityScopeLength(random(ships[i].getVisibilityScopeLength() - diff,
                                                         ships[i].getVisibilityScopeLength() + diff));
            }
            else{
                ships[i].setVisibilityScopeLength(random(Ship::minVisibilityScopeLength, Ship::maxVisibilityScopeLength));
            }
        }

        out.device()->seek(0);
        out << (quint16)(block.size() - sizeof(quint16));
        clientConnection->write(block);
        clientConnection->waitForBytesWritten();
        block.clear();
        QThread::msleep(1000);
    }
}

