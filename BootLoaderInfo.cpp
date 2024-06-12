

#include "BootLoaderInfo.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {



BootLoaderInfo::~BootLoaderInfo()
{

    if (_connectionParameters.has_value()) {
        delete &_connectionParameters;
    }

}

bool BootLoaderInfo::TryLoad(const QJsonObject &jsonObject, BootLoaderInfo &result)
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

    if (jsonObject.contains("query"))
    {

        if (!jsonObject["query"].isString())
        {
            return false;
        }

        result.setQuery(jsonObject["query"].toString());

    }

    if (jsonObject.contains("connectionParameters"))
    {

        if (!jsonObject["connectionParameters"].isObject())
        {
            return false;
        }

        auto connectionParameters = new ConnectionParameters();
        if (!ConnectionParameters::TryLoad(jsonObject["connectionParameters"].toObject(), *connectionParameters))
        {
            delete connectionParameters;
            return false;
        }

    }


    return true;
}
void BootLoaderInfo::setCommandType(QString newValue)
{
    this->_commandType = newValue;
}
QString &BootLoaderInfo::getCommandType()
{
    return this->_commandType.value();
}
void BootLoaderInfo::clearCommandType()
{
    this->_commandType = {};
}

bool BootLoaderInfo::hasCommandType() const
{
    return this->_commandType.has_value();
}
void BootLoaderInfo::setAddress(QString newValue)
{
    this->_address = newValue;
}
QString &BootLoaderInfo::getAddress()
{
    return this->_address.value();
}
void BootLoaderInfo::clearAddress()
{
    this->_address = {};
}

bool BootLoaderInfo::hasAddress() const
{
    return this->_address.has_value();
}
void BootLoaderInfo::setQuery(QString newValue)
{
    this->_query = newValue;
}
QString &BootLoaderInfo::getQuery()
{
    return this->_query.value();
}
void BootLoaderInfo::clearQuery()
{
    this->_query = {};
}

bool BootLoaderInfo::hasQuery() const
{
    return this->_query.has_value();
}
void BootLoaderInfo::setConnectionParameters(ConnectionParameters newValue)
{
    this->_connectionParameters = newValue;
}
ConnectionParameters &BootLoaderInfo::getConnectionParameters()
{
    return this->_connectionParameters.value();
}
void BootLoaderInfo::clearConnectionParameters()
{
    this->_connectionParameters = {};
}

bool BootLoaderInfo::hasConnectionParameters() const
{
    return this->_connectionParameters.has_value();
}



}

