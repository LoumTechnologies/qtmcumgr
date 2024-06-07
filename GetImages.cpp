

#include "GetImages.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {


void GetImages::setAddress(QString newValue)
{
    this->_address = newValue;
}

QString &GetImages::getAddress()
{
    return this->_address;
}
void GetImages::setConnectionParameters(ConnectionParameters newValue)
{
    this->_connectionParameters = newValue;
}

ConnectionParameters &GetImages::getConnectionParameters()
{
    return this->_connectionParameters;
}



}
