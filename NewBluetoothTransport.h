//
// Created by loum-technologies on 6/20/2024.
//

#ifndef QTMCUMGR_NEWBLUETOOTHTRANSPORT_H
#define QTMCUMGR_NEWBLUETOOTHTRANSPORT_H

#include <QObject>
#include <QTimer>
#include "smp_transport.h"
#include "BluetoothConnection.h"

class NewBluetoothTransport : public smp_transport {
Q_OBJECT

public:
    NewBluetoothTransport();
    ~NewBluetoothTransport();
    void silenceDisconnectionMessages();

    int connect(void);
    int disconnect(bool force);
    int is_connected();
    int send(smp_message *message);
    void form_connect_to_device(const QBluetoothDeviceInfo &info);
    QString address();

private slots:

    void characteristicChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
    void characteristicWritten(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
    void errorOccurred(QLowEnergyService::ServiceError newError);

private:
    BluetoothConnection *connection;
    uint16_t mtu;
    uint16_t mtu_max_worked;
    QByteArray sendbuffer;
    smp_message received_data;

    QTimer retry_timer;
    QTimer discover_timer;
    int retry_count;
    QBluetoothDeviceInfo *mInfo;
};


#endif //QTMCUMGR_NEWBLUETOOTHTRANSPORT_H
