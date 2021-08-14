#include "../hdr/Client.hpp"
#include "../hdr/Utility.hpp"

Client::Client(int descriptor, QObject *parent) :
    QTcpSocket(parent),
    calculator(new Calculator(this))
{
    connect(this, &Client::disconnected, this, &Client::deleteLater);
    connect(this, &Client::readyRead, this, &Client::readyReadNewData);
    this->setSocketDescriptor(descriptor);
    qDebug() << "A new client is created, descriptor: " << descriptor;

    calculator->setAutoDelete(false);
    connect(calculator, &Calculator::notifyResult, this, &Client::response);
}

Client::~Client()
{
    qDebug() << "Client is disconnected!";
}

void Client::readyReadNewData()
{
    const char* message = this->readAll();
    DEBUG_MSG("New data:" << message);

    calculator->addExpression(message);
    qDebug() << "Starting a new task using a thread from the QThreadPool, socket id: " << this->socketDescriptor();
    QThreadPool::globalInstance()->start(calculator);
}

void Client::response(int64_t result)
{
    qDebug() << "response: " << result;
    QByteArray buffer;
    buffer.append("\r\nTask result = " + std::to_string(result) + "\n");
    this->write(buffer);
}
