//
// Created by loum-technologies on 4/18/2024.
//

#include "IoThread.h"
//#include "IoThread.moc"
#include <print>
#include <iostream>

IoThread::IoThread(Discoverer *discoverer)
{
    this->discoverer = discoverer;
}

IoThread::~IoThread()
{
}

void IoThread::process()
{
    while(true) {
        auto input_line = new std::string();
        if (!getline(std::cin, *input_line)) {
            break;
        }

        QTimer::singleShot(0, QCoreApplication::instance(), [this, input_line]()
        {
            discoverer->process(*input_line);
            delete input_line;
        });
    }

    emit finished();
}
