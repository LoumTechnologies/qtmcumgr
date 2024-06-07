

#include "Connected.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {


void Connected::setEventType(QString newValue)
{
    this->_eventType = newValue;
}

QString &Connected::getEventType()
{
    return this->_eventType;
}
void Connected::setAddress(QString newValue)
{
    this->_address = newValue;
}

QString &Connected::getAddress()
{
    return this->_address;
}



}
