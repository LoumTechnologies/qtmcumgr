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

Connection::Connection(const QBluetoothDeviceInfo &info, QObject *parent) {
    auto bluetooth_transport = new smp_bluetooth();
    transport = bluetooth_transport;
    processor = new smp_processor(parent);
    processor->set_transport(transport);

    bluetooth_transport->form_connect_to_device(info);

    this->processor = new smp_processor(parent);
    this->smp_groups = new smp_group_array();
    smp_groups->fs_mgmt = new smp_group_fs_mgmt(processor);
    smp_groups->img_mgmt = new smp_group_img_mgmt(processor);
    smp_groups->os_mgmt = new smp_group_os_mgmt(processor);
    smp_groups->settings_mgmt = new smp_group_settings_mgmt(processor);
    smp_groups->shell_mgmt = new smp_group_shell_mgmt(processor);
    smp_groups->stat_mgmt = new smp_group_stat_mgmt(processor);
    smp_groups->zephyr_mgmt = new smp_group_zephyr_mgmt(processor);
}

Connection::~Connection() {
    delete smp_groups->fs_mgmt;
    delete smp_groups->img_mgmt;
    delete smp_groups->os_mgmt;
    delete smp_groups->settings_mgmt;
    delete smp_groups->shell_mgmt;
    delete smp_groups->stat_mgmt;
    delete smp_groups->zephyr_mgmt;
    delete smp_groups;
    delete processor;
    delete transport;
}

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
    std::print(
        "{{ \"eventType\": \"DeviceDiscovered\", \"address\": \"{0}\", \"name\": \"{1}\" }}\n",
        info.address().toString().toStdString(),
        info.name().toStdString()
    );
    std::flush(std::cout);
    (*devices)[info.address().toString()] = info;
}

void Discoverer::start()
{
    discoveryAgent->start();
    std::print("{{ \"eventType\": \"DeviceScanningStarted\" }}\n");
    std::flush(std::cout);
}

void Discoverer::finished() {
    std::print("{{ \"eventType\": \"DeviceScanningEnded\" }}\n");
    std::flush(std::cout);
}

void Discoverer::process(const std::string &command) {
    auto commandDocument = QJsonDocument::fromJson(QString(command.c_str()).toUtf8());
    QJsonObject commandObject = commandDocument.object();

    if (commandObject["commandType"] == "connect") {
        auto address = commandObject["address"].toString();
        if (!connections->contains(address)) {
            auto info = (*devices)[address];
            (*connections)[address] = new Connection(info);
            std::print("{{ \"eventType\": \"Connected\", \"address\": \"{0}\" }}\n", address.toStdString());
        }
        else {
            std::print("{{ \"eventType\": \"AlreadyConnected\", \"address\": \"{0}\" }}\n", address.toStdString());
        }
    }
    else if (commandObject["commandType"] == "disconnect") {
        auto address = commandObject["address"].toString();
        if (connections->contains(address)) {
            auto transport = (*connections)[address];
            (*connections).remove(address);
            delete transport;
            std::print("{{ \"eventType\": \"Disconnected\", \"address\": \"{0}\" }}\n", address.toStdString());
        } else {
            std::print("{{ \"eventType\": \"AlreadyDisconnected\", \"address\": \"{0}\" }}\n", address.toStdString());
        }
    }
    else if (commandObject["commandType"] == "reset") {
        auto address = commandObject["address"].toString();
        auto force = commandObject["force"].toBool();
        auto connection = (*connections)[address];
        connection->smp_groups->os_mgmt->start_reset(force);
        std::print("{{ \"eventType\": \"Reset\", \"address\": \"{0}\" }}\n", address.toStdString());
    }
}
