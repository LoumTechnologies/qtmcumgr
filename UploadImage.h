
#pragma once


#include <QString>
#include <QJsonObject>

#include "ConnectionParameters.h"


namespace qtmcumgr {


class UploadImage
{
public:

static bool TryLoad(QJsonObject &jsonObject, UploadImage &result);
void setAddress(QString newValue);
QString &getAddress();
void setImage(int newValue);
int &getImage();
void setFileName(QString newValue);
QString &getFileName();
void setUpgrade(bool newValue);
bool &getUpgrade();
void setConnectionParameters(ConnectionParameters newValue);
ConnectionParameters &getConnectionParameters();

private:
QString _address;
int _image;
QString _fileName;
bool _upgrade;
ConnectionParameters _connectionParameters;

};


}
