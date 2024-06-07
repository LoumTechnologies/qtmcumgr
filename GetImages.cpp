

#include "GetImages.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {



GetImages::~GetImages()
{

    delete &_connectionParameters;

}

bool GetImages::TryLoad(const QJsonObject &jsonObject, GetImages &result)
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
void GetImages::setCommandType(QString newValue)
{
    this->_commandType = newValue;
}
QString &GetImages::getCommandType()
{
    return this->_commandType.value();
}
void GetImages::clearCommandType()
{
    this->_commandType = {};
}

bool GetImages::hasCommandType() const
{
    return this->_commandType.has_value();
}
void GetImages::setAddress(QString newValue)
{
    this->_address = newValue;
}
QString &GetImages::getAddress()
{
    return this->_address.value();
}
void GetImages::clearAddress()
{
    this->_address = {};
}

bool GetImages::hasAddress() const
{
    return this->_address.has_value();
}
void GetImages::setConnectionParameters(ConnectionParameters newValue)
{
    this->_connectionParameters = newValue;
}
ConnectionParameters &GetImages::getConnectionParameters()
{
    return this->_connectionParameters.value();
}
void GetImages::clearConnectionParameters()
{
    this->_connectionParameters = {};
}

bool GetImages::hasConnectionParameters() const
{
    return this->_connectionParameters.has_value();
}



}

