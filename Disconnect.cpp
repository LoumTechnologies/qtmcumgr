

#include "Disconnect.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {



Disconnect::~Disconnect()
{

}

bool Disconnect::TryLoad(const QJsonObject &jsonObject, Disconnect &result)
{

    if (jsonObject.contains("commandType"))
    {

        if (!jsonObject["commandType"].isString())
        {
            return false;
        }

        result.setCommandType(jsonObject["commandType"].toString());

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
void Disconnect::setCommandType(QString newValue)
{
    this->_commandType = newValue;
}
QString &Disconnect::getCommandType()
{
    return this->_commandType.value();
}
void Disconnect::clearCommandType()
{
    this->_commandType = {};
}

bool Disconnect::hasCommandType() const
{
    return this->_commandType.has_value();
}
void Disconnect::setAddress(QString newValue)
{
    this->_address = newValue;
}
QString &Disconnect::getAddress()
{
    return this->_address.value();
}
void Disconnect::clearAddress()
{
    this->_address = {};
}

bool Disconnect::hasAddress() const
{
    return this->_address.has_value();
}



}

