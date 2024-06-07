

#include "BootLoaderInfo.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {


void BootLoaderInfo::setAddress(QString newValue)
{
    this->_address = newValue;
}

QString &BootLoaderInfo::getAddress()
{
    return this->_address;
}
void BootLoaderInfo::setQuery(QString newValue)
{
    this->_query = newValue;
}

QString &BootLoaderInfo::getQuery()
{
    return this->_query;
}



}
