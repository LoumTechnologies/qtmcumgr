
#pragma once


#include <QString>
#include <QJsonObject>



namespace qtmcumgr {


class DeviceDiscovered
{
public:

static bool TryLoad(QJsonObject &jsonObject, DeviceDiscovered &result);
void setEventType(QString newValue);
QString &getEventType();
void setAddress(QString newValue);
QString &getAddress();
void setName(QString newValue);
QString &getName();
void setCached(bool newValue);
bool &getCached();
void setValid(bool newValue);
bool &getValid();
void setRssi(int newValue);
int &getRssi();
void setMajorDeviceClass(QString newValue);
QString &getMajorDeviceClass();
void setMinorDeviceClass(int newValue);
int &getMinorDeviceClass();

private:
QString _eventType;
QString _address;
QString _name;
bool _cached;
bool _valid;
int _rssi;
QString _majorDeviceClass;
int _minorDeviceClass;

};


}
