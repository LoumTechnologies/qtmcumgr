/******************************************************************************
** Copyright (C) 2021-2023 Jamie M.
**
** Project: AuTerm
**
** Module:  smp_uart.h
**
** Notes:
**
** License: This program is free software: you can redistribute it and/or
**          modify it under the terms of the GNU General Public License as
**          published by the Free Software Foundation, version 3.
**
**          This program is distributed in the hope that it will be useful,
**          but WITHOUT ANY WARRANTY; without even the implied warranty of
**          MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**          GNU General Public License for more details.
**
**          You should have received a copy of the GNU General Public License
**          along with this program.  If not, see http://www.gnu.org/licenses/
**
*******************************************************************************/
#ifndef SMP_UART_H
#define SMP_UART_H

#include <QObject>
#include "smp_transport.h"
#include "smp_message.h"

class smp_uart : public smp_transport
{
    Q_OBJECT

public:
    smp_uart(QObject *parent = nullptr);
    ~smp_uart();
    int send(smp_message *message);
    uint16_t max_message_data_size(uint16_t mtu);

private:
    void data_received(QByteArray *message);

signals:
    void serial_write(QByteArray *data);

public slots:
    void serial_read(QByteArray *rec_data);

private:
    QByteArray SerialData;
    QByteArray SMPBuffer;
    QByteArray SMPBufferActualData;
    bool SMPWaitingForContinuation = false;
    const QByteArray smp_first_header = QByteArrayLiteral("\x06\x09");
    const QByteArray smp_continuation_header = QByteArrayLiteral("\x04\x14");
    uint16_t waiting_packet_length = 0;
};

#endif // SMP_UART_H
