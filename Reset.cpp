

#include "Reset.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {



Reset::~Reset()
{

    delete &_connectionParameters;

}

bool Reset::TryLoad(const QJsonObject &jsonObject, Reset &result)
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

    if (jsonObject.contains("force"))
    {

        if (!jsonObject["force"].isObject())
        {
            return false;
        }

        result.setForce(jsonObject["force"].toBool());

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
void Reset::setCommandType(QString newValue)
{
    this->_commandType = newValue;
}
QString &Reset::getCommandType()
{
    return this->_commandType.value();
}
void Reset::clearCommandType()
{
    this->_commandType = {};
}

bool Reset::hasCommandType() const
{
    return this->_commandType.has_value();
}
void Reset::setAddress(QString newValue)
{
    this->_address = newValue;
}
QString &Reset::getAddress()
{
    return this->_address.value();
}
void Reset::clearAddress()
{
    this->_address = {};
}

bool Reset::hasAddress() const
{
    return this->_address.has_value();
}
void Reset::setForce(bool newValue)
{
    this->_force = newValue;
}
bool &Reset::getForce()
{
    return this->_force.value();
}
void Reset::clearForce()
{
    this->_force = {};
}

bool Reset::hasForce() const
{
    return this->_force.has_value();
}
void Reset::setConnectionParameters(ConnectionParameters newValue)
{
    this->_connectionParameters = newValue;
}
ConnectionParameters &Reset::getConnectionParameters()
{
    return this->_connectionParameters.value();
}
void Reset::clearConnectionParameters()
{
    this->_connectionParameters = {};
}

bool Reset::hasConnectionParameters() const
{
    return this->_connectionParameters.has_value();
}



}

