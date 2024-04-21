//
// Created by loum-technologies on 4/18/2024.
//

#ifndef QTMCUMGR_DISCOVERER_H
#define QTMCUMGR_DISCOVERER_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>

#include "smp_group_array.h"
#include "smp_processor.h"

class Connection {
public:
    Connection(QString address, QObject *parent = nullptr);
    ~Connection();
private:
    smp_transport *transport;
    smp_processor *processor;
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

private:
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    smp_processor *processor;
    smp_group_array *smp_groups;
    QMap<QString, Connection*> *connections;
};


#endif //QTMCUMGR_DISCOVERER_H
