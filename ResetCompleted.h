
#pragma once


#include <QString>
#include <QJsonObject>

#include <optional>


namespace qtmcumgr {


class ResetCompleted
{
public:

    ~ResetCompleted();

    static bool TryLoad(const QJsonObject &jsonObject, ResetCompleted &result);
    void setEventType(QString newValue);
    QString &getEventType();
    void clearEventType();
    bool hasEventType() const;
    void setAddress(QString newValue);
    QString &getAddress();
    void clearAddress();
    bool hasAddress() const;

private:
    std::optional<QString> _eventType;
    std::optional<QString> _address;

};


}

