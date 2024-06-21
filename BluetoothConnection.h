//
// Created by loum-technologies on 6/20/2024.
//

#ifndef QTMCUMGR_BLUETOOTHCONNECTION_H
#define QTMCUMGR_BLUETOOTHCONNECTION_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyConnectionParameters>
#include <QLowEnergyController>

/// This class's sole responsibility is to get a valid transmit characteristic for mcumgr for a single bluetooth device.
class BluetoothConnection : public QObject
{
    Q_OBJECT

public:
    BluetoothConnection(const QBluetoothDeviceInfo &info, QObject *parent = nullptr);
    ~BluetoothConnection();
    void silenceDisconnectionMessages();

private slots:
    // Slots for the connection
    void deviceConnected();
    void deviceConnectionUpdated(const QLowEnergyConnectionParameters &newParameters);
    void deviceDisconnected();
    void deviceDiscoveryFinished();
    void deviceErrorOccurred(QLowEnergyController::Error newError);
    void deviceMtuChanged(int mtu);
    void deviceRssiRead(qint16 rssi);
    void deviceServiceDiscovered(const QBluetoothUuid &newService);
    void deviceStateChanged(QLowEnergyController::ControllerState state);

    // Slots for the mcumgr_service
    void serviceCharacteristicChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
    void serviceCharacteristicRead(const QLowEnergyCharacteristic &characteristic, const QByteArray &value);
    void serviceCharacteristicWritten(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
    void serviceDescriptorRead(const QLowEnergyDescriptor &descriptor, const QByteArray &value);
    void serviceDescriptorWritten(const QLowEnergyDescriptor &descriptor, const QByteArray &newValue);
    void serviceErrorOccurred(QLowEnergyService::ServiceError newError);
    void serviceStateChanged(QLowEnergyService::ServiceState newState);

signals:

    void characteristicChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
    void characteristicWritten(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
    void errorOccurred(QLowEnergyService::ServiceError newError);

public:
    QLowEnergyController *getController();
    QLowEnergyService *getMcumgrService();
    QLowEnergyCharacteristic getTransmitCharacteristic();
    bool isConnected();

private:
    QBluetoothDeviceInfo mInfo;
    QLowEnergyController *controller;
    QLowEnergyService *mcumgr_service;
    QLowEnergyCharacteristic transmit_characteristic;
    bool isConnecting;
    bool _silenceDisconnectionMessages;
};


#endif //QTMCUMGR_BLUETOOTHCONNECTION_H
