
#pragma once


#include <QString>
#include <QJsonObject>

#include "ConnectionParameters.h"


namespace qtmcumgr {


class GetImages
{
public:

static bool TryLoad(QJsonObject &jsonObject, GetImages &result);
void setAddress(QString newValue);
QString &getAddress();
void setConnectionParameters(ConnectionParameters newValue);
ConnectionParameters &getConnectionParameters();

private:
QString _address;
ConnectionParameters _connectionParameters;

};


}
