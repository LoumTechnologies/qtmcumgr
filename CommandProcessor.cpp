//
// Created by loum-technologies on 6/19/2024.
//

#include <QJsonDocument>
#include <QJsonObject>
#include "CommandProcessor.h"
#include "API.h"

CommandProcessor::CommandProcessor(BluetoothDeviceManager *deviceManager) {
    this->deviceManager = deviceManager;
}

CommandProcessor::~CommandProcessor() {
    for (const auto &item: this->connections) {
        delete item;
    }
}

void CommandProcessor::processCommand(const QString &command) {
    auto json = QJsonDocument::fromJson(command.toUtf8());
    if (!json.isObject()) {
        return;
    }

    auto commandObject = json.object();
    auto commandType = commandObject.value("commandType").toString();
    auto address = commandObject.value("address").toString();

    if (commandType == "connect") {
        deviceManager->connect(address);
        return;
    }

    if (commandType == "disconnect") {
        deviceManager->disconnect(address);
        return;
    }

    if (commandType == "getImages") {
        CommonParameters commonParameters;
        deviceManager->getImages(address, commonParameters);
    }

    if (commandType == "reset") {
        CommonParameters commonParameters;
        auto force = commandObject.value("force").toBool();
        deviceManager->reset(address, force);
    }

    if (commandType == "uploadImage") {
        CommonParameters commonParameters;
        auto image = commandObject.value("image").toInt();
        auto fileName = commandObject.value("fileName").toString();
        auto upgrade = commandObject.value("upgrade").toBool();
        deviceManager->uploadImage(address, image, fileName, upgrade, commonParameters);
    }

    if (commandType == "setImage") {
        CommonParameters commonParameters;
        auto hashString = commandObject.value("hashString").toString();
        auto confirm = commandObject.value("confirm").toBool();
        deviceManager->setImage(address, hashString, confirm, commonParameters);
    }

    if (commandType == "rediscoverCharacteristics") {
        CommonParameters commonParameters;
        deviceManager->rediscoverCharacteristics(address);
    }
}
