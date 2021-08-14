#include "../hdr/Server.hpp"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
    int processorCores = QThread::idealThreadCount();
    qDebug() << "Setup max thread count for the Thread Pool: " << processorCores;
    QThreadPool::globalInstance()->setMaxThreadCount(processorCores);
}

void Server::start(int port)
{
    if(listen(QHostAddress::Any, port))
    {
        qDebug() << "Server started at port" << port;
    }
    else
    {
        qDebug() << "Server is not started!";
        exit(EXIT_FAILURE);
    }
}

void Server::incomingConnection(long long handle)
{
    Client *client = new Client(this);
    client->setSocket(handle);
}
