

#include "ResetCompleted.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {



ResetCompleted::~ResetCompleted()
{

}

bool ResetCompleted::TryLoad(const QJsonObject &jsonObject, ResetCompleted &result)
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
void ResetCompleted::setEventType(QString newValue)
{
    this->_eventType = newValue;
}
QString &ResetCompleted::getEventType()
{
    return this->_eventType.value();
}
void ResetCompleted::clearEventType()
{
    this->_eventType = {};
}

bool ResetCompleted::hasEventType() const
{
    return this->_eventType.has_value();
}
void ResetCompleted::setAddress(QString newValue)
{
    this->_address = newValue;
}
QString &ResetCompleted::getAddress()
{
    return this->_address.value();
}
void ResetCompleted::clearAddress()
{
    this->_address = {};
}

bool ResetCompleted::hasAddress() const
{
    return this->_address.has_value();
}



}

