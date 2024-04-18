//
// Created by loum-technologies on 4/18/2024.
//

#ifndef QTMCUMGR_DISCOVERER_H
#define QTMCUMGR_DISCOVERER_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>


class Discoverer : QObject {
    Q_OBJECT

public:
    explicit Discoverer();
    ~Discoverer();
    void start();

public slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &info);

signals:
    void finished();

private:
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
};


#endif //QTMCUMGR_DISCOVERER_H
