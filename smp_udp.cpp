/******************************************************************************
** Copyright (C) 2021-2023 Jamie M.
**
** Project: AuTerm
**
** Module:  smp_udp.cpp
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
#include "smp_udp.h"
#include <QNetworkDatagram>

smp_udp::smp_udp(QObject *parent)
{
    Q_UNUSED(parent);

    socket = new QUdpSocket(this);
    socket_is_connected = false;

    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(socket_readyread()));
//    QObject::connect(socket, SIGNAL(connected()), this, SLOT(socket_connected()));
//    QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(socket_disconnected()));
//    QObject::connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socket_statechanged(QAbstractSocket::SocketState)));
//    QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socket_error(QAbstractSocket::SocketError)));
//    QObject::connect(socket, SIGNAL(readChannelFinished()), this, SLOT(socket_readchannelfinished()));

//    QObject::connect(udp_window, SIGNAL(connect_to_device(QString,uint16_t)), this, SLOT(connect_to_device(QString,uint16_t)));
//    QObject::connect(udp_window, SIGNAL(plugin_save_setting(QString,QVariant)), main_window, SLOT(plugin_save_setting(QString,QVariant)));
//    QObject::connect(udp_window, SIGNAL(plugin_load_setting(QString,QVariant*,bool*)), main_window, SLOT(plugin_load_setting(QString,QVariant*,bool*)));
}

smp_udp::~smp_udp()
{
    QObject::disconnect(this, SLOT(socket_readyread()));
//    QObject::disconnect(this, SLOT(socket_connected()));
//    QObject::disconnect(this, SLOT(socket_disconnected()));
//    QObject::disconnect(this, SLOT(socket_statechanged(QAbstractSocket::SocketState)));
//    QObject::disconnect(this, SLOT(socket_error(QAbstractSocket::SocketError)));
//    QObject::disconnect(this, SLOT(socket_readchannelfinished()));

    QObject::disconnect(this, SLOT(connect_to_device(QString,uint16_t)));
//    QObject::disconnect(udp_window, SIGNAL(plugin_save_setting(QString,QVariant)), main_window, SLOT(plugin_save_setting(QString,QVariant)));
//    QObject::disconnect(udp_window, SIGNAL(plugin_load_setting(QString,QVariant*,bool*)), main_window, SLOT(plugin_load_setting(QString,QVariant*,bool*)));

    if (socket_is_connected == true)
    {
        socket->disconnectFromHost();
        socket_is_connected = false;
    }

//    if (udp_window->isVisible())
//    {
//        udp_window->close();
//    }
//
//    delete udp_window;
    delete socket;
}

QString smp_udp::address() {
    return socket->peerAddress().toString();
}


int smp_udp::connect(void)
{
    if (socket_is_connected == true)
    {
        return SMP_TRANSPORT_ERROR_ALREADY_CONNECTED;
    }

//    udp_window->show();

    return SMP_TRANSPORT_ERROR_OK;
}

int smp_udp::disconnect(bool force)
{
    if (socket_is_connected == false)
    {
        return SMP_TRANSPORT_ERROR_NOT_CONNECTED;
    }

    socket->disconnectFromHost();
    socket_is_connected = false;
//    socket_received_data.clear();
    received_data.clear();

    return SMP_TRANSPORT_ERROR_OK;
}

int smp_udp::is_connected()
{
    if (socket_is_connected == true)
    {
        return 1;
    }

    return 0;
}

int smp_udp::send(smp_message *message)
{
    if (socket_is_connected == false)
    {
        return SMP_TRANSPORT_ERROR_NOT_CONNECTED;
    }

    socket->write(*message->data());

    return SMP_TRANSPORT_ERROR_OK;
}

#if 0
int smp_udp::receive(QByteArray *data, uint16_t max_size)
{
    if (socket_is_connected == false)
    {
        return SMP_TRANSPORT_ERROR_NOT_CONNECTED;
    }

    if (socket_received_data.length() == 0)
    {
        return SMP_TRANSPORT_ERROR_NO_DATA;
    }

    if (max_size == 0 || max_size >= socket_received_data.length())
    {
        *data = socket_received_data;
        socket_received_data.clear();
    }
    else
    {
        *data = socket_received_data.left(max_size);
        socket_received_data.remove(0, max_size);

        return SMP_TRANSPORT_ERROR_OK;
    }

    //Check if there are more packets waiting, after the event loop regains control
    QMetaObject::invokeMethod(this, "socket_readyread", Qt::QueuedConnection);

    return SMP_TRANSPORT_ERROR_OK;
}

int smp_udp::receive_data_size()
{
    if (socket_is_connected == false)
    {
        return SMP_TRANSPORT_ERROR_NOT_CONNECTED;
    }

    return socket_received_data.length();
}

int smp_udp::get_mtu()
{
    return setting_mtu;
}

QString smp_udp::get_error_string(int error_code)
{
#if 0
    if (error_code == 1)
    {
        return "yeah";
    }
#endif

    return smp_transport::get_error_string(error_code);
}
#endif

void smp_udp::socket_readyread()
{
//    qDebug() << "called";
#if 0
    if (socket->hasPendingDatagrams() && socket_received_data.isEmpty())
    {
        QNetworkDatagram datagram = socket->receiveDatagram();
        socket_received_data = datagram.data();
        emit receive_waiting();
    }
#endif
    while (socket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = socket->receiveDatagram();
        received_data.append(datagram.data());
        //socket_received_data.append(datagram.data());
    }

    //Check if there is a full packet
    if (received_data.is_valid() == true)
    {
        emit receive_waiting(&received_data);
        received_data.clear();
    }
}

#if 0
void smp_udp::socket_connected()
{
	emit connected();
}

void smp_udp::socket_disconnected()
{
	emit disconnected();
}

void smp_udp::socket_statechanged(QAbstractSocket::SocketState state)
{

}

void smp_udp::socket_error(QAbstractSocket::SocketError error)
{

}

void smp_udp::socket_readchannelfinished()
{

}
#endif

#if 0
int smp_udp::send_bytes_waiting(void)
{
	if (socket_is_connected == false)
	{
        return SMP_TRANSPORT_ERROR_NOT_CONNECTED;
	}

	return socket->bytesToWrite();
}

int smp_udp::has_data(void)
{
	if (socket_is_connected == false)
	{
        return SMP_TRANSPORT_ERROR_NOT_CONNECTED;
	}

	return socket->hasPendingDatagrams();
}
#endif

void smp_udp::connect_to_device(QString host, uint16_t port)
{
    socket->connectToHost(host, port);
    socket_is_connected = true;
    //TODO: need to alert parent
}

void smp_udp::close_connect_dialog()
{
//    if (udp_window->isVisible())
//    {
//        udp_window->close();
//    }
}

void smp_udp::setup_finished()
{
//    udp_window->load_settings();
}
