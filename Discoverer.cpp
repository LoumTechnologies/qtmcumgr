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
#include "smp_group_settings_mgmt.h"
#include "smp_group_shell_mgmt.h"
#include "smp_group_stat_mgmt.h"
#include "smp_group_zephyr_mgmt.h"
#include "smp_processor.h"
#include <QString>
#include <QJsonObject>

#include "smp_bluetooth.h"

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

    std::print(
        "{{ \"eventType\": \"deviceDiscovered\", \"address\": \"{0}\", \"name\": \"{1}\", \"cached\": {2}, \"valid\": {3}, \"rssi\": {4}, \"majorDeviceClass\": \"{5}\", \"minorDeviceClass\": {6} }}\n",
        info.address().toString().toStdString(),
        info.name().toStdString(),
        cached,
        valid,
        info.rssi(),
        majorDeviceClass.toStdString(),
        info.minorDeviceClass()
    );
    std::flush(std::cout);
    (*devices)[info.address().toString().toUpper()] = info;

    //connect(info.address().toString().toUpper());
}

void Discoverer::start()
{
    discoveryAgent->start();
    std::print("{{ \"eventType\": \"deviceScanningStarted\" }}\n");
    std::flush(std::cout);
}

void Discoverer::finished() {
    std::print("{{ \"eventType\": \"deviceScanningEnded\" }}\n");
    std::flush(std::cout);
}

void Discoverer::connect(QString address) {
    if (!connections->contains(address)) {
        if (!devices->contains(address)) {
            std::print("{{ \"eventType\": \"error\", \"errorType\": \"deviceNotYetDiscovered\", \"address\": \"{0}\" }}\n",
                       address.toStdString());
        }
        else {
            auto info = (*devices)[address];
            (*connections)[address] = new Connection(&info, this);
        }
    }
    else {
        auto connection = (*connections)[address];
        if (connection->isConnected) {
            std::print("{{ \"eventType\": \"alreadyConnected\", \"address\": \"{0}\" }}\n", address.toStdString());
        } else {
            delete connection;
            connections->remove(address);
            connect(address);
        }
    }
}

void Discoverer::disconnect(QString address) {
    if (connections->contains(address)) {
        auto connection = (*connections)[address];
        (*connections).remove(address);
        delete connection;
    } else {
        std::print("{{ \"eventType\": \"alreadyDisconnected\", \"address\": \"{0}\" }}\n", address.toStdString());
    }
}

void Discoverer::reset(QString address, bool force) {
    if (!connections->contains(address)) {
        std::print("{{ \"eventType\": \"error\", \"errorType\": \"deviceNotYetDiscovered\", \"address\": \"{0}\" }}\n",
                   address.toStdString());
    } else {
        auto connection = (*connections)[address];
        connection->smp_groups->os_mgmt->start_reset(force);
    }
}

void Discoverer::process(const std::string &command) {
    auto commandDocument = QJsonDocument::fromJson(QString(command.c_str()).toUtf8());
    QJsonObject commandObject = commandDocument.object();

    if (commandObject["commandType"] == "connect") {
        auto address = commandObject["address"].toString().toUpper();
        connect(address);
    } else if (commandObject["commandType"] == "disconnect") {
        auto address = commandObject["address"].toString().toUpper();
        disconnect(address);
    } else if (commandObject["commandType"] == "reset") {
        auto address = commandObject["address"].toString().toUpper();
        auto force = commandObject["force"].toBool();
        reset(address, force);
    }
}
