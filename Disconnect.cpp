

#include "Disconnect.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {


void Disconnect::setAddress(QString newValue)
{
    this->_address = newValue;
}

QString &Disconnect::getAddress()
{
    return this->_address;
}



}
