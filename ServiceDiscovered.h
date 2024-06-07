
#pragma once


#include <QString>
#include <QJsonObject>

#include <optional>


namespace qtmcumgr {


class ServiceDiscovered
{
public:

    ~ServiceDiscovered();

    static bool TryLoad(const QJsonObject &jsonObject, ServiceDiscovered &result);
    void setEventType(QString newValue);
    QString &getEventType();
    void clearEventType();
    bool hasEventType() const;
    void setAddress(QString newValue);
    QString &getAddress();
    void clearAddress();
    bool hasAddress() const;
    void setService(QString newValue);
    QString &getService();
    void clearService();
    bool hasService() const;
    void setServiceDescription(QString newValue);
    QString &getServiceDescription();
    void clearServiceDescription();
    bool hasServiceDescription() const;

private:
    std::optional<QString> _eventType;
    std::optional<QString> _address;
    std::optional<QString> _service;
    std::optional<QString> _serviceDescription;

};


}

