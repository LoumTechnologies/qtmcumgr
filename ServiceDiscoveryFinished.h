
#pragma once


#include <QString>
#include <QJsonObject>



namespace qtmcumgr {


class ServiceDiscoveryFinished
{
public:

static bool TryLoad(QJsonObject &jsonObject, ServiceDiscoveryFinished &result);
void setEventType(QString newValue);
QString &getEventType();
void setAddress(QString newValue);
QString &getAddress();

private:
QString _eventType;
QString _address;

};


}
