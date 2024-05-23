//
// Created by loum-technologies on 4/18/2024.
//

#ifndef QTMCUMGR_DISCOVERER_H
#define QTMCUMGR_DISCOVERER_H

#include <QBluetoothDeviceDiscoveryAgent>

#include "smp_group_array.h"
#include "Connection.h"
#include "Connect.h"
#include "Disconnect.h"
#include "GetImages.h"
#include "Reset.h"
#include "SetImage.h"
#include "UploadImage.h"

class Discoverer : QObject {
    Q_OBJECT

public:
    explicit Discoverer();
    ~Discoverer();
    void process(const std::string &command);

public slots:
    void start();
    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void finished();

private:
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QMap<QString, Connection*> *connections;
    QMap<QString, QBluetoothDeviceInfo> *devices;

    void handleConnect(Connect &connect);
    void handleDisconnect(Disconnect &disconnect);
    void handleGetImages(Connection &connection, GetImages &getImages);
    void handleReset(Connection &connection, Reset &reset);
    void handleSetImage(Connection &connection, SetImage &image);
    void handleUploadImage(Connection &connection, UploadImage &image);
};


#endif //QTMCUMGR_DISCOVERER_H
