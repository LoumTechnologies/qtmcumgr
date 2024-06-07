
#pragma once


#include <QString>
#include <QJsonObject>



namespace qtmcumgr {


class BootLoaderInfo
{
public:

static bool TryLoad(QJsonObject &jsonObject, BootLoaderInfo &result);
void setAddress(QString newValue);
QString &getAddress();
void setQuery(QString newValue);
QString &getQuery();

private:
QString _address;
QString _query;

};


}
