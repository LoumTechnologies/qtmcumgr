
#pragma once


#include <QString>
#include <QJsonObject>

#include <optional>
#include "ConnectionParameters.h"


namespace qtmcumgr {


class SetImage
{
public:

    ~SetImage();

    static bool TryLoad(const QJsonObject &jsonObject, SetImage &result);
    void setCommandType(QString newValue);
    QString &getCommandType();
    void clearCommandType();
    bool hasCommandType() const;
    void setAddress(QString newValue);
    QString &getAddress();
    void clearAddress();
    bool hasAddress() const;
    void setHashString(QString newValue);
    QString &getHashString();
    void clearHashString();
    bool hasHashString() const;
    void setConfirm(bool newValue);
    bool &getConfirm();
    void clearConfirm();
    bool hasConfirm() const;
    void setConnectionParameters(ConnectionParameters newValue);
    ConnectionParameters &getConnectionParameters();
    void clearConnectionParameters();
    bool hasConnectionParameters() const;

private:
    std::optional<QString> _commandType;
    std::optional<QString> _address;
    std::optional<QString> _hashString;
    std::optional<bool> _confirm;
    std::optional<ConnectionParameters> _connectionParameters;

};


}

