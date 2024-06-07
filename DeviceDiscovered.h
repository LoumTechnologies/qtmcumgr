
#pragma once


#include <QString>
#include <QJsonObject>

#include <optional>


namespace qtmcumgr {


class DeviceDiscovered
{
public:

    ~DeviceDiscovered();

    static bool TryLoad(const QJsonObject &jsonObject, DeviceDiscovered &result);
    void setEventType(QString newValue);
    QString &getEventType();
    void clearEventType();
    bool hasEventType() const;
    void setAddress(QString newValue);
    QString &getAddress();
    void clearAddress();
    bool hasAddress() const;
    void setName(QString newValue);
    QString &getName();
    void clearName();
    bool hasName() const;
    void setCached(bool newValue);
    bool &getCached();
    void clearCached();
    bool hasCached() const;
    void setValid(bool newValue);
    bool &getValid();
    void clearValid();
    bool hasValid() const;
    void setRssi(int newValue);
    int &getRssi();
    void clearRssi();
    bool hasRssi() const;
    void setMajorDeviceClass(QString newValue);
    QString &getMajorDeviceClass();
    void clearMajorDeviceClass();
    bool hasMajorDeviceClass() const;
    void setMinorDeviceClass(int newValue);
    int &getMinorDeviceClass();
    void clearMinorDeviceClass();
    bool hasMinorDeviceClass() const;

private:
    std::optional<QString> _eventType;
    std::optional<QString> _address;
    std::optional<QString> _name;
    std::optional<bool> _cached;
    std::optional<bool> _valid;
    std::optional<int> _rssi;
    std::optional<QString> _majorDeviceClass;
    std::optional<int> _minorDeviceClass;

};


}

