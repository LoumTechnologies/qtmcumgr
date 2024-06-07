
#pragma once


#include <QString>
#include <QJsonObject>



namespace qtmcumgr {


class Reset
{
public:

static bool TryLoad(QJsonObject &jsonObject, Reset &result);
void setAddress(QString newValue);
QString &getAddress();
void setForce(bool newValue);
bool &getForce();

private:
QString _address;
bool _force;

};


}
