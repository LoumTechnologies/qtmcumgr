//
// Created by loum-technologies on 4/18/2024.
//

#ifndef QTMCUMGR_IOTHREAD_H
#define QTMCUMGR_IOTHREAD_H


#include <QtCore>

class IoThread : public QObject {
    Q_OBJECT

public:
    IoThread();
    ~IoThread();

    void process();

signals:
    void finished();
    void error(QString error);

};


#endif //QTMCUMGR_IOTHREAD_H
