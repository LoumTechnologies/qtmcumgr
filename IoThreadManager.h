//
// Created by loum-technologies on 4/18/2024.
//

#ifndef QTMCUMGR_IOTHREADMANAGER_H
#define QTMCUMGR_IOTHREADMANAGER_H


#include <QThread>
#include "IoThread.h"

class IoThreadManager : QObject {
    Q_OBJECT

public:
    IoThreadManager(CommandProcessor *discoverer);
    ~IoThreadManager();

public:

    void start();

private:
    CommandProcessor *discoverer = nullptr;
    QThread *thread = nullptr;
    IoThread *worker = nullptr;
};


#endif //QTMCUMGR_IOTHREADMANAGER_H
