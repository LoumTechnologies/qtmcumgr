//
// Created by loum-technologies on 6/20/2024.
//

#include "BluetoothConnection.h"
#include "API.h"

BluetoothConnection::BluetoothConnection(const QBluetoothDeviceInfo &info, QObject *parent) : QObject(parent) {
    mInfo = info;
    controller = QLowEnergyController::createCentral(info);
    mcumgr_service = nullptr;

    QObject::connect(controller, &QLowEnergyController::connected, this, &BluetoothConnection::deviceConnected);
    QObject::connect(controller, &QLowEnergyController::connectionUpdated, this,
                     &BluetoothConnection::deviceConnectionUpdated);
    QObject::connect(controller, &QLowEnergyController::disconnected, this, &BluetoothConnection::deviceDisconnected);
    QObject::connect(controller, &QLowEnergyController::discoveryFinished, this,
                     &BluetoothConnection::deviceDiscoveryFinished);
    QObject::connect(controller, &QLowEnergyController::errorOccurred, this, &BluetoothConnection::deviceErrorOccurred);
    QObject::connect(controller, &QLowEnergyController::mtuChanged, this, &BluetoothConnection::deviceMtuChanged);
    QObject::connect(controller, &QLowEnergyController::rssiRead, this, &BluetoothConnection::deviceRssiRead);
    QObject::connect(controller, &QLowEnergyController::serviceDiscovered, this,
                     &BluetoothConnection::deviceServiceDiscovered);
    QObject::connect(controller, &QLowEnergyController::stateChanged, this, &BluetoothConnection::deviceStateChanged);

    controller->connectToDevice();
    _silenceDisconnectionMessages=false;
}

BluetoothConnection::~BluetoothConnection() {
    if (!_silenceDisconnectionMessages) {
        API::sendEvent(std::format(
                R"({{ "eventType": "disconnected", "address": "{0}" }})",
                mInfo.address().toString().toStdString()
        ));
    }
    controller->disconnectFromDevice();

    if (mcumgr_service != nullptr) {
        QObject::disconnect(mcumgr_service, &QLowEnergyService::characteristicChanged, this, &BluetoothConnection::serviceCharacteristicChanged);
        QObject::disconnect(mcumgr_service, &QLowEnergyService::characteristicRead, this, &BluetoothConnection::serviceCharacteristicRead);
        QObject::disconnect(mcumgr_service, &QLowEnergyService::characteristicWritten, this, &BluetoothConnection::serviceCharacteristicWritten);
        QObject::disconnect(mcumgr_service, &QLowEnergyService::descriptorRead, this, &BluetoothConnection::serviceDescriptorRead);
        QObject::disconnect(mcumgr_service, &QLowEnergyService::descriptorWritten, this, &BluetoothConnection::serviceDescriptorWritten);
        QObject::disconnect(mcumgr_service, &QLowEnergyService::errorOccurred, this, &BluetoothConnection::serviceErrorOccurred);
        QObject::disconnect(mcumgr_service, &QLowEnergyService::stateChanged, this, &BluetoothConnection::serviceStateChanged);

        delete mcumgr_service;
        mcumgr_service = nullptr;
    }

    delete controller;
}

QLowEnergyController *BluetoothConnection::getController() {
    return controller;
}

QLowEnergyService *BluetoothConnection::getMcumgrService() {
    return mcumgr_service;
}

QLowEnergyCharacteristic BluetoothConnection::getTransmitCharacteristic() {
    return transmit_characteristic;
}

bool BluetoothConnection::isConnected() {
    auto state = controller->state();
    if (state == QLowEnergyController::ControllerState::ConnectedState
    || state == QLowEnergyController::ControllerState::DiscoveringState
    || state == QLowEnergyController::ControllerState::DiscoveredState) {
        return true;
    }

    return false;
}




void BluetoothConnection::deviceConnected()
{
    API::sendEvent(std::format(
            R"({{ "eventType": "connected", "address": "{0}" }})",
            mInfo.address().toString().toStdString()
    ));

    controller->discoverServices();
}

void BluetoothConnection::deviceConnectionUpdated(const QLowEnergyConnectionParameters &newParameters)
{
    API::sendEvent(std::format(
            R"({{ "eventType": "connectionUpdated", "address": "{0}", "latency": {1}, "maximumInterval": {2}, "minimumInterval": {3}, "supervisionTimeout": {4} }})",
            mInfo.address().toString().toStdString(),
            newParameters.latency(),
            newParameters.maximumInterval(),
            newParameters.minimumInterval(),
            newParameters.supervisionTimeout()
    ));
}

