//
// Created by loum-technologies on 4/18/2024.
//

#include "IoThreadManager.h"
//#include "IoThreadManager.moc"

IoThreadManager::IoThreadManager(Discoverer *discoverer) {
    this->discoverer = discoverer;
}

void IoThreadManager::start()
{
    thread = new QThread();
    worker = new IoThread(discoverer);
    worker->moveToThread(thread);
    //connect( worker, &Worker::error, this, &MyClass::errorString);
    connect( thread, &QThread::started, worker, &IoThread::process);
    connect( worker, &IoThread::finished, thread, &QThread::quit);
    connect( worker, &IoThread::finished, worker, &IoThread::deleteLater);
    connect( thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();
}

IoThreadManager::~IoThreadManager() {
    if (thread != nullptr) {
        delete thread;
    }
    if (worker != nullptr) {
        delete worker;
    }
}
