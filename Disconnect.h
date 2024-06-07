
#pragma once


#include <QString>
#include <QJsonObject>

#include <optional>


namespace qtmcumgr {


class Disconnect
{
public:

    ~Disconnect();

    static bool TryLoad(const QJsonObject &jsonObject, Disconnect &result);
    void setCommandType(QString newValue);
    QString &getCommandType();
    void clearCommandType();
    bool hasCommandType() const;
    void setAddress(QString newValue);
    QString &getAddress();
    void clearAddress();
    bool hasAddress() const;

private:
    std::optional<QString> _commandType;
    std::optional<QString> _address;

};


}

