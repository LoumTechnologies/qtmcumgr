

#include "ResetCompleted.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {


void ResetCompleted::setEventType(QString newValue)
{
    this->_eventType = newValue;
}

QString &ResetCompleted::getEventType()
{
    return this->_eventType;
}
void ResetCompleted::setAddress(QString newValue)
{
    this->_address = newValue;
}

QString &ResetCompleted::getAddress()
{
    return this->_address;
}



}
