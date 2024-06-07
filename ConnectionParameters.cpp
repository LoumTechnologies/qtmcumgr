

#include "ConnectionParameters.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {


void ConnectionParameters::setProtocolVersion(int newValue)
{
    this->_protocolVersion = newValue;
}

int &ConnectionParameters::getProtocolVersion()
{
    return this->_protocolVersion;
}
void ConnectionParameters::setMtu(int newValue)
{
    this->_mtu = newValue;
}

int &ConnectionParameters::getMtu()
{
    return this->_mtu;
}
void ConnectionParameters::setRetries(int newValue)
{
    this->_retries = newValue;
}

int &ConnectionParameters::getRetries()
{
    return this->_retries;
}
void ConnectionParameters::setTimeoutMs(int newValue)
{
    this->_timeoutMs = newValue;
}

int &ConnectionParameters::getTimeoutMs()
{
    return this->_timeoutMs;
}



}
