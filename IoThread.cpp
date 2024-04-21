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
        std::string input_line;
        if (!getline(std::cin, input_line)) {
            break;
        }

        discoverer->process(input_line);
    }

    emit finished();
}
