

#include "Connect.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {


void Connect::setAddress(QString newValue)
{
    this->_address = newValue;
}

QString &Connect::getAddress()
{
    return this->_address;
}



}
