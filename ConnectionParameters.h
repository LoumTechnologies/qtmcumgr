
#pragma once


#include <QString>
#include <QJsonObject>



namespace qtmcumgr {


class ConnectionParameters
{
public:

static bool TryLoad(QJsonObject &jsonObject, ConnectionParameters &result);
void setProtocolVersion(int newValue);
int &getProtocolVersion();
void setMtu(int newValue);
int &getMtu();
void setRetries(int newValue);
int &getRetries();
void setTimeoutMs(int newValue);
int &getTimeoutMs();

private:
int _protocolVersion;
int _mtu;
int _retries;
int _timeoutMs;

};


}
