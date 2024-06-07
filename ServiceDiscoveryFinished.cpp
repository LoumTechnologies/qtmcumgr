

#include "ServiceDiscoveryFinished.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {



ServiceDiscoveryFinished::~ServiceDiscoveryFinished()
{

}

bool ServiceDiscoveryFinished::TryLoad(const QJsonObject &jsonObject, ServiceDiscoveryFinished &result)
{

    if (jsonObject.contains("eventType"))
    {

        if (!jsonObject["eventType"].isString())
        {
            return false;
        }

        result.setEventType(jsonObject["eventType"].toString());

    }

    if (jsonObject.contains("address"))
    {

        if (!jsonObject["address"].isString())
        {
            return false;
        }

        result.setAddress(jsonObject["address"].toString());

    }


    return true;
}
void ServiceDiscoveryFinished::setEventType(QString newValue)
{
    this->_eventType = newValue;
}
QString &ServiceDiscoveryFinished::getEventType()
{
    return this->_eventType.value();
}
void ServiceDiscoveryFinished::clearEventType()
{
    this->_eventType = {};
}

bool ServiceDiscoveryFinished::hasEventType() const
{
    return this->_eventType.has_value();
}
void ServiceDiscoveryFinished::setAddress(QString newValue)
{
    this->_address = newValue;
}
QString &ServiceDiscoveryFinished::getAddress()
{
    return this->_address.value();
}
void ServiceDiscoveryFinished::clearAddress()
{
    this->_address = {};
}

bool ServiceDiscoveryFinished::hasAddress() const
{
    return this->_address.has_value();
}



}

