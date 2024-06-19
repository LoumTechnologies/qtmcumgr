//
// Created by loum-technologies on 6/19/2024.
//

#ifndef SIMPLETCPSERVER_BLUETOOTHDEVICEMANAGER_H
#define SIMPLETCPSERVER_BLUETOOTHDEVICEMANAGER_H


#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include "Connection.h"

class BluetoothDeviceManager : public QObject {
Q_OBJECT

public:
    BluetoothDeviceManager();
    ~BluetoothDeviceManager();
    void start();

public:

    void connect(QString &address);
    void disconnect(QString &address);
    void getImages(QString &address, CommonParameters &parameters);
    void uploadImage(QString &address, int image, QString &fileName, bool upgrade, CommonParameters commonParameters);
    void setImage(QString &address, QString &hashString, bool confirm, CommonParameters &commonParameters);
    void reset(QString &address, bool force);

private:
    void onDeviceDiscovered(const QBluetoothDeviceInfo &info);
    void onDeviceDiscoveryFinished();
    void onDeviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error error);

    QMap<QString, Connection*> connections;
    QBluetoothDeviceDiscoveryAgent discoveryAgent;
    QMap<QString, const QBluetoothDeviceInfo *> devices;
};


#endif //SIMPLETCPSERVER_BLUETOOTHDEVICEMANAGER_H