void BluetoothConnection::deviceDisconnected() {
    if (!_silenceDisconnectionMessages) {
        API::sendEvent(std::format(
                R"({{ "eventType": "gracefullyDisconnected", "address": "{0}" }})",
                mInfo.address().toString().toStdString()
        ));
    }
}

void BluetoothConnection::deviceDiscoveryFinished()
{
    API::sendEvent(std::format(
            R"({{ "eventType": "deviceDiscoveryFinished", "address": "{0}" }})",
            mInfo.address().toString().toStdString()
    ));

    if (mcumgr_service != nullptr)
    {
        QObject::connect(mcumgr_service, &QLowEnergyService::characteristicChanged, this, &BluetoothConnection::serviceCharacteristicChanged);
        QObject::connect(mcumgr_service, &QLowEnergyService::characteristicRead, this, &BluetoothConnection::serviceCharacteristicRead);
        QObject::connect(mcumgr_service, &QLowEnergyService::characteristicWritten, this, &BluetoothConnection::serviceCharacteristicWritten);
        QObject::connect(mcumgr_service, &QLowEnergyService::descriptorRead, this, &BluetoothConnection::serviceDescriptorRead);
        QObject::connect(mcumgr_service, &QLowEnergyService::descriptorWritten, this, &BluetoothConnection::serviceDescriptorWritten);
        QObject::connect(mcumgr_service, &QLowEnergyService::errorOccurred, this, &BluetoothConnection::serviceErrorOccurred);
        QObject::connect(mcumgr_service, &QLowEnergyService::stateChanged, this, &BluetoothConnection::serviceStateChanged);
    }
}

void BluetoothConnection::deviceErrorOccurred(QLowEnergyController::Error newError)
{
    QString errorString;

    switch(newError) {
        case QLowEnergyController::Error::NoError:
            errorString = "NoError";
            break;
        case QLowEnergyController::Error::UnknownError:
            errorString = "UnknownError";
            break;
        case QLowEnergyController::Error::UnknownRemoteDeviceError:
            errorString = "UnknownRemoteDeviceError";
            break;
        case QLowEnergyController::Error::NetworkError:
            errorString = "NetworkError";
            break;
        case QLowEnergyController::Error::InvalidBluetoothAdapterError:
            errorString = "InvalidBluetoothAdapterError";
            break;
        case QLowEnergyController::Error::ConnectionError:
            errorString = "ConnectionError";
            break;
        case QLowEnergyController::Error::AdvertisingError:
            errorString = "AdvertisingError";
            break;
        case QLowEnergyController::Error::RemoteHostClosedError:
            errorString = "RemoteHostClosedError";
            break;
        case QLowEnergyController::Error::AuthorizationError:
            errorString = "AuthorizationError";
            break;
        case QLowEnergyController::Error::MissingPermissionsError:
            errorString = "MissingPermissionsError";
            break;
        case QLowEnergyController::Error::RssiReadError:
            errorString = "RssiReadError";
            break;
    }

    API::sendEvent(std::format(
            R"({{ "eventType": "error", "address": "{0}", "description": "{1}" }})",
            mInfo.address().toString().toStdString(),
            errorString.toStdString()
    ));
}

void BluetoothConnection::deviceMtuChanged(int mtu)
{
    API::sendEvent(std::format(
            R"({{ "eventType": "deviceMtuChanged", "address": "{0}", "mtu": {1} }})",
            mInfo.address().toString().toStdString(),
            mtu
    ));
}

void BluetoothConnection::deviceRssiRead(qint16 rssi)
{
    API::sendEvent(std::format(
            R"({{ "eventType": "readRssi", "address": "{0}", "rssi": {1} }})",
            mInfo.address().toString().toStdString(),
            rssi
    ));
}

void BluetoothConnection::deviceServiceDiscovered(const QBluetoothUuid &newService)
{
    API::sendEvent(std::format(
            R"({{ "eventType": "deviceServiceDiscovered", "address": "{0}", "service": "{1}" }})",
            mInfo.address().toString().toStdString(),
            newService.toString(QUuid::WithoutBraces).toStdString()
    ));

    if (newService == QBluetoothUuid(QString("8D53DC1D-1DB7-4CD3-868B-8A527460AA84"))) {
        mcumgr_service = controller->createServiceObject(newService, this);

        mcumgr_service->discoverDetails();
        API::sendEvent(std::format(R"({{ "eventType": "serviceDiscoverDetails", "address": "{0}", "service": "{1}" }})",
                                   mInfo.address().toString().toStdString(),
                                   mcumgr_service->serviceUuid().toString(QUuid::WithoutBraces).toStdString()
        ));
    }
}

