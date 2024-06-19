//
// Created by loum-technologies on 4/28/2024.
//

#ifndef QTMCUMGR_COMMONPARAMETERS_H
#define QTMCUMGR_COMMONPARAMETERS_H


#include <QJsonObject>

class CommonParameters {
public:
    CommonParameters();
    static CommonParameters Load(QJsonObject &json);

    int getProtocolVersion();
    int getMtu();
    int getRetries();
    int getTimeout_ms();

private:
    int protocolVersion;
    int mtu;
    int retries;
    int timeout_ms;
};


#endif //QTMCUMGR_COMMONPARAMETERS_H
