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

#include "Connect.h"
#include "Connected.h"
#include "DeviceDiscovered.h"
#include "Disconnect.h"
#include "Disconnected.h"
#include "GetImages.h"
#include "Reset.h"
#include "ResetCompleted.h"
#include "ServiceDiscovered.h"
#include "ServiceDiscoveryFinished.h"
#include "SetImage.h"
#include "UploadImage.h"
#include "BootLoaderInfo.h"

using namespace qtmcumgr;

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

void Discoverer::handleConnect(Connect &connect) {
    if (!connections->contains(connect.getAddress())) {
        if (!devices->contains(connect.getAddress())) {
            API::sendEvent(std::format(R"({{ "eventType": "error", "errorType": "deviceNotYetDiscovered", "address": "{0}" }})",
                                       connect.getAddress().toStdString()));
        }
        else {
            auto info = (*devices)[connect.getAddress()];
            (*connections)[connect.getAddress()] = new Connection(&info, this);
        }
    }
    else {
        auto connection = (*connections)[connect.getAddress()];
        API::sendEvent(std::format(R"({{ "eventType": "alreadyConnected", "address": "{0}" }})", connect.getAddress().toStdString()));
    }
}

void Discoverer::handleDisconnect(Disconnect &disconnect) {
    if (connections->contains(disconnect.getAddress())) {
        auto connection = (*connections)[disconnect.getAddress()];
        (*connections).remove(disconnect.getAddress());
        delete connection;
    } else {
        API::sendEvent(std::format(R"({{ "eventType": "alreadyDisconnected", "address": "{0}" }})", disconnect.getAddress().toStdString()));
    }
}

void Discoverer::handleReset(Connection &connection, Reset &reset) {
    connection.reset(reset.getForce());
}

void Discoverer::handleGetImages(Connection &connection, GetImages &getImages) {
    if (getImages.hasConnectionParameters()) {
        connection.getImages(getImages.getConnectionParameters());
    }else {
        ConnectionParameters defaults;
        defaults.setDefaults();
        connection.getImages(defaults);
    }
}

void Discoverer::handleSetImage(Connection &connection, SetImage &image) {
    auto hash = new QByteArray(QByteArray::fromHex(image.getHashString().toLatin1()));
    connection.setImage(hash, image.getConfirm(), image.getConnectionParameters());
}

void Discoverer::handleUploadImage(Connection &connection, UploadImage &image) {
    connection.getImages(image.getConnectionParameters());
}

void Discoverer::handleBootLoaderInfo(Connection &connection, BootLoaderInfo &info) {
    if (!info.hasQuery()) {
        auto str = QString("");
        connection.bootLoaderInfo(str);
    }
    else {
        connection.bootLoaderInfo(info.getQuery());
    }
}

void Discoverer::process(const std::string &command) {
    auto commandDocument = QJsonDocument::fromJson(QString(command.c_str()).toUtf8()).object();
    auto commandType = commandDocument.value("commandType").toString();

    if (commandType == "connect") {
        Connect connect;
        if (Connect::TryLoad(commandDocument, connect)) {
            handleConnect(connect);
        }
        return;
    }

    if (commandType == "disconnect") {
        Disconnect disconnect;
        if (Disconnect::TryLoad(commandDocument, disconnect)) {
            handleDisconnect(disconnect);
        }
        return;
    }

    auto id = commandDocument["address"].toString();

    if (!connections->contains(id)) {
        API::sendEvent(std::format(R"({{ "eventType": "error", "errorType": "deviceNotYetDiscovered", "address": "{0}" }})",
                                   id.toStdString()));
        return;
    }

    auto connection = (*connections)[id];

    if (commandType == "getImages") {
        auto getImages = new GetImages();
        if (GetImages::TryLoad(commandDocument, *getImages)) {
            handleGetImages(*connection, *getImages);
        }
        return;
    }

    if (commandType == "reset") {
        auto reset = new Reset();
        if (Reset::TryLoad(commandDocument, *reset)) {
            handleReset(*connection, *reset);
        }
        return;
    }

    if(commandType == "setImage") {
        auto setImage = new SetImage();
        if (SetImage::TryLoad(commandDocument, *setImage)) {
            handleSetImage(*connection, *setImage);
        }
        return;
    }

    if (commandType == "uploadImage") {
        auto uploadImage = new UploadImage();
        if (UploadImage::TryLoad(commandDocument, *uploadImage)) {
            handleUploadImage(*connection, *uploadImage);
        }
        return;
    }

    if (commandType == "bootLoaderInfo") {
        auto bootLoaderInfo = new BootLoaderInfo();
        if (BootLoaderInfo::TryLoad(commandDocument, *bootLoaderInfo)) {
            handleBootLoaderInfo(*connection, *bootLoaderInfo);
        }
        return;
    }
}
