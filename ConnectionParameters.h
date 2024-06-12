
#pragma once


#include <QString>
#include <QJsonObject>

#include <optional>


namespace qtmcumgr {


class ConnectionParameters
{
public:

    ~ConnectionParameters();

    static bool TryLoad(const QJsonObject &jsonObject, ConnectionParameters &result);
    void setProtocolVersion(int newValue);
    int &getProtocolVersion();
    void clearProtocolVersion();
    bool hasProtocolVersion() const;
    void setMtu(int newValue);
    int &getMtu();
    void clearMtu();
    bool hasMtu() const;
    void setRetries(int newValue);
    int &getRetries();
    void clearRetries();
    bool hasRetries() const;
    void setTimeoutMs(int newValue);
    int &getTimeoutMs();
    void clearTimeoutMs();
    bool hasTimeoutMs() const;

    void setDefaults();

private:
    std::optional<int> _protocolVersion;
    std::optional<int> _mtu;
    std::optional<int> _retries;
    std::optional<int> _timeoutMs;

};


}

