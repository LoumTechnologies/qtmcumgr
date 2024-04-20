//
// Created by loum-technologies on 4/18/2024.
//

#ifndef QTMCUMGR_DISCOVERER_H
#define QTMCUMGR_DISCOVERER_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>

#include "smp_group_array.h"
#include "smp_processor.h"


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
    QMap<QString, smp_transport*> *transports;
};


#endif //QTMCUMGR_DISCOVERER_H
