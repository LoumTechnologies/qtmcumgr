//
// Created by loumtechnologies on 4/23/2024.
//

#include "Connection.h"
#include <QTimer>
#include <print>

Connection::Connection(QBluetoothDeviceInfo *info, QObject *parent) : QObject(parent) {
    this->info = info;
    controller = QLowEnergyController::createCentral(*info);
    //controller->setParent(this);

    connect(controller, SIGNAL(connected()), this, SLOT(connected()));
    connect(controller, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(controller, SIGNAL(discoveryFinished()), this, SLOT(discoveryFinished()));
    connect(controller, SIGNAL(serviceDiscovered(QBluetoothUuid)), this, SLOT(serviceDiscovered(QBluetoothUuid)));
    connect(controller, SIGNAL(error(QLowEnergyController::Error)), this, SLOT(errorz(QLowEnergyController::Error)));
    // [&]() {
    //     std::print("{{ \"eventType\": \"connected\", \"address\": \"{0}\" }}\n", info.address().toString().toStdString());
    //     this->isConnected = true;
    //     controller->discoverServices();
    // });
    // connect(controller, &QLowEnergyController::disconnected, this, [&]() {
    //     if (isDeleting) {
    //         return;
    //     }
    //     std::print("{{ \"eventType\": \"disconnected\", \"address\": \"{0}\" }}\n", info.address().toString().toStdString());
    // });
    // connect(controller, &QLowEnergyController::discoveryFinished, this, [&]() {
    //     std::print("{{ \"eventType\": \"doneDiscoveringServices\", \"address\": \"{0}\" }}\n", info.address().toString().toStdString());
    // });

    //std::print("{{ \"eventType\": \"connectionStarted\", \"address\": \"{0}\" }}\n", info->address().toString().toStdString());
    controller->setRemoteAddressType(QLowEnergyController::RandomAddress);
    controller->connectToDevice();

    //auto bluetooth_transport = new smp_bluetooth(parent);
    //transport = bluetooth_transport;

    // processor = new smp_processor(parent);
    // processor->set_transport(transport);
    // smp_groups = new smp_group_array();
    // smp_groups->fs_mgmt = new smp_group_fs_mgmt(processor);
    // smp_groups->img_mgmt = new smp_group_img_mgmt(processor);
    // smp_groups->os_mgmt = new smp_group_os_mgmt(processor);
    // smp_groups->settings_mgmt = new smp_group_settings_mgmt(processor);
    // smp_groups->shell_mgmt = new smp_group_shell_mgmt(processor);
    // smp_groups->stat_mgmt = new smp_group_stat_mgmt(processor);
    // smp_groups->zephyr_mgmt = new smp_group_zephyr_mgmt(processor);
    //
    // bluetooth_transport->form_connect_to_device(*info);
}

Connection::~Connection() {
    controller->disconnect();

    disconnect(controller, SIGNAL(connected()), this, SLOT(connected()));
    disconnect(controller, SIGNAL(disconnected()), this, SLOT(disconnected()));
    disconnect(controller, SIGNAL(discoveryFinished()), this, SLOT(discoveryFinished()));

    isDeleting = true;
    delete controller;
    // delete smp_groups->fs_mgmt;
    // delete smp_groups->img_mgmt;
    // delete smp_groups->os_mgmt;
    // delete smp_groups->settings_mgmt;
    // delete smp_groups->shell_mgmt;
    // delete smp_groups->stat_mgmt;
    // delete smp_groups->zephyr_mgmt;
    // delete smp_groups;
    // delete processor;
    // delete transport;
    // delete controller;
}

void Connection::connected() {
    std::print("{{ \"eventType\": \"connected\", \"address\": \"{0}\" }}\n", info->address().toString().toStdString());
    this->isConnected = true;
    controller->discoverServices();
}

void Connection::disconnected() {
    if (isDeleting) {
        return;
    }
    std::print("{{ \"eventType\": \"disconnected\", \"address\": \"{0}\" }}\n", info->address().toString().toStdString());
}

void Connection::discoveryFinished() {
    std::print("{{ \"eventType\": \"serviceDiscoveryFinished\", \"address\": \"{0}\" }}\n", info->address().toString().toStdString());
}

void Connection::serviceDiscovered(QBluetoothUuid uuid) {
    auto str = uuid.toString(QUuid::WithoutBraces).toStdString();
    std::print("{{ \"eventType\": \"serviceDiscovered\", \"address\": \"{0}\", \"service\": \"{1}\" }}\n",
        info->address().toString().toStdString(),
        str
    );
}

void Connection::errorz(QLowEnergyController::Error error) {
    QString errorString;
    if (error == QLowEnergyController::Error::NoError) errorString = "NoError";
    else if (error == QLowEnergyController::Error::UnknownError) errorString = "UnknownError";
    else if (error == QLowEnergyController::Error::UnknownRemoteDeviceError) errorString = "UnknownRemoteDeviceError";
    else if (error == QLowEnergyController::Error::NetworkError) errorString = "NetworkError";
    else if (error == QLowEnergyController::Error::InvalidBluetoothAdapterError) errorString = "InvalidBluetoothAdapterError";
    else if (error == QLowEnergyController::Error::ConnectionError) errorString = "ConnectionError";
    else if (error == QLowEnergyController::Error::AdvertisingError) errorString = "AdvertisingError";
    else if (error == QLowEnergyController::Error::RemoteHostClosedError) errorString = "RemoteHostClosedError";
    else if (error == QLowEnergyController::Error::AuthorizationError) errorString = "AuthorizationError";
    else if (error == QLowEnergyController::Error::MissingPermissionsError) errorString = "MissingPermissionsError";
    else if (error == QLowEnergyController::Error::RssiReadError) errorString = "RssiReadError";
    else errorString = "UnlistedError";
    std::print("{{ \"eventType\": \"error\", \"errorType\": \"{0}\", \"address\": \"{1}\" }}\n",
        errorString.toStdString(),
        info->address().toString().toStdString()
    );
}
