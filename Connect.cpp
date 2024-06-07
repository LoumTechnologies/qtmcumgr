

#include "Connect.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {



Connect::~Connect()
{

}

bool Connect::TryLoad(const QJsonObject &jsonObject, Connect &result)
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
void Connect::setCommandType(QString newValue)
{
    this->_commandType = newValue;
}
QString &Connect::getCommandType()
{
    return this->_commandType.value();
}
void Connect::clearCommandType()
{
    this->_commandType = {};
}

bool Connect::hasCommandType() const
{
    return this->_commandType.has_value();
}
void Connect::setAddress(QString newValue)
{
    this->_address = newValue;
}
QString &Connect::getAddress()
{
    return this->_address.value();
}
void Connect::clearAddress()
{
    this->_address = {};
}

bool Connect::hasAddress() const
{
    return this->_address.has_value();
}



}

