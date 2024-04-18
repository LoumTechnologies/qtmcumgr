//
// Created by loum-technologies on 4/18/2024.
//

#include "IoThread.h"
//#include "IoThread.moc"
#include <print>
#include <iostream>

IoThread::IoThread()
{
}

IoThread::~IoThread()
{
}


void IoThread::process()
{
    while(true) {
        std::print("Please enter a command: ");
        std::string input_line;
        if (!getline(std::cin, input_line)) {
            break;
        }

        std::print("You entered: {0}\n", input_line);
    }

    emit finished();
}
