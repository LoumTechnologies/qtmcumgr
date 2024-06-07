

#include "Disconnected.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {



Disconnected::~Disconnected()
{

}

bool Disconnected::TryLoad(const QJsonObject &jsonObject, Disconnected &result)
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
void Disconnected::setEventType(QString newValue)
{
    this->_eventType = newValue;
}
QString &Disconnected::getEventType()
{
    return this->_eventType.value();
}
void Disconnected::clearEventType()
{
    this->_eventType = {};
}

bool Disconnected::hasEventType() const
{
    return this->_eventType.has_value();
}
void Disconnected::setAddress(QString newValue)
{
    this->_address = newValue;
}
QString &Disconnected::getAddress()
{
    return this->_address.value();
}
void Disconnected::clearAddress()
{
    this->_address = {};
}

bool Disconnected::hasAddress() const
{
    return this->_address.has_value();
}



}

