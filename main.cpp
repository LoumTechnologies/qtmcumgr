#include <QCoreApplication>
#include <QtBluetooth/QBluetoothLocalDevice>
#include "CommandEventTcpServer.h"
#include "BluetoothDeviceManager.h"
#include "CommandProcessor.h"
#include "IoThreadManager.h"
#include <iostream>

CommandEventTcpServer *tcpServer;

namespace API {
    void sendEvent(std::string str) {
        std::cout << str << std::endl;
        std::flush(std::cout);
        std::cerr << str << std::endl;
        std::flush(std::cerr);
        auto qstring = QString::fromStdString(str);
        qstring.append('\n');
        tcpServer->sendMessageToClient(qstring);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Initialize Bluetooth
    QBluetoothLocalDevice device;
    if (!device.isValid()) {
        qDebug() << "Invalid local Bluetooth adapter";
        return -1;
    }

    BluetoothDeviceManager deviceManager;
    CommandEventTcpServer theTcpServer;
    CommandProcessor processor(&deviceManager);
    IoThreadManager instance(&processor);
    tcpServer = &theTcpServer;
    QObject::connect(&theTcpServer, &CommandEventTcpServer::receiveMessageFromClient, &processor, &CommandProcessor::processCommand, Qt::ConnectionType::QueuedConnection);
    if (!theTcpServer.start()) {
        return 1;
    }
    QTimer::singleShot(0, [&instance, &deviceManager]() {
        deviceManager.start();
        instance.start();
    });

    // Wait for the process to finish
    int result = app.exec();
    return result;
}

#include "main.moc"