
#pragma once


#include <QString>
#include <QJsonObject>

#include <optional>


namespace qtmcumgr {


class Connect
{
public:

    ~Connect();

    static bool TryLoad(const QJsonObject &jsonObject, Connect &result);
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

