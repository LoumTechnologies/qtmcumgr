//
// Created by loum-technologies on 4/18/2024.
//

#ifndef QTMCUMGR_DISCOVERER_H
#define QTMCUMGR_DISCOVERER_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
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
    void discovery_finished();

public:
    smp_transport *transport;
    smp_processor *processor;
    smp_group_array *smp_groups;
    QLowEnergyController *controller;
    bool isConnected = false;
    bool isDeleting = false;

private:
    QBluetoothDeviceInfo *info;
};

class Discoverer : QObject {
    Q_OBJECT

public:
    explicit Discoverer();
    ~Discoverer();
    void start();
    void process(const std::string &command);

public slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void finished();

    void connect(QString address);

    void disconnect(QString address);

    void reset(QString address, bool force);

private:
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QMap<QString, Connection*> *connections;
    QMap<QString, QBluetoothDeviceInfo> *devices;
};


#endif //QTMCUMGR_DISCOVERER_H
