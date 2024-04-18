#include <QCoreApplication>
#include "Discoverer.h"
#include "IoThreadManager.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    IoThreadManager instance;
    instance.start();
    Discoverer discoverer;
    discoverer.start();
    return QCoreApplication::exec();
}
