

#include "DeviceDiscovered.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {


void DeviceDiscovered::setEventType(QString newValue)
{
    this->_eventType = newValue;
}

QString &DeviceDiscovered::getEventType()
{
    return this->_eventType;
}
void DeviceDiscovered::setAddress(QString newValue)
{
    this->_address = newValue;
}

QString &DeviceDiscovered::getAddress()
{
    return this->_address;
}
void DeviceDiscovered::setName(QString newValue)
{
    this->_name = newValue;
}

QString &DeviceDiscovered::getName()
{
    return this->_name;
}
void DeviceDiscovered::setCached(bool newValue)
{
    this->_cached = newValue;
}

bool &DeviceDiscovered::getCached()
{
    return this->_cached;
}
void DeviceDiscovered::setValid(bool newValue)
{
    this->_valid = newValue;
}

bool &DeviceDiscovered::getValid()
{
    return this->_valid;
}
void DeviceDiscovered::setRssi(int newValue)
{
    this->_rssi = newValue;
}

int &DeviceDiscovered::getRssi()
{
    return this->_rssi;
}
void DeviceDiscovered::setMajorDeviceClass(QString newValue)
{
    this->_majorDeviceClass = newValue;
}

QString &DeviceDiscovered::getMajorDeviceClass()
{
    return this->_majorDeviceClass;
}
void DeviceDiscovered::setMinorDeviceClass(int newValue)
{
    this->_minorDeviceClass = newValue;
}

int &DeviceDiscovered::getMinorDeviceClass()
{
    return this->_minorDeviceClass;
}



}
