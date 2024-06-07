

#include "Reset.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {


void Reset::setAddress(QString newValue)
{
    this->_address = newValue;
}

QString &Reset::getAddress()
{
    return this->_address;
}
void Reset::setForce(bool newValue)
{
    this->_force = newValue;
}

bool &Reset::getForce()
{
    return this->_force;
}



}
