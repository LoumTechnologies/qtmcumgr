
#pragma once


#include <QString>
#include <QJsonObject>

#include <optional>
#include "ConnectionParameters.h"


namespace qtmcumgr {


class UploadImage
{
public:

    ~UploadImage();

    static bool TryLoad(const QJsonObject &jsonObject, UploadImage &result);
    void setCommandType(QString newValue);
    QString &getCommandType();
    void clearCommandType();
    bool hasCommandType() const;
    void setAddress(QString newValue);
    QString &getAddress();
    void clearAddress();
    bool hasAddress() const;
    void setImage(int newValue);
    int &getImage();
    void clearImage();
    bool hasImage() const;
    void setFileName(QString newValue);
    QString &getFileName();
    void clearFileName();
    bool hasFileName() const;
    void setUpgrade(bool newValue);
    bool &getUpgrade();
    void clearUpgrade();
    bool hasUpgrade() const;
    void setConnectionParameters(ConnectionParameters newValue);
    ConnectionParameters &getConnectionParameters();
    void clearConnectionParameters();
    bool hasConnectionParameters() const;

private:
    std::optional<QString> _commandType;
    std::optional<QString> _address;
    std::optional<int> _image;
    std::optional<QString> _fileName;
    std::optional<bool> _upgrade;
    std::optional<ConnectionParameters> _connectionParameters;

};


}

