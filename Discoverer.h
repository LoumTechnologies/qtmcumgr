//
// Created by loum-technologies on 4/18/2024.
//

#ifndef QTMCUMGR_DISCOVERER_H
#define QTMCUMGR_DISCOVERER_H

#include <QBluetoothDeviceDiscoveryAgent>

#include "smp_group_array.h"
#include "Connection.h"

class Discoverer : QObject {
    Q_OBJECT

public:
    explicit Discoverer();
    ~Discoverer();
    void process(const std::string &command);

public slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void finished();
    void connect(QString id);
    void disconnect(QString id);
    void start();

private:
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QMap<QString, Connection*> *connections;
    QMap<QString, QBluetoothDeviceInfo> *devices;
};


#endif //QTMCUMGR_DISCOVERER_H
