//
// Created by loum-technologies on 6/19/2024.
//

#include <iostream>
#include "BluetoothDeviceManager.h"
#include "API.h"

BluetoothDeviceManager::BluetoothDeviceManager() {
    QObject::connect(&discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BluetoothDeviceManager::onDeviceDiscovered);
    QObject::connect(&discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &BluetoothDeviceManager::onDeviceDiscoveryFinished);
    QObject::connect(&discoveryAgent, &QBluetoothDeviceDiscoveryAgent::errorOccurred, this, &BluetoothDeviceManager::onDeviceDiscoveryError);
}

BluetoothDeviceManager::~BluetoothDeviceManager() {
    QObject::disconnect(&discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BluetoothDeviceManager::onDeviceDiscovered);
    QObject::disconnect(&discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &BluetoothDeviceManager::onDeviceDiscoveryFinished);
    QObject::disconnect(&discoveryAgent, &QBluetoothDeviceDiscoveryAgent::errorOccurred, this, &BluetoothDeviceManager::onDeviceDiscoveryError);

    for(auto item : connections) {
        delete item;
    }
    for(auto item : devices) {
        delete item;
    }
}

void BluetoothDeviceManager::onDeviceDiscovered(const QBluetoothDeviceInfo &info) {
    auto address = info.address().toString();

    if (address == "00:00:00:00:00:00")
    {
        address = info.deviceUuid().toString(QUuid::WithoutBraces);
    }

    if (devices.contains(address))
    {
        return;
    }

    auto newInfo = new QBluetoothDeviceInfo(info);

    devices[address] = newInfo;

    auto cached = info.isCached() ? "true" : "false";
    auto valid = info.isValid() ? "true" : "false";
    QString majorDeviceClass;
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::MiscellaneousDevice) {
        majorDeviceClass = "MiscellaneousDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::ComputerDevice) {
        majorDeviceClass = "ComputerDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::PhoneDevice) {
        majorDeviceClass = "PhoneDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::NetworkDevice) {
        majorDeviceClass = "NetworkDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::AudioVideoDevice) {
        majorDeviceClass = "AudioVideoDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::PeripheralDevice) {
        majorDeviceClass = "PeripheralDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::ImagingDevice) {
        majorDeviceClass = "ImagingDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::WearableDevice) {
        majorDeviceClass = "WearableDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::ToyDevice) {
        majorDeviceClass = "ToyDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::HealthDevice) {
        majorDeviceClass = "HealthDevice";
    }
    if (info.majorDeviceClass() == QBluetoothDeviceInfo::MajorDeviceClass::UncategorizedDevice) {
        majorDeviceClass = "UncategorizedDevice";
    }

    API::sendEvent(std::format(
            R"({{ "eventType": "deviceDiscovered", "address": "{0}", "deviceUuid": "{7}", "name": "{1}", "cached": {2}, "valid": {3}, "rssi": {4}, "majorDeviceClass": "{5}", "minorDeviceClass": {6} }})",
            info.address().toString().toStdString(),
            info.name().toStdString(),
            cached,
            valid,
            info.rssi(),
            majorDeviceClass.toStdString(),
            info.minorDeviceClass(),
            info.deviceUuid().toString(QUuid::WithoutBraces).toStdString()
    ));
}

void BluetoothDeviceManager::start() {
    discoveryAgent.start();
}

void BluetoothDeviceManager::onDeviceDiscoveryFinished() {
    discoveryAgent.start();
}

