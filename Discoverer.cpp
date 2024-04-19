//
// Created by loum-technologies on 4/18/2024.
//

#include "Discoverer.h"
//#include "Discoverer.moc"
#include <QIODevice>
#include <print>
#include <iostream>
#include "json.hpp"

Discoverer::Discoverer()
{
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    discoveryAgent->setLowEnergyDiscoveryTimeout(0);
    QObject::connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    QObject::connect(discoveryAgent, SIGNAL(finished()), this, SLOT(finished()));
}

Discoverer::~Discoverer()
{
    if (discoveryAgent != nullptr) {
        delete discoveryAgent;
        discoveryAgent = nullptr;
    }
}

void Discoverer::deviceDiscovered(const QBluetoothDeviceInfo &info)
{
    std::print(
        "{{ \"eventType\": \"DeviceDiscovered\", \"address\": \"{0}\", \"name\": \"{1}\" }}\n",
        info.address().toString().toStdString(),
        info.name().toStdString()
    );
    std::flush(std::cout);
}

void Discoverer::start()
{
    discoveryAgent->start();
}

void Discoverer::finished() {
    std::print("{{ \"eventType\": \"DeviceScanningEnded\" }}\n");
    std::flush(std::cout);
}

void Discoverer::process(std::string command) {

}
