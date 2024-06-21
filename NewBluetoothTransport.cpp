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
        QObject::disconnect(connection, &BluetoothConnection::characteristicChanged, this, &NewBluetoothTransport::characteristicChanged);
        QObject::disconnect(connection, &BluetoothConnection::characteristicWritten, this, &NewBluetoothTransport::characteristicWritten);
        QObject::disconnect(connection, &BluetoothConnection::errorOccurred, this, &NewBluetoothTransport::errorOccurred);
        delete connection;
        connection = nullptr;
    }
}

void NewBluetoothTransport::form_connect_to_device(const QBluetoothDeviceInfo &info) {
    if (connection != nullptr) {
        QObject::disconnect(connection, &BluetoothConnection::characteristicChanged, this, &NewBluetoothTransport::characteristicChanged);
        QObject::disconnect(connection, &BluetoothConnection::characteristicWritten, this, &NewBluetoothTransport::characteristicWritten);
        QObject::disconnect(connection, &BluetoothConnection::errorOccurred, this, &NewBluetoothTransport::errorOccurred);
        delete connection;
        connection = nullptr;
    }
    if (mInfo != nullptr) {
        delete mInfo;
        mInfo = nullptr;
    }
    mInfo = new QBluetoothDeviceInfo(info);
    connection = new BluetoothConnection(info, this);
    QObject::connect(connection, &BluetoothConnection::characteristicChanged, this, &NewBluetoothTransport::characteristicChanged);
    QObject::connect(connection, &BluetoothConnection::characteristicWritten, this, &NewBluetoothTransport::characteristicWritten);
    QObject::connect(connection, &BluetoothConnection::errorOccurred, this, &NewBluetoothTransport::errorOccurred);
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
        QObject::disconnect(connection, &BluetoothConnection::characteristicChanged, this, &NewBluetoothTransport::characteristicChanged);
        QObject::disconnect(connection, &BluetoothConnection::characteristicWritten, this, &NewBluetoothTransport::characteristicWritten);
        QObject::disconnect(connection, &BluetoothConnection::errorOccurred, this, &NewBluetoothTransport::errorOccurred);
        delete connection;
        connection = nullptr;
    }
    connection = new BluetoothConnection(*mInfo, this);
    QObject::connect(connection, &BluetoothConnection::characteristicChanged, this, &NewBluetoothTransport::characteristicChanged);
    QObject::connect(connection, &BluetoothConnection::characteristicWritten, this, &NewBluetoothTransport::characteristicWritten);
    QObject::connect(connection, &BluetoothConnection::errorOccurred, this, &NewBluetoothTransport::errorOccurred);
    return 0;
}

int NewBluetoothTransport::disconnect(bool force) {
    if (connection != nullptr) {
        QObject::disconnect(connection, &BluetoothConnection::characteristicChanged, this, &NewBluetoothTransport::characteristicChanged);
        QObject::disconnect(connection, &BluetoothConnection::characteristicWritten, this, &NewBluetoothTransport::characteristicWritten);
        QObject::disconnect(connection, &BluetoothConnection::errorOccurred, this, &NewBluetoothTransport::errorOccurred);
        delete connection;
        connection = nullptr;
    }
    return 0;
}

QString NewBluetoothTransport::address() {
    if (mInfo == nullptr) {
        return QString("");
    }
    return mInfo->address().toString();
}

void NewBluetoothTransport::characteristicWritten(const QLowEnergyCharacteristic &characteristic, const QByteArray &baData) {
    qDebug() << baData;

    if (baData.length() > mtu_max_worked)
    {
        mtu_max_worked = baData.length();
    }

    retry_count = 0;

    if (connection == nullptr) {
        return;
    }
    auto bluetooth_service_mcumgr = connection->getMcumgrService();
    if (bluetooth_service_mcumgr == nullptr) {
        return;
    }
    auto bluetooth_characteristic_transmit = connection->getTransmitCharacteristic();
    if (!bluetooth_characteristic_transmit.isValid())
    {
        return;
    }

    if (sendbuffer.length() > 0)
    {
        sendbuffer.remove(0, baData.length());

        if (sendbuffer.length() > 0)
        {
            bluetooth_service_mcumgr->writeCharacteristic(bluetooth_characteristic_transmit, sendbuffer.left(mtu));
        }
    }
}

void NewBluetoothTransport::errorOccurred(QLowEnergyService::ServiceError newError) {
    if (newError == QLowEnergyService::CharacteristicWriteError)
    {
        qDebug() << "send failed with mtu " << mtu;

        ++retry_count;

        if (connection == nullptr) {
            return;
        }
        auto bluetooth_service_mcumgr = connection->getMcumgrService();
        if (bluetooth_service_mcumgr == nullptr) {
            return;
        }
        auto bluetooth_characteristic_transmit = connection->getTransmitCharacteristic();
        if (!bluetooth_characteristic_transmit.isValid())
        {
            return;
        }

        if (retry_count > 2)
        {
            retry_count = 0;

            if (mtu >= 25)
            {
                if (mtu >= 100)
                {
                    mtu -= 32;
                }
                else
                {
                    mtu -= 16;
                }

                bluetooth_service_mcumgr->writeCharacteristic(bluetooth_characteristic_transmit, sendbuffer.left(mtu));
            }
            else
            {
                sendbuffer.clear();
            }
        }
        else
        {
            retry_timer.start();
        }
    }
}

void NewBluetoothTransport::characteristicChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &baData) {
    received_data.append(&baData);

    if (received_data.is_valid() == true)
    {
        emit receive_waiting(&received_data);
        received_data.clear();
    }
}

void NewBluetoothTransport::silenceDisconnectionMessages() {
    if (connection != nullptr) {
        connection->silenceDisconnectionMessages();
    }
}
