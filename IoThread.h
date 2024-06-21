//
// Created by loum-technologies on 4/18/2024.
//

#ifndef QTMCUMGR_IOTHREAD_H
#define QTMCUMGR_IOTHREAD_H


#include <QtCore>
#include "CommandProcessor.h"

class IoThread : public QObject {
    Q_OBJECT

public:
    IoThread(CommandProcessor *discoverer);
    ~IoThread();

    void process();

signals:
    void finished();
    void error(QString error);

private:
    CommandProcessor *discoverer;
};


#endif //QTMCUMGR_IOTHREAD_H
