
#pragma once


#include <QString>
#include <QJsonObject>



namespace qtmcumgr {


class Connect
{
public:

static bool TryLoad(QJsonObject &jsonObject, Connect &result);
void setAddress(QString newValue);
QString &getAddress();

private:
QString _address;

};


}
