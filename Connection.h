//
// Created by loumtechnologies on 4/23/2024.
//

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QLowEnergyController>
#include "smp_group_array.h"
#include "smp_processor.h"
#include "CommonParameters.h"

class Connection : QObject {
    Q_OBJECT

public:
    Connection(QBluetoothDeviceInfo *info, QObject *parent = nullptr);
    ~Connection();

    void reset(bool force);
    void bootLoaderInfo(QString &query);

    smp_group_array *smp_groups;

    void getImages(CommonParameters &parameters);

private slots:
    void status(uint8_t user_data, group_status status, QString error_string);
    void progress(uint8_t user_data, uint8_t percent);

private:
    smp_transport *transport;
    smp_processor *processor;
    bool isConnected = false;
    bool isDeleting = false;

    QList<image_state_t> images_list;
    QList<hash_checksum_t> supported_hash_checksum_list;
    QVariant bootloader_info_response;
    QByteArray settings_read_response;
    QByteArray fs_hash_checksum_response;
    uint32_t fs_size_response;
    bool uart_transport_locked;
    QDateTime rtc_time_date_response;
    QList<image_state_t> images;
};



#endif //CONNECTION_H
