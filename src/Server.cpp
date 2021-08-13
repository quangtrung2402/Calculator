#include "../hdr/Server.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
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
    }
}

void Server::incomingConnection(long long handle)
{
    Client *client = new Client(this);
    client->setSocket(handle);
}