void BluetoothConnection::deviceStateChanged(QLowEnergyController::ControllerState state)
{
    QString stateString;

    switch(state) {
        case QLowEnergyController::ControllerState::UnconnectedState:
            stateString = "UnconnectedState";
            break;
        case QLowEnergyController::ControllerState::ConnectingState:
            stateString = "ConnectingState";
            break;
        case QLowEnergyController::ControllerState::ConnectedState:
            stateString = "ConnectedState";
            break;
        case QLowEnergyController::ControllerState::DiscoveringState:
            stateString = "DiscoveringState";
            break;
        case QLowEnergyController::ControllerState::DiscoveredState:
            stateString = "DiscoveredState";
            break;
        case QLowEnergyController::ControllerState::ClosingState:
            stateString = "ClosingState";
            break;
        case QLowEnergyController::ControllerState::AdvertisingState:
            stateString = "AdvertisingState";
            break;
    }

    API::sendEvent(std::format(
            R"({{ "eventType": "deviceStateChanged", "address": "{0}", "state": "{1}" }})",
            mInfo.address().toString().toStdString(),
            stateString.toStdString()
    ));
}






void BluetoothConnection::serviceCharacteristicChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue)
{
//    API::sendEvent(std::format(R"({{ "eventType": "serviceCharacteristicChanged", "address": "{0}", "service": "{1}", "characteristic": "{2}", "name": "{3}", "value": "{4}", "newValue": "{5}", "isValid": {6} }})",
//                               mInfo.address().toString().toStdString(),
//                               mcumgr_service->serviceUuid().toString(QUuid::WithoutBraces).toStdString(),
//                               characteristic.uuid().toString(QUuid::WithoutBraces).toStdString(),
//                               characteristic.name().toStdString(),
//                               QString::fromLatin1(characteristic.value().toHex()).toStdString(),
//                               QString::fromLatin1(newValue.toHex()).toStdString(),
//                               characteristic.isValid()
//    ));
    emit characteristicChanged(characteristic, newValue);
}
void BluetoothConnection::serviceCharacteristicRead(const QLowEnergyCharacteristic &characteristic, const QByteArray &value)
{
//    API::sendEvent(std::format(R"({{ "eventType": "serviceCharacteristicRead", "address": "{0}", "service": "{1}", "characteristic": "{2}", "name": "{3}", "mvalue": "{4}", "value": "{5}", "isValid": {6} }})",
//                               mInfo.address().toString().toStdString(),
//                               mcumgr_service->serviceUuid().toString(QUuid::WithoutBraces).toStdString(),
//                               characteristic.uuid().toString(QUuid::WithoutBraces).toStdString(),
//                               characteristic.name().toStdString(),
//                               QString::fromLatin1(characteristic.value().toHex()).toStdString(),
//                               QString::fromLatin1(value.toHex()).toStdString(),
//                               characteristic.isValid()
//    ));
}
void BluetoothConnection::serviceCharacteristicWritten(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue)
{
//    API::sendEvent(std::format(R"({{ "eventType": "serviceCharacteristicWritten", "address": "{0}", "service": "{1}", "characteristic": "{2}", "name": "{3}", "value": "{4}", "newValue": "{5}", "isValid": {6} }})",
//                               mInfo.address().toString().toStdString(),
//                               mcumgr_service->serviceUuid().toString(QUuid::WithoutBraces).toStdString(),
//                               characteristic.uuid().toString(QUuid::WithoutBraces).toStdString(),
//                               characteristic.name().toStdString(),
//                               QString::fromLatin1(characteristic.value().toHex()).toStdString(),
//                               QString::fromLatin1(newValue.toHex()).toStdString(),
//                               characteristic.isValid()
//    ));

    emit characteristicWritten(characteristic, newValue);
}
void BluetoothConnection::serviceDescriptorRead(const QLowEnergyDescriptor &descriptor, const QByteArray &value)
{
    API::sendEvent(std::format(R"({{ "eventType": "serviceDescriptorRead", "address": "{0}", "service": "{1}", "characteristic": "{2}", "name": "{3}", "ovalue": "{4}", "value": "{5}", "isValid": {6} }})",
                               mInfo.address().toString().toStdString(),
                               mcumgr_service->serviceUuid().toString(QUuid::WithoutBraces).toStdString(),
                               descriptor.uuid().toString(QUuid::WithoutBraces).toStdString(),
                               descriptor.name().toStdString(),
                               QString::fromLatin1(descriptor.value().toHex()).toStdString(),
                               QString::fromLatin1(value.toHex()).toStdString(),
                               descriptor.isValid()
    ));
}
void BluetoothConnection::serviceDescriptorWritten(const QLowEnergyDescriptor &descriptor, const QByteArray &newValue)
{
    API::sendEvent(std::format(R"({{ "eventType": "serviceDescriptorWritten", "address": "{0}", "service": "{1}", "characteristic": "{2}", "name": "{3}", "value": "{4}", "newValue": "{5}", "isValid": {6} }})",
                               mInfo.address().toString().toStdString(),
                               mcumgr_service->serviceUuid().toString(QUuid::WithoutBraces).toStdString(),
                               descriptor.uuid().toString(QUuid::WithoutBraces).toStdString(),
                               descriptor.name().toStdString(),
                               QString::fromLatin1(descriptor.value().toHex()).toStdString(),
                               QString::fromLatin1(newValue.toHex()).toStdString(),
                               descriptor.isValid()
    ));
}
void BluetoothConnection::serviceErrorOccurred(QLowEnergyService::ServiceError newError)
{
    QString newErrorString;

    switch(newError) {
        case QLowEnergyService::ServiceError::NoError:
            newErrorString = "NoError";
            break;
        case QLowEnergyService::ServiceError::OperationError:
            newErrorString = "OperationError";
            break;
        case QLowEnergyService::ServiceError::CharacteristicWriteError:
            newErrorString = "CharacteristicWriteError";
            break;
        case QLowEnergyService::ServiceError::DescriptorWriteError:
            newErrorString = "DescriptorWriteError";
            break;
        case QLowEnergyService::ServiceError::UnknownError:
            newErrorString = "UnknownError";
            break;
        case QLowEnergyService::ServiceError::CharacteristicReadError:
            newErrorString = "CharacteristicReadError";
            break;
        case QLowEnergyService::ServiceError::DescriptorReadError:
            newErrorString = "DescriptorReadError";
            break;
    }


    API::sendEvent(std::format(R"({{ "eventType": "serviceErrorOccurred", "address": "{0}", "service": "{1}", "error": "{2}" }})",
                               mInfo.address().toString().toStdString(),
                               mcumgr_service->serviceUuid().toString(QUuid::WithoutBraces).toStdString(),
                               newErrorString.toStdString()
    ));

    emit errorOccurred(newError);
}
void BluetoothConnection::serviceStateChanged(QLowEnergyService::ServiceState newState)
{
    QString newStateString;

    switch(newState) {
        case QLowEnergyService::ServiceState::InvalidService:
            newStateString = "InvalidService";
            break;
        case QLowEnergyService::ServiceState::RemoteService:
            newStateString = "RemoteService";
            break;
        case QLowEnergyService::ServiceState::RemoteServiceDiscovering:
            newStateString = "RemoteServiceDiscovering";
            break;
        case QLowEnergyService::ServiceState::RemoteServiceDiscovered:
            newStateString = "RemoteServiceDiscovered";
            break;
        case QLowEnergyService::ServiceState::LocalService:
            newStateString = "LocalService";
            break;
    }

    API::sendEvent(std::format(R"({{ "eventType": "serviceStateChanged", "address": "{0}", "service": "{1}", "state": "{2}" }})",
                               mInfo.address().toString().toStdString(),
                               mcumgr_service->serviceUuid().toString(QUuid::WithoutBraces).toStdString(),
                               newStateString.toStdString()
    ));

    if (newState == QLowEnergyService::ServiceState::RemoteServiceDiscovered) {
        if (mcumgr_service != nullptr) {

            for (const auto &item: mcumgr_service->characteristics()) {
                API::sendEvent(std::format(R"({{ "eventType": "characteristicDiscovered", "address": "{0}", "service": "{1}", "characteristic": "{2}", "characteristicName": "{3}", "isValid": {4} }})",
                                           mInfo.address().toString().toStdString(),
                                           mcumgr_service->serviceUuid().toString(QUuid::WithoutBraces).toStdString(),
                                           item.uuid().toString(QUuid::WithoutBraces).toStdString(),
                                           item.name().toStdString(),
                                           item.isValid()));
                if (item.uuid() == QBluetoothUuid(QString("DA2E7828-FBCE-4E01-AE9E-261174997C48"))) {
                    transmit_characteristic = item;

                    const QLowEnergyDescriptor descTXDesc = transmit_characteristic.descriptor(QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration);

                    if (!descTXDesc.isValid())
                    {
                        API::sendEvent(std::format(R"({{ "eventType": "error", "address": "{0}", "description": "Invalid TX" }})",
                                                   mInfo.address().toString().toStdString()));
                    }
                    else {
                        //Enable Tx descriptor notifications
                        mcumgr_service->writeDescriptor(descTXDesc, QByteArray::fromHex("0100"));
                    }
                }
            }
        }
    }
}

void BluetoothConnection::silenceDisconnectionMessages() {
    _silenceDisconnectionMessages = true;
}
