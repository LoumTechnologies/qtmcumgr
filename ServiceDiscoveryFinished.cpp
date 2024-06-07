

#include "ServiceDiscoveryFinished.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {


void ServiceDiscoveryFinished::setEventType(QString newValue)
{
    this->_eventType = newValue;
}

QString &ServiceDiscoveryFinished::getEventType()
{
    return this->_eventType;
}
void ServiceDiscoveryFinished::setAddress(QString newValue)
{
    this->_address = newValue;
}

QString &ServiceDiscoveryFinished::getAddress()
{
    return this->_address;
}



}
