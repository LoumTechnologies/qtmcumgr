

#include "SetImage.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {



SetImage::~SetImage()
{

    delete &_connectionParameters;

}

bool SetImage::TryLoad(const QJsonObject &jsonObject, SetImage &result)
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

    if (jsonObject.contains("hashString"))
    {

        if (!jsonObject["hashString"].isString())
        {
            return false;
        }

        result.setHashString(jsonObject["hashString"].toString());

    }

    if (jsonObject.contains("confirm"))
    {

        if (!jsonObject["confirm"].isObject())
        {
            return false;
        }

        result.setConfirm(jsonObject["confirm"].toBool());

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
void SetImage::setCommandType(QString newValue)
{
    this->_commandType = newValue;
}
QString &SetImage::getCommandType()
{
    return this->_commandType.value();
}
void SetImage::clearCommandType()
{
    this->_commandType = {};
}

bool SetImage::hasCommandType() const
{
    return this->_commandType.has_value();
}
void SetImage::setAddress(QString newValue)
{
    this->_address = newValue;
}
QString &SetImage::getAddress()
{
    return this->_address.value();
}
void SetImage::clearAddress()
{
    this->_address = {};
}

bool SetImage::hasAddress() const
{
    return this->_address.has_value();
}
void SetImage::setHashString(QString newValue)
{
    this->_hashString = newValue;
}
QString &SetImage::getHashString()
{
    return this->_hashString.value();
}
void SetImage::clearHashString()
{
    this->_hashString = {};
}

bool SetImage::hasHashString() const
{
    return this->_hashString.has_value();
}
void SetImage::setConfirm(bool newValue)
{
    this->_confirm = newValue;
}
bool &SetImage::getConfirm()
{
    return this->_confirm.value();
}
void SetImage::clearConfirm()
{
    this->_confirm = {};
}

bool SetImage::hasConfirm() const
{
    return this->_confirm.has_value();
}
void SetImage::setConnectionParameters(ConnectionParameters newValue)
{
    this->_connectionParameters = newValue;
}
ConnectionParameters &SetImage::getConnectionParameters()
{
    return this->_connectionParameters.value();
}
void SetImage::clearConnectionParameters()
{
    this->_connectionParameters = {};
}

bool SetImage::hasConnectionParameters() const
{
    return this->_connectionParameters.has_value();
}



}

