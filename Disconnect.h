
#pragma once


#include <QString>
#include <QJsonObject>



namespace qtmcumgr {


class Disconnect
{
public:

static bool TryLoad(QJsonObject &jsonObject, Disconnect &result);
void setAddress(QString newValue);
QString &getAddress();

private:
QString _address;

};


}
