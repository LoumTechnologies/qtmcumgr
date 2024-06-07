

#include "ServiceDiscovered.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {



ServiceDiscovered::~ServiceDiscovered()
{

}

bool ServiceDiscovered::TryLoad(const QJsonObject &jsonObject, ServiceDiscovered &result)
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

    if (jsonObject.contains("service"))
    {

        if (!jsonObject["service"].isString())
        {
            return false;
        }

        result.setService(jsonObject["service"].toString());

    }

    if (jsonObject.contains("serviceDescription"))
    {

        if (!jsonObject["serviceDescription"].isString())
        {
            return false;
        }

        result.setServiceDescription(jsonObject["serviceDescription"].toString());

    }


    return true;
}
void ServiceDiscovered::setEventType(QString newValue)
{
    this->_eventType = newValue;
}
QString &ServiceDiscovered::getEventType()
{
    return this->_eventType.value();
}
void ServiceDiscovered::clearEventType()
{
    this->_eventType = {};
}

bool ServiceDiscovered::hasEventType() const
{
    return this->_eventType.has_value();
}
void ServiceDiscovered::setAddress(QString newValue)
{
    this->_address = newValue;
}
QString &ServiceDiscovered::getAddress()
{
    return this->_address.value();
}
void ServiceDiscovered::clearAddress()
{
    this->_address = {};
}

bool ServiceDiscovered::hasAddress() const
{
    return this->_address.has_value();
}
void ServiceDiscovered::setService(QString newValue)
{
    this->_service = newValue;
}
QString &ServiceDiscovered::getService()
{
    return this->_service.value();
}
void ServiceDiscovered::clearService()
{
    this->_service = {};
}

bool ServiceDiscovered::hasService() const
{
    return this->_service.has_value();
}
void ServiceDiscovered::setServiceDescription(QString newValue)
{
    this->_serviceDescription = newValue;
}
QString &ServiceDiscovered::getServiceDescription()
{
    return this->_serviceDescription.value();
}
void ServiceDiscovered::clearServiceDescription()
{
    this->_serviceDescription = {};
}

bool ServiceDiscovered::hasServiceDescription() const
{
    return this->_serviceDescription.has_value();
}



}