void BluetoothDeviceManager::onDeviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error error) {
    switch(error) {
        case QBluetoothDeviceDiscoveryAgent::Error::NoError:
            std::cout << "NoError" << std::endl;
            break;
        case QBluetoothDeviceDiscoveryAgent::Error::InputOutputError:
            std::cout << "InputOutputError" << std::endl;
            break;
        case QBluetoothDeviceDiscoveryAgent::Error::PoweredOffError:
            std::cout << "PoweredOffError" << std::endl;
            break;
        case QBluetoothDeviceDiscoveryAgent::Error::InvalidBluetoothAdapterError:
            std::cout << "InvalidBluetoothAdapterError" << std::endl;
            break;
        case QBluetoothDeviceDiscoveryAgent::Error::UnsupportedPlatformError:
            std::cout << "UnsupportedPlatformError" << std::endl;
            break;
        case QBluetoothDeviceDiscoveryAgent::Error::UnsupportedDiscoveryMethod:
            std::cout << "UnsupportedDiscoveryMethod" << std::endl;
            break;
        case QBluetoothDeviceDiscoveryAgent::Error::LocationServiceTurnedOffError:
            std::cout << "LocationServiceTurnedOffError" << std::endl;
            break;
        case QBluetoothDeviceDiscoveryAgent::Error::MissingPermissionsError:
            std::cout << "MissingPermissionsError" << std::endl;
            break;
        case QBluetoothDeviceDiscoveryAgent::Error::UnknownError:
            std::cout << "UnknownError" << std::endl;
            break;
        default:
            std::cout << "OtherError: " << (int)error << std::endl;
            break;
    }
}

void BluetoothDeviceManager::connect(QString &address) {
    if (!connections.contains(address)) {
        if (!devices.contains(address)) {
            API::sendEvent(std::format(R"({{ "eventType": "error", "errorType": "deviceNotYetDiscovered", "address": "{0}" }})",
                                       address.toStdString()));
        }
        else {
            auto info = devices[address];
            connections[address] = new Connection(*info, this);
        }
    }
    else {
        auto connection = connections[address];
        API::sendEvent(std::format(R"({{ "eventType": "alreadyConnected", "address": "{0}" }})", address.toStdString()));
    }
}

void BluetoothDeviceManager::disconnect(QString &address) {
    if (connections.contains(address)) {
        auto connection = connections[address];
        connections.remove(address);
        delete connection;
        API::sendEvent(std::format(R"({{ "eventType": "disconnected", "address": "{0}" }})", address.toStdString()));
    } else {
        API::sendEvent(std::format(R"({{ "eventType": "alreadyDisconnected", "address": "{0}" }})", address.toStdString()));
    }
}

void BluetoothDeviceManager::getImages(QString &address, CommonParameters &parameters) {
    if (!connections.contains(address)) {
        API::sendEvent(std::format(R"({{ "eventType": "error", "errorType": "deviceNotYetDiscovered", "address": "{0}" }})",
                                   address.toStdString()));
        return;
    }
    auto connection = connections[address];
    connection->getImages(parameters);
}

void BluetoothDeviceManager::reset(QString &address, bool force) {
    if (!connections.contains(address)) {
        API::sendEvent(std::format(R"({{ "eventType": "error", "errorType": "deviceNotYetDiscovered", "address": "{0}" }})",
                                   address.toStdString()));
        return;
    }
    auto connection = connections[address];
    connection->reset(force);
}

void BluetoothDeviceManager::setImage(QString &address, QString &hashString, bool confirm, CommonParameters &commonParameters) {
    if (!connections.contains(address)) {
        API::sendEvent(std::format(R"({{ "eventType": "error", "errorType": "deviceNotYetDiscovered", "address": "{0}" }})",
                                   address.toStdString()));
        return;
    }
    auto connection = connections[address];
    connection->setImage( new QByteArray(QByteArray::fromHex(hashString.toLatin1())), confirm, commonParameters);
}

void BluetoothDeviceManager::uploadImage(QString &address, int image, QString &fileName, bool upgrade,
                                         CommonParameters commonParameters) {
    if (!connections.contains(address)) {
        API::sendEvent(std::format(R"({{ "eventType": "error", "errorType": "deviceNotYetDiscovered", "address": "{0}" }})",
                                   address.toStdString()));
        return;
    }
    auto connection = connections[address];
    connection->imageUpload(image, fileName, upgrade, commonParameters);
}
