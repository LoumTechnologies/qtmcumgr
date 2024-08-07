//
// Created by loum-technologies on 4/18/2024.
//

#include "IoThread.h"
//#include "IoThread.moc"
#include <print>
#include <iostream>

IoThread::IoThread(CommandProcessor *discoverer)
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
            QString str(input_line->c_str());
            if (str.trimmed().isEmpty()) {
                delete input_line;
                return;
            }
            std::cerr << input_line << std::endl;
            std::flush(std::cerr);
            discoverer->processCommand(str);
        });
    }

    emit finished();
}
