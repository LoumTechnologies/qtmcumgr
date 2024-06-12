

#include "ConnectionParameters.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {



ConnectionParameters::~ConnectionParameters()
{

}

bool ConnectionParameters::TryLoad(const QJsonObject &jsonObject, ConnectionParameters &result)
{

    if (jsonObject.contains("protocolVersion"))
    {

        if (!jsonObject["protocolVersion"].isObject())
        {
            return false;
        }

        result.setProtocolVersion(jsonObject["protocolVersion"].toInt());

    }

    if (jsonObject.contains("mtu"))
    {

        if (!jsonObject["mtu"].isObject())
        {
            return false;
        }

        result.setMtu(jsonObject["mtu"].toInt());

    }

    if (jsonObject.contains("retries"))
    {

        if (!jsonObject["retries"].isObject())
        {
            return false;
        }

        result.setRetries(jsonObject["retries"].toInt());

    }

    if (jsonObject.contains("timeout_ms"))
    {

        if (!jsonObject["timeout_ms"].isObject())
        {
            return false;
        }

        result.setTimeoutMs(jsonObject["timeout_ms"].toInt());

    }


    return true;
}
void ConnectionParameters::setProtocolVersion(int newValue)
{
    this->_protocolVersion = newValue;
}
int &ConnectionParameters::getProtocolVersion()
{
    return this->_protocolVersion.value();
}
void ConnectionParameters::clearProtocolVersion()
{
    this->_protocolVersion = {};
}

bool ConnectionParameters::hasProtocolVersion() const
{
    return this->_protocolVersion.has_value();
}
void ConnectionParameters::setMtu(int newValue)
{
    this->_mtu = newValue;
}
int &ConnectionParameters::getMtu()
{
    return this->_mtu.value();
}
void ConnectionParameters::clearMtu()
{
    this->_mtu = {};
}

bool ConnectionParameters::hasMtu() const
{
    return this->_mtu.has_value();
}
void ConnectionParameters::setRetries(int newValue)
{
    this->_retries = newValue;
}
int &ConnectionParameters::getRetries()
{
    return this->_retries.value();
}
void ConnectionParameters::clearRetries()
{
    this->_retries = {};
}

bool ConnectionParameters::hasRetries() const
{
    return this->_retries.has_value();
}
void ConnectionParameters::setTimeoutMs(int newValue)
{
    this->_timeoutMs = newValue;
}
int &ConnectionParameters::getTimeoutMs()
{
    return this->_timeoutMs.value();
}
void ConnectionParameters::clearTimeoutMs()
{
    this->_timeoutMs = {};
}

bool ConnectionParameters::hasTimeoutMs() const
{
    return this->_timeoutMs.has_value();
}

    void ConnectionParameters::setDefaults() {
        this->setMtu(256);
        this->setRetries(3);
        this->setTimeoutMs(3000);
        this->setProtocolVersion(1);
    }

}

