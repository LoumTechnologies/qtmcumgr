

#include "UploadImage.h"
#include <QString>
#include <QJsonObject>


namespace qtmcumgr {


void UploadImage::setAddress(QString newValue)
{
    this->_address = newValue;
}

QString &UploadImage::getAddress()
{
    return this->_address;
}
void UploadImage::setImage(int newValue)
{
    this->_image = newValue;
}

int &UploadImage::getImage()
{
    return this->_image;
}
void UploadImage::setFileName(QString newValue)
{
    this->_fileName = newValue;
}

QString &UploadImage::getFileName()
{
    return this->_fileName;
}
void UploadImage::setUpgrade(bool newValue)
{
    this->_upgrade = newValue;
}

bool &UploadImage::getUpgrade()
{
    return this->_upgrade;
}
void UploadImage::setConnectionParameters(ConnectionParameters newValue)
{
    this->_connectionParameters = newValue;
}

ConnectionParameters &UploadImage::getConnectionParameters()
{
    return this->_connectionParameters;
}



}
