#include <QCoreApplication>
#include "Discoverer.h"
#include "IoThreadManager.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Discoverer discoverer;
    discoverer.start();
    IoThreadManager instance(&discoverer);
    instance.start();
    return QCoreApplication::exec();
}
