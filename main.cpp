#include <QCoreApplication>
#include<iostream>

#include<hdr/Server.h>

int main(int argc, char *argv[])
{
    if ((argc < 2) ||
            (!std::atoi(argv[1])))
    {
        std::cerr << "Usage: CalculatorServer <port>\nExample: CalculatorServer 1234" << std::endl;;
        return 1;
    }
    QCoreApplication a(argc, argv);

    // Create an instance of a server and then start it.
    Server server;
    server.start(std::atoi(argv[1]));

    return a.exec();
}
