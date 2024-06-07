
#pragma once


#include <QString>
#include <QJsonObject>



namespace qtmcumgr {


class ServiceDiscovered
{
public:

static bool TryLoad(QJsonObject &jsonObject, ServiceDiscovered &result);
void setEventType(QString newValue);
QString &getEventType();
void setAddress(QString newValue);
QString &getAddress();
void setService(QString newValue);
QString &getService();
void setServiceDescription(QString newValue);
QString &getServiceDescription();

private:
QString _eventType;
QString _address;
QString _service;
QString _serviceDescription;

};


}
