

#include "UploadImage.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {



UploadImage::~UploadImage()
{

}

bool UploadImage::TryLoad(const QJsonObject &jsonObject, UploadImage &result)
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

    if (jsonObject.contains("image"))
    {

        if (!jsonObject["image"].isObject())
        {
            return false;
        }

        result.setImage(jsonObject["image"].toInt());

    }

    if (jsonObject.contains("fileName"))
    {

        if (!jsonObject["fileName"].isString())
        {
            return false;
        }

        result.setFileName(jsonObject["fileName"].toString());

    }

    if (jsonObject.contains("upgrade"))
    {

        if (!jsonObject["upgrade"].isObject())
        {
            return false;
        }

        result.setUpgrade(jsonObject["upgrade"].toBool());

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
void UploadImage::setCommandType(QString newValue)
{
    this->_commandType = newValue;
}
QString &UploadImage::getCommandType()
{
    return this->_commandType.value();
}
void UploadImage::clearCommandType()
{
    this->_commandType = {};
}

bool UploadImage::hasCommandType() const
{
    return this->_commandType.has_value();
}
void UploadImage::setAddress(QString newValue)
{
    this->_address = newValue;
}
QString &UploadImage::getAddress()
{
    return this->_address.value();
}
void UploadImage::clearAddress()
{
    this->_address = {};
}

bool UploadImage::hasAddress() const
{
    return this->_address.has_value();
}
void UploadImage::setImage(int newValue)
{
    this->_image = newValue;
}
int &UploadImage::getImage()
{
    return this->_image.value();
}
void UploadImage::clearImage()
{
    this->_image = {};
}

bool UploadImage::hasImage() const
{
    return this->_image.has_value();
}
void UploadImage::setFileName(QString newValue)
{
    this->_fileName = newValue;
}
QString &UploadImage::getFileName()
{
    return this->_fileName.value();
}
void UploadImage::clearFileName()
{
    this->_fileName = {};
}

bool UploadImage::hasFileName() const
{
    return this->_fileName.has_value();
}
void UploadImage::setUpgrade(bool newValue)
{
    this->_upgrade = newValue;
}
bool &UploadImage::getUpgrade()
{
    return this->_upgrade.value();
}
void UploadImage::clearUpgrade()
{
    this->_upgrade = {};
}

bool UploadImage::hasUpgrade() const
{
    return this->_upgrade.has_value();
}
void UploadImage::setConnectionParameters(ConnectionParameters newValue)
{
    this->_connectionParameters = newValue;
}
ConnectionParameters &UploadImage::getConnectionParameters()
{
    return this->_connectionParameters.value();
}
void UploadImage::clearConnectionParameters()
{
    this->_connectionParameters = {};
}

bool UploadImage::hasConnectionParameters() const
{
    return this->_connectionParameters.has_value();
}



}

