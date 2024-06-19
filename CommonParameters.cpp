//
// Created by loum-technologies on 4/28/2024.
//

#include "CommonParameters.h"

CommonParameters::CommonParameters() {
    protocolVersion = 1;
    mtu = 256;
    retries = 3;
    timeout_ms = 3000;
}

CommonParameters CommonParameters::Load(QJsonObject &json) {
    auto result = CommonParameters();
    if (!json["protocolVersion"].isDouble()) {
        result.protocolVersion = 1;
    }
    else {
        result.protocolVersion = json["protocolVersion"].toInt();
    }
    if (!json["mtu"].isDouble()) {
        result.mtu = 256;
    }
    else {
        result.mtu = json["mtu"].toInt();
    }
    if (!json["retries"].isDouble()) {
        result.retries = 3;
    }
    else {
        result.retries = json["retries"].toInt();
    }
    if (!json["timeoutMs"].isDouble()) {
        result.timeout_ms = 3000;
    }
    else {
        result.timeout_ms = json["timeoutMs"].toInt();
    }
    return result;
}

int CommonParameters::getProtocolVersion() {
    return protocolVersion;
}

int CommonParameters::getMtu() {
    return mtu;
}

int CommonParameters::getRetries() {
    return retries;
}

int CommonParameters::getTimeout_ms() {
    return timeout_ms;
}
