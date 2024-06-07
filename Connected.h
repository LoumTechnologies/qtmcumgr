
#pragma once


#include <QString>
#include <QJsonObject>



namespace qtmcumgr {


class Connected
{
public:

static bool TryLoad(QJsonObject &jsonObject, Connected &result);
void setEventType(QString newValue);
QString &getEventType();
void setAddress(QString newValue);
QString &getAddress();

private:
QString _eventType;
QString _address;

};


}
