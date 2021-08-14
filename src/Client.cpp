#include "../hdr/Client.hpp"
#include "../hdr/Utility.hpp"
#include <iostream>

Client::Client(int descriptor, QObject *parent) :
    QTcpSocket(parent)
{
    connect(this, &Client::disconnected, this, &Client::deleteLater);
    connect(this, &Client::readyRead, this, &Client::readyReadNewData);
    this->setSocketDescriptor(descriptor);
    qDebug() << "A new client is created, descriptor: " << descriptor;
}

Client::~Client()
{
    qDebug() << "Client is disconnected!";
}

void Client::readyReadNewData()
{
    DEBUG_MSG("New data:" << this->readAll());

    Calculator *calculator = new Calculator();
    calculator->setAutoDelete(true);
    connect(calculator, &Calculator::notifyResult, this, &Client::response);

    qDebug() << "Starting a new task using a thread from the QThreadPool, socket id: " << this->socketDescriptor();
    QThreadPool::globalInstance()->start(calculator);
}

void Client::response(int64_t result)
{
    qDebug() << "response: " << result;
    QByteArray buffer;
    buffer.append("\r\nTask result = " + std::to_string(result));
    this->write(buffer);
}
