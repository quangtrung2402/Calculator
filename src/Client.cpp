#include "../hdr/Client.hpp"
#include "../hdr/Utility.hpp"
#include <iostream>

Client::Client(QObject *parent) :
    QObject(parent)
{
}

void Client::setSocket(int descriptor)
{
    // Create a new socket for incomming data
    socket = new CustomSocket(this);

    connect(socket, &QTcpSocket::disconnected, this, &Client::deleteLater);
    connect(socket, &QTcpSocket::readyRead, this, &Client::readyRead);

    socket->setSocketDescriptor(descriptor);

    qDebug() << "A new socket created" << descriptor;
}

void Client::readyRead()
{

    DEBUG_MSG("New data:" << socket->readAll());

    Calculator *calculator = new Calculator();
    calculator->setAutoDelete(true);
    connect(calculator, &Calculator::notifyResult, this, &Client::response);

    qDebug() << "Starting a new task using a thread from the QThreadPool, socket id: " << socket->socketDescriptor();
    QThreadPool::globalInstance()->start(calculator);
}

void Client::response(int64_t result)
{
    qDebug() << "response: " << result;
    QByteArray buffer;
    buffer.append("\r\nTask result = " + std::to_string(result));
    socket->write(buffer);
}
