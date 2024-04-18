#include <QCoreApplication>
#include <QDebug>
#include <print>
#include <iostream>
#include <QBluetoothDeviceDiscoveryAgent>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    while(true) {
        std::print("Please enter a command: ");
        std::string input_line;
        if (!getline(std::cin, input_line)) {
            break;
        }

        std::print("You entered: {0}\n", input_line);
    }
    return QCoreApplication::exec();
}
