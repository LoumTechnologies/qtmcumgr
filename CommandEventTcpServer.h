//
// Created by loum-technologies on 6/19/2024.
//

#ifndef SIMPLETCPSERVER_COMMANDEVENTTCPSERVER_H
#define SIMPLETCPSERVER_COMMANDEVENTTCPSERVER_H

#include <QTcpSocket>
#include <QTcpServer>

class CommandEventTcpServer : public QTcpServer
{
Q_OBJECT

public:
    explicit CommandEventTcpServer(QObject *parent = nullptr);
    bool start();

    Q_SIGNALS:
            void receiveMessageFromClient(const QString &message);
protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
            void handleReadyRead();
    void removeClient();

public slots:
            void sendMessageToClient(const QString& message);

private:
    QMap<qintptr, QTcpSocket*> m_clients;
};


#endif //SIMPLETCPSERVER_COMMANDEVENTTCPSERVER_H
