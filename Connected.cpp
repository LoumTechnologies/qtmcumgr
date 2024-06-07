

#include "Connected.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {



Connected::~Connected()
{

}

bool Connected::TryLoad(const QJsonObject &jsonObject, Connected &result)
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
void Connected::setEventType(QString newValue)
{
    this->_eventType = newValue;
}
QString &Connected::getEventType()
{
    return this->_eventType.value();
}
void Connected::clearEventType()
{
    this->_eventType = {};
}

bool Connected::hasEventType() const
{
    return this->_eventType.has_value();
}
void Connected::setAddress(QString newValue)
{
    this->_address = newValue;
}
QString &Connected::getAddress()
{
    return this->_address.value();
}
void Connected::clearAddress()
{
    this->_address = {};
}

bool Connected::hasAddress() const
{
    return this->_address.has_value();
}



}

