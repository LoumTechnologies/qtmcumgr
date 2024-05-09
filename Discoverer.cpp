//
// Created by loum-technologies on 4/18/2024.
//

#include "Discoverer.h"
#include <print>
#include <iostream>
#include <qjsondocument.h>

#include "smp_group_fs_mgmt.h"
#include "smp_group_img_mgmt.h"
#include "smp_group_os_mgmt.h"
#include <QString>
#include <QJsonObject>

#include "API.h"
#include "smp_bluetooth.h"
#include "CommonParameters.h"

Discoverer::Discoverer()
{
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    discoveryAgent->setLowEnergyDiscoveryTimeout(0);
    QObject::connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    QObject::connect(discoveryAgent, SIGNAL(finished()), this, SLOT(finished()));
    connections = new QMap<QString, Connection*>();
    devices = new QMap<QString, QBluetoothDeviceInfo>();
}

Discoverer::~Discoverer()
{
    if (discoveryAgent != nullptr) {
        delete discoveryAgent;
        discoveryAgent = nullptr;
    }
    auto connectionValues = connections->values();
    for(auto i = 0; i < connectionValues.count(); i++) {
        delete connectionValues[i];
    }
    delete connections;
    delete devices;
}

void Discoverer::deviceDiscovered(const QBluetoothDeviceInfo &info)
{
    auto cached = info.isCached() ? "true" : "false";
    auto valid = info.isValid() ? "true" : "false";
    QString majorDeviceClass;
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::MiscellaneousDevice) {
        majorDeviceClass = "MiscellaneousDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::ComputerDevice) {
        majorDeviceClass = "ComputerDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::PhoneDevice) {
        majorDeviceClass = "PhoneDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::NetworkDevice) {
        majorDeviceClass = "NetworkDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::AudioVideoDevice) {
        majorDeviceClass = "AudioVideoDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::PeripheralDevice) {
        majorDeviceClass = "PeripheralDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::ImagingDevice) {
        majorDeviceClass = "ImagingDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::WearableDevice) {
        majorDeviceClass = "WearableDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::ToyDevice) {
        majorDeviceClass = "ToyDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::HealthDevice) {
        majorDeviceClass = "HealthDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::UncategorizedDevice) {
        majorDeviceClass = "UncategorizedDevice";
    }

    auto addressOrDeviceUuid = info.address().toString();

    if (addressOrDeviceUuid == "00:00:00:00:00:00")
    {
        addressOrDeviceUuid = info.deviceUuid().toString(QUuid::WithoutBraces);
    }

    if (devices->contains(addressOrDeviceUuid))
    {
        return;
    }

    (*devices)[addressOrDeviceUuid] = info;

    API::sendEvent(std::format(
        R"({{ "eventType": "deviceDiscovered", "address": "{0}", "deviceUuid": "{7}", "name": "{1}", "cached": {2}, "valid": {3}, "rssi": {4}, "majorDeviceClass": "{5}", "minorDeviceClass": {6} }})",
        info.address().toString().toStdString(),
        info.name().toStdString(),
        cached,
        valid,
        info.rssi(),
        majorDeviceClass.toStdString(),
        info.minorDeviceClass(),
        info.deviceUuid().toString(QUuid::WithoutBraces).toStdString()
    ));
}

void Discoverer::start()
{
    discoveryAgent->start();
    API::sendEvent(R"({ "eventType": "deviceScanningStarted" })");
}

void Discoverer::finished() {
    API::sendEvent(R"({ "eventType": "deviceScanningEnded" })");
}

void Discoverer::connect(QString id) {
    if (!connections->contains(id)) {
        if (!devices->contains(id)) {
            API::sendEvent(std::format(R"({{ "eventType": "error", "errorType": "deviceNotYetDiscovered", "id": "{0}" }})",
                       id.toStdString()));
        }
        else {
            auto info = (*devices)[id];
            (*connections)[id] = new Connection(&info, this);
        }
    }
    else {
        auto connection = (*connections)[id];
        API::sendEvent(std::format(R"({{ "eventType": "alreadyConnected", "id": "{0}" }})", id.toStdString()));
    }
}

void Discoverer::disconnect(QString id) {
    if (connections->contains(id)) {
        auto connection = (*connections)[id];
        (*connections).remove(id);
        delete connection;
    } else {
        API::sendEvent(std::format(R"({{ "eventType": "alreadyDisconnected", "id": "{0}" }})", id.toStdString()));
    }
}

void Discoverer::process(const std::string &command) {
    auto commandDocument = QJsonDocument::fromJson(QString(command.c_str()).toUtf8());
    QJsonObject commandObject = commandDocument.object();
    auto commandType = commandObject["commandType"].toString();
    auto id = commandObject["id"].toString().toUpper();

    if (commandType == "connect") {
        connect(id);
    } else if (commandType == "disconnect") {
        disconnect(id);
    }
    else
    {
        auto parameters = CommonParameters::Load(commandObject);

        if (!connections->contains(id)) {
            API::sendEvent(std::format(R"({{ "eventType": "error", "errorType": "deviceNotYetDiscovered", "id": "{0}" }})",
                       id.toStdString()));
            return;
        }

        auto connection = (*connections)[id];

        if (commandType == "reset") {
            auto force = commandObject["force"].toBool();
            connection->reset(force);
        } else if (commandType == "bootLoaderInfo") {
            auto query = commandObject["query"].toString();
            connection->bootLoaderInfo(query);
        } else if (commandType == "getImages") {
            connection->getImages(parameters);
        } else if (commandType == "setImage") {
            auto hashString = QByteArray::fromHex(commandObject["hashString"].toString().toLatin1());
            auto confirm = commandObject["confirm"].toBool();
            connection->setImage(&hashString, confirm, parameters);
        } else if (commandType == "uploadImage") {
            auto image = commandObject["image"].toInt();
            auto fileName = commandObject["fileName"].toString();
//            if (!fileName.endsWith(".bin")) {
//                API::sendEvent(std::format("{{ \"eventType\": \"error\", \"errorType\": \"incorrectFileExtension\", \"address\": \"{0}\", \"fileName\": \"{1}\" }}\n",
//                                           address.toStdString(),
//                                           fileName.toStdString()));
//                return;
//            }
            auto upgrade = commandObject["upgrade"].toBool();
            connection->imageUpload(image, fileName, upgrade, parameters);
        }
    }
}
