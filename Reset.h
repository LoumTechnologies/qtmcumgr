
#pragma once


#include <QString>
#include <QJsonObject>

#include <optional>
#include "ConnectionParameters.h"


namespace qtmcumgr {


class Reset
{
public:

    ~Reset();

    static bool TryLoad(const QJsonObject &jsonObject, Reset &result);
    void setCommandType(QString newValue);
    QString &getCommandType();
    void clearCommandType();
    bool hasCommandType() const;
    void setAddress(QString newValue);
    QString &getAddress();
    void clearAddress();
    bool hasAddress() const;
    void setForce(bool newValue);
    bool &getForce();
    void clearForce();
    bool hasForce() const;
    void setConnectionParameters(ConnectionParameters newValue);
    ConnectionParameters &getConnectionParameters();
    void clearConnectionParameters();
    bool hasConnectionParameters() const;

private:
    std::optional<QString> _commandType;
    std::optional<QString> _address;
    std::optional<bool> _force;
    std::optional<ConnectionParameters> _connectionParameters;

};


}

