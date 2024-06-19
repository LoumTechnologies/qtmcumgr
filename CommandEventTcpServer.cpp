//
// Created by loum-technologies on 6/19/2024.
//

#include "CommandEventTcpServer.h"
#include "API.h"

CommandEventTcpServer::CommandEventTcpServer(QObject *parent)
        : QTcpServer(parent)
{
}

bool CommandEventTcpServer::start() {
    if (!this->listen(QHostAddress::Any, 6983)) {
        API::sendEvent(std::format(R"({{ "eventType": "error", "errorType": "Failed to listen on TCP port", "port": {0} }})",
                                   "6983"));
        return false;
    }

    return true;
}

void CommandEventTcpServer::incomingConnection(qintptr socketDescriptor) {

    m_clients[socketDescriptor] = new QTcpSocket(this);
    QObject::connect(m_clients[socketDescriptor], &QTcpSocket::readyRead, this, &CommandEventTcpServer::handleReadyRead);
    QObject::connect(m_clients[socketDescriptor], &QTcpSocket::disconnected, this, &CommandEventTcpServer::removeClient);
    m_clients[socketDescriptor]->setSocketDescriptor(socketDescriptor);
}

void CommandEventTcpServer::handleReadyRead() {
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray data = socket->readAll();
    auto command = QString::fromLatin1(data);
    receiveMessageFromClient(command);
}

void CommandEventTcpServer::removeClient() {
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    m_clients.remove(socket->socketDescriptor());
}

void CommandEventTcpServer::sendMessageToClient(const QString& message) {
    QByteArray data = message.toUtf8();
    for (const auto &item: m_clients.values()) {
        item->write(data);
        item->flush();
    }
}
