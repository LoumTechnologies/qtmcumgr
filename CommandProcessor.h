//
// Created by loum-technologies on 6/19/2024.
//

#ifndef SIMPLETCPSERVER_COMMANDPROCESSOR_H
#define SIMPLETCPSERVER_COMMANDPROCESSOR_H

#include <QObject>
#include "BluetoothDeviceManager.h"
#include "Connection.h"

class CommandProcessor : public QObject {
Q_OBJECT

public:
    CommandProcessor(BluetoothDeviceManager *deviceManager);
    ~CommandProcessor();

public slots:
    void processCommand(const QString& command);

private:
    BluetoothDeviceManager *deviceManager;
    QMap<QString, Connection*> connections;
};


#endif //SIMPLETCPSERVER_COMMANDPROCESSOR_H
