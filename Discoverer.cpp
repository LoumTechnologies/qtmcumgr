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

    API::sendEvent(std::format(
        "{{ \"eventType\": \"deviceDiscovered\", \"address\": \"{0}\", \"name\": \"{1}\", \"cached\": {2}, \"valid\": {3}, \"rssi\": {4}, \"majorDeviceClass\": \"{5}\", \"minorDeviceClass\": {6} }}\n",
        info.address().toString().toStdString(),
        info.name().toStdString(),
        cached,
        valid,
        info.rssi(),
        majorDeviceClass.toStdString(),
        info.minorDeviceClass()
    ));
    (*devices)[info.address().toString().toUpper()] = info;

    //connect(info.address().toString().toUpper());
}

void Discoverer::start()
{
    discoveryAgent->start();
    API::sendEvent("{ \"eventType\": \"deviceScanningStarted\" }\n");
}

void Discoverer::finished() {
    API::sendEvent("{ \"eventType\": \"deviceScanningEnded\" }\n");
}

void Discoverer::connect(QString address) {
    if (!connections->contains(address)) {
        if (!devices->contains(address)) {
            API::sendEvent(std::format("{{ \"eventType\": \"error\", \"errorType\": \"deviceNotYetDiscovered\", \"address\": \"{0}\" }}\n",
                       address.toStdString()));
        }
        else {
            auto info = (*devices)[address];
            (*connections)[address] = new Connection(&info, this);
        }
    }
    else {
        auto connection = (*connections)[address];
        API::sendEvent(std::format("{{ \"eventType\": \"alreadyConnected\", \"address\": \"{0}\" }}\n", address.toStdString()));
    }
}

void Discoverer::disconnect(QString address) {
    if (connections->contains(address)) {
        auto connection = (*connections)[address];
        (*connections).remove(address);
        delete connection;
    } else {
        API::sendEvent(std::format("{{ \"eventType\": \"alreadyDisconnected\", \"address\": \"{0}\" }}\n", address.toStdString()));
    }
}

void Discoverer::process(const std::string &command) {
    auto commandDocument = QJsonDocument::fromJson(QString(command.c_str()).toUtf8());
    QJsonObject commandObject = commandDocument.object();
    auto commandType = commandObject["commandType"].toString();

    auto address = commandObject["address"].toString().toUpper();

    if (commandType == "connect") {
        auto address = commandObject["address"].toString().toUpper();
        connect(address);
    } else if (commandType == "disconnect") {
        auto address = commandObject["address"].toString().toUpper();
        disconnect(address);
    }
    else {
        auto parameters = CommonParameters::Load(commandObject);

        if (!connections->contains(address)) {
            API::sendEvent(std::format("{{ \"eventType\": \"error\", \"errorType\": \"deviceNotYetDiscovered\", \"address\": \"{0}\" }}\n",
                       address.toStdString()));
            return;
        }

        auto connection = (*connections)[address];

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
        } else if (commandType == "imageUpload") {
            auto image = commandObject["image"].toInt();
            auto fileName = commandObject["fileName"].toString();
            auto upgrade = commandObject["upgrade"].toBool();
            auto hashString = QByteArray::fromHex(commandObject["hashString"].toString().toLatin1());
            connection->imageUpload(image, fileName, upgrade, &hashString, parameters);
        }
    }
}
