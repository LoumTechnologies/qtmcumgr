
#pragma once


#include <QString>
#include <QJsonObject>

#include "ConnectionParameters.h"


namespace qtmcumgr {


class SetImage
{
public:

static bool TryLoad(QJsonObject &jsonObject, SetImage &result);
void setAddress(QString newValue);
QString &getAddress();
void setHashString(QString newValue);
QString &getHashString();
void setConfirm(bool newValue);
bool &getConfirm();
void setConnectionParameters(ConnectionParameters newValue);
ConnectionParameters &getConnectionParameters();

private:
QString _address;
QString _hashString;
bool _confirm;
ConnectionParameters _connectionParameters;

};


}
