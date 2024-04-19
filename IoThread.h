//
// Created by loum-technologies on 4/18/2024.
//

#ifndef QTMCUMGR_IOTHREAD_H
#define QTMCUMGR_IOTHREAD_H


#include <QtCore>
#include "Discoverer.h"

class IoThread : public QObject {
    Q_OBJECT

public:
    IoThread(Discoverer *discoverer);
    ~IoThread();

    void process();

signals:
    void finished();
    void error(QString error);

private:
    Discoverer *discoverer;
};


#endif //QTMCUMGR_IOTHREAD_H
