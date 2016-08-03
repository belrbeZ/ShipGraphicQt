#include "ship.h"
#include "randomvaluegenerator.h"

quint8 Ship::shipsNum = 0;

Ship::Ship(){
    shipsNum++;
    shipID = QString(shipsNum);
    routingAngle = random(minRoutingAngle, maxRoutingAngle);
    shipVelocity = random(minShipVelocity, maxShipVelocity);
    visibilityScopeAngle = random(minVisibilityScopeAngle, maxVisibilityScopeAngle);
    visibilityScopeLength = random(minVisibilityScopeLength, maxVisibilityScopeLength);
    shipTotalDistance = 0;
    routingTime = QTime(0,0,0);
}

Ship::Ship(QString sID, qint16 rAngle, quint8 sVelocity, quint8 vScopeAngles,
           quint8 vScopeLength, quint64 sTotalDistance, QTime rTime){
    shipsNum++;
    shipID = sID;
    routingAngle = rAngle;
    shipVelocity = sVelocity;
    visibilityScopeAngle = vScopeAngles;
    visibilityScopeLength = vScopeLength;
    shipTotalDistance = sTotalDistance;
    routingTime = rTime;
}

Ship::Ship(const Ship& other): shipID(other.shipID), routingAngle(other.routingAngle),
    shipVelocity(other.shipVelocity), visibilityScopeAngle(other.visibilityScopeAngle),
    visibilityScopeLength(other.visibilityScopeLength), shipTotalDistance(other.shipTotalDistance),
    routingTime(other.routingTime){
    shipsNum++;
}

Ship::~Ship(){
    shipsNum--;
}

quint8 Ship:: getShipsNum(){
    return shipsNum;
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
