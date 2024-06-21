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

private slots:
    // Slots for the connection
    void connected();
    void connectionUpdated(const QLowEnergyConnectionParameters &newParameters);
    void disconnected();
    void discoveryFinished();
    void errorOccurred(QLowEnergyController::Error newError);
    void mtuChanged(int mtu);
    void rssiRead(qint16 rssi);
    void serviceDiscovered(const QBluetoothUuid &newService);
    void stateChanged(QLowEnergyController::ControllerState state);

    // Slots for the mcumgr_service
    void serviceCharacteristicChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
    void serviceCharacteristicRead(const QLowEnergyCharacteristic &characteristic, const QByteArray &value);
    void serviceCharacteristicWritten(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
    void serviceDescriptorRead(const QLowEnergyDescriptor &descriptor, const QByteArray &value);
    void serviceDescriptorWritten(const QLowEnergyDescriptor &descriptor, const QByteArray &newValue);
    void serviceErrorOccurred(QLowEnergyService::ServiceError newError);
    void serviceStateChanged(QLowEnergyService::ServiceState newState);

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
};


#endif //QTMCUMGR_BLUETOOTHCONNECTION_H
