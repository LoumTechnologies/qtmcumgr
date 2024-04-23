//
// Created by loumtechnologies on 4/23/2024.
//

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QLowEnergyController>
#include "smp_group_array.h"
#include "smp_processor.h"

class Connection : QObject {
    Q_OBJECT

public:
    Connection(QBluetoothDeviceInfo *info, QObject *parent = nullptr);
    ~Connection();

private slots:

    void connected();
    void disconnected();
    void discoveryFinished();
    void serviceDiscovered(QBluetoothUuid uuid);
    void errorz(QLowEnergyController::Error error);

public:
    smp_transport *transport;
    smp_processor *processor;
    smp_group_array *smp_groups;
    QLowEnergyController *controller;
    bool isConnected = false;
    bool isDeleting = false;
};



#endif //CONNECTION_H
