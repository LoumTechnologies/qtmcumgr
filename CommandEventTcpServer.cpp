//
// Created by loum-technologies on 6/17/2024.
//

#include <QTcpSocket>
#include "CommandEventTcpServer.h"
#include "API.h"
#include "Discoverer.h"
#include <cstdio>
#include <iostream>

CommandEventTcpServer::CommandEventTcpServer(Discoverer *discoverer, QObject *parent)
        : QTcpServer(parent)
{
    this->discoverer = discoverer;
}

void CommandEventTcpServer::incomingConnection(qintptr socketDescriptor) {
    API::sendEvent(std::format(R"({{ "eventType": "incomingConnection", "socketDescriptor": "{0}" }})",
                               socketDescriptor));

    m_clients[socketDescriptor] = new QTcpSocket(this);
    connect(m_clients[socketDescriptor], &QTcpSocket::readyRead, this, &CommandEventTcpServer::handleReadyRead);
    connect(m_clients[socketDescriptor], &QTcpSocket::disconnected, this, &CommandEventTcpServer::removeClient);
    m_clients[socketDescriptor]->setSocketDescriptor(socketDescriptor);
}

void CommandEventTcpServer::handleReadyRead() {
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray data = socket->readAll();
    auto command = QString::fromLatin1(data).toStdString();
    std::cerr << command << std::endl;
    std::flush(std::cerr);
    this->discoverer->process(command);
}

void CommandEventTcpServer::removeClient() {
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    API::sendEvent(std::format(R"({{ "eventType": "endingIncomingConnection", "socketDescriptor": "{0}" }})",
                               socket->socketDescriptor()));
    m_clients.remove(socket->socketDescriptor());
}

void CommandEventTcpServer::sendMessageToClient(const QString& message) {
    QByteArray data = message.toUtf8();
    for (const auto &item: m_clients.values()) {
        item->write(data);
        item->flush();
    }
}