#include <QCoreApplication>
#include <QHostAddress>
#include "Discoverer.h"
#include "IoThreadManager.h"
#include "CommandEventTcpServer.h"
#include "API.h"

#include <print>
#include <iostream>

CommandEventTcpServer *tcpServer;

namespace API {
    void sendEvent(std::string str) {
        std::print("{0}\n", str);
        std::flush(std::cout);
        std::cerr << str << std::endl;
        std::flush(std::cerr);
        auto qstring = QString::fromStdString(str);
        qstring.append('\n');
        tcpServer->sendMessageToClient(qstring);
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    auto discoverer = new Discoverer();
    auto instance = new IoThreadManager(discoverer);
    QTimer::singleShot(0, [&]() {
        discoverer->start();
        instance->start();
    });

    CommandEventTcpServer server(discoverer);
    tcpServer = &server;
    if (!server.listen(QHostAddress::Any, 6983)) {
        QTextStream cerr(stderr);
        API::sendEvent(std::format(R"({{ "eventType": "error", "errorType": "Failed to listen on TCP port", "port": {0} }})",
                                   "6983"));
        return -1;
    }

    API::sendEvent(std::format(R"({{ "eventType": "listeningOnPort", "port": {0} }})",
                               "6983"));

    auto exitCode = QCoreApplication::exec();
    delete instance;
    delete discoverer;
    return exitCode;
}
