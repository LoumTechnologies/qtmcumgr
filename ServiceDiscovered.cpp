

#include "ServiceDiscovered.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {


void ServiceDiscovered::setEventType(QString newValue)
{
    this->_eventType = newValue;
}

QString &ServiceDiscovered::getEventType()
{
    return this->_eventType;
}
void ServiceDiscovered::setAddress(QString newValue)
{
    this->_address = newValue;
}

QString &ServiceDiscovered::getAddress()
{
    return this->_address;
}
void ServiceDiscovered::setService(QString newValue)
{
    this->_service = newValue;
}

QString &ServiceDiscovered::getService()
{
    return this->_service;
}
void ServiceDiscovered::setServiceDescription(QString newValue)
{
    this->_serviceDescription = newValue;
}

QString &ServiceDiscovered::getServiceDescription()
{
    return this->_serviceDescription;
}



}
