
#pragma once


#include <QString>
#include <QJsonObject>

#include <optional>
#include "ConnectionParameters.h"


namespace qtmcumgr {


class BootLoaderInfo
{
public:

    ~BootLoaderInfo();

    static bool TryLoad(const QJsonObject &jsonObject, BootLoaderInfo &result);
    void setCommandType(QString newValue);
    QString &getCommandType();
    void clearCommandType();
    bool hasCommandType() const;
    void setAddress(QString newValue);
    QString &getAddress();
    void clearAddress();
    bool hasAddress() const;
    void setQuery(QString newValue);
    QString &getQuery();
    void clearQuery();
    bool hasQuery() const;
    void setConnectionParameters(ConnectionParameters newValue);
    ConnectionParameters &getConnectionParameters();
    void clearConnectionParameters();
    bool hasConnectionParameters() const;

private:
    std::optional<QString> _commandType;
    std::optional<QString> _address;
    std::optional<QString> _query;
    std::optional<ConnectionParameters> _connectionParameters;

};


}

