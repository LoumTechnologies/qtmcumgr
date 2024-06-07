

#include "Disconnected.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {


void Disconnected::setEventType(QString newValue)
{
    this->_eventType = newValue;
}

QString &Disconnected::getEventType()
{
    return this->_eventType;
}
void Disconnected::setAddress(QString newValue)
{
    this->_address = newValue;
}

QString &Disconnected::getAddress()
{
    return this->_address;
}



}
