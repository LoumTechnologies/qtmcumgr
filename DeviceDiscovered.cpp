

#include "DeviceDiscovered.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {



DeviceDiscovered::~DeviceDiscovered()
{

}

bool DeviceDiscovered::TryLoad(const QJsonObject &jsonObject, DeviceDiscovered &result)
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

    if (jsonObject.contains("name"))
    {

        if (!jsonObject["name"].isString())
        {
            return false;
        }

        result.setName(jsonObject["name"].toString());

    }

    if (jsonObject.contains("cached"))
    {

        if (!jsonObject["cached"].isObject())
        {
            return false;
        }

        result.setCached(jsonObject["cached"].toBool());

    }

    if (jsonObject.contains("valid"))
    {

        if (!jsonObject["valid"].isObject())
        {
            return false;
        }

        result.setValid(jsonObject["valid"].toBool());

    }

    if (jsonObject.contains("rssi"))
    {

        if (!jsonObject["rssi"].isObject())
        {
            return false;
        }

        result.setRssi(jsonObject["rssi"].toInt());

    }

    if (jsonObject.contains("majorDeviceClass"))
    {

        if (!jsonObject["majorDeviceClass"].isString())
        {
            return false;
        }

        result.setMajorDeviceClass(jsonObject["majorDeviceClass"].toString());

    }

    if (jsonObject.contains("minorDeviceClass"))
    {

        if (!jsonObject["minorDeviceClass"].isObject())
        {
            return false;
        }

        result.setMinorDeviceClass(jsonObject["minorDeviceClass"].toInt());

    }


    return true;
}
void DeviceDiscovered::setEventType(QString newValue)
{
    this->_eventType = newValue;
}
QString &DeviceDiscovered::getEventType()
{
    return this->_eventType.value();
}
void DeviceDiscovered::clearEventType()
{
    this->_eventType = {};
}

bool DeviceDiscovered::hasEventType() const
{
    return this->_eventType.has_value();
}
void DeviceDiscovered::setAddress(QString newValue)
{
    this->_address = newValue;
}
QString &DeviceDiscovered::getAddress()
{
    return this->_address.value();
}
void DeviceDiscovered::clearAddress()
{
    this->_address = {};
}

bool DeviceDiscovered::hasAddress() const
{
    return this->_address.has_value();
}
void DeviceDiscovered::setName(QString newValue)
{
    this->_name = newValue;
}
QString &DeviceDiscovered::getName()
{
    return this->_name.value();
}
void DeviceDiscovered::clearName()
{
    this->_name = {};
}

bool DeviceDiscovered::hasName() const
{
    return this->_name.has_value();
}
void DeviceDiscovered::setCached(bool newValue)
{
    this->_cached = newValue;
}
bool &DeviceDiscovered::getCached()
{
    return this->_cached.value();
}
void DeviceDiscovered::clearCached()
{
    this->_cached = {};
}

bool DeviceDiscovered::hasCached() const
{
    return this->_cached.has_value();
}
void DeviceDiscovered::setValid(bool newValue)
{
    this->_valid = newValue;
}
bool &DeviceDiscovered::getValid()
{
    return this->_valid.value();
}
void DeviceDiscovered::clearValid()
{
    this->_valid = {};
}

bool DeviceDiscovered::hasValid() const
{
    return this->_valid.has_value();
}
void DeviceDiscovered::setRssi(int newValue)
{
    this->_rssi = newValue;
}
int &DeviceDiscovered::getRssi()
{
    return this->_rssi.value();
}
void DeviceDiscovered::clearRssi()
{
    this->_rssi = {};
}

bool DeviceDiscovered::hasRssi() const
{
    return this->_rssi.has_value();
}
void DeviceDiscovered::setMajorDeviceClass(QString newValue)
{
    this->_majorDeviceClass = newValue;
}
QString &DeviceDiscovered::getMajorDeviceClass()
{
    return this->_majorDeviceClass.value();
}
void DeviceDiscovered::clearMajorDeviceClass()
{
    this->_majorDeviceClass = {};
}

bool DeviceDiscovered::hasMajorDeviceClass() const
{
    return this->_majorDeviceClass.has_value();
}
void DeviceDiscovered::setMinorDeviceClass(int newValue)
{
    this->_minorDeviceClass = newValue;
}
int &DeviceDiscovered::getMinorDeviceClass()
{
    return this->_minorDeviceClass.value();
}
void DeviceDiscovered::clearMinorDeviceClass()
{
    this->_minorDeviceClass = {};
}

bool DeviceDiscovered::hasMinorDeviceClass() const
{
    return this->_minorDeviceClass.has_value();
}



}

