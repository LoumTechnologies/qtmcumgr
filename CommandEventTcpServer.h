//
// Created by loum-technologies on 6/17/2024.
//

#ifndef QTMCUMGR_COMMANDEVENTTCPSERVER_H
#define QTMCUMGR_COMMANDEVENTTCPSERVER_H


#include <QObject>
#include <QTcpServer>
#include <QMap>
#include <QDebug>
#include "Discoverer.h"

class CommandEventTcpServer : public QTcpServer
{
Q_OBJECT

public:
    explicit CommandEventTcpServer(Discoverer *discoverer, QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void handleReadyRead();
    void removeClient();

public slots:
    void sendMessageToClient(const QString& message);

private:
    QMap<qintptr, QTcpSocket*> m_clients;
    Discoverer *discoverer;
};

#endif //QTMCUMGR_COMMANDEVENTTCPSERVER_H
