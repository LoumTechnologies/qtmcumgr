

#include "SetImage.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {


void SetImage::setAddress(QString newValue)
{
    this->_address = newValue;
}

QString &SetImage::getAddress()
{
    return this->_address;
}
void SetImage::setHashString(QString newValue)
{
    this->_hashString = newValue;
}

QString &SetImage::getHashString()
{
    return this->_hashString;
}
void SetImage::setConfirm(bool newValue)
{
    this->_confirm = newValue;
}

bool &SetImage::getConfirm()
{
    return this->_confirm;
}
void SetImage::setConnectionParameters(ConnectionParameters newValue)
{
    this->_connectionParameters = newValue;
}

ConnectionParameters &SetImage::getConnectionParameters()
{
    return this->_connectionParameters;
}



}
