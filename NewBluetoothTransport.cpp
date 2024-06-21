//
// Created by loum-technologies on 6/20/2024.
//

#include "NewBluetoothTransport.h"

//Aim for a connection interval of between 7.5us-30us with a 4 second supervision timeout
const double connection_interval_min = 7.5;
const double connection_interval_max = 30;
const int connection_latency = 0;
const int connection_supervision_timeout = 4000;

//Default MTU of 490 - less than 512 maximum with a bit of safety
const int default_mtu = 490;

NewBluetoothTransport::NewBluetoothTransport() {
    connection = nullptr;
    mInfo = nullptr;
    mtu = default_mtu;
    mtu_max_worked = 0;
}

NewBluetoothTransport::~NewBluetoothTransport() {
    if (connection != nullptr) {
        delete connection;
    }
}

void NewBluetoothTransport::form_connect_to_device(const QBluetoothDeviceInfo &info) {
    if (mInfo != nullptr) {
        delete mInfo;
    }
    mInfo = new QBluetoothDeviceInfo(info);
    connection = new BluetoothConnection(info, this);
}

int NewBluetoothTransport::is_connected() {
    if (connection == nullptr) {
        return 0;
    }

    if (connection->isConnected()) {
        return 1;
    }

    return 0;
}

int NewBluetoothTransport::send(smp_message *message)
{
    retry_count = 0;
    sendbuffer.clear();

    if (mtu < mtu_max_worked)
    {
        mtu = mtu_max_worked;
    }

    if (connection == nullptr) {
        return 0;
    }
    auto bluetooth_service_mcumgr = connection->getMcumgrService();
    if (bluetooth_service_mcumgr == nullptr) {
        return 0;
    }
    auto bluetooth_characteristic_transmit = connection->getTransmitCharacteristic();
    if (!bluetooth_characteristic_transmit.isValid())
    {
        return 0;
    }

    sendbuffer.append(*message->data());
    bluetooth_service_mcumgr->writeCharacteristic(bluetooth_characteristic_transmit, sendbuffer.left(mtu));
//    bluetooth_window->add_debug(QString("Writing ").append(QString::number(mtu)).append(sendbuffer.left(mtu)));

    return 0;
}

int NewBluetoothTransport::connect() {
    if (connection != nullptr) {
        delete connection;
    }
    connection = new BluetoothConnection(*mInfo, this);
    return 0;
}

int NewBluetoothTransport::disconnect(bool force) {
    if (connection != nullptr) {
        delete connection;
    }
}

QString NewBluetoothTransport::address() {
    if (mInfo == nullptr) {
        return QString("");
    }
    return mInfo->address().toString();
}
