#include <QCoreApplication>
#include "Discoverer.h"
#include "IoThreadManager.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    auto discoverer = new Discoverer();
    auto instance = new IoThreadManager(discoverer);
    QTimer::singleShot(0, [&]() {
        discoverer->start();
        instance->start();
    });
    auto exitCode = QCoreApplication::exec();
    delete instance;
    delete discoverer;
    return exitCode;
}
