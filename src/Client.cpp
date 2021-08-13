#include "../hdr/Client.h"

Client::Client(QObject *parent) :
    QObject(parent)
{
    //TO-DO: get CPU core
    QThreadPool::globalInstance()->setMaxThreadCount(5);
}

void Client::setSocket(int descriptor)
{
    // Create a new socket for incomming data
    socket = new CustomSocket(this);

    connect(socket, &QTcpSocket::connected, this, &Client::connected);
    connect(socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::readyRead);

    socket->setSocketDescriptor(descriptor);

    qDebug() << "A new socket created at" << descriptor;
}

void Client::connected()
{
    qDebug() << "Client connected event";
}

void Client::disconnected()
{
    qDebug() << "Client disconnected";
}

void Client::readyRead()
{
    qDebug() << socket->readAll();

    Task *task = new Task();
    task->setAutoDelete(true);
    connect(task, &Task::result, this, &Client::result, Qt::QueuedConnection);

    qDebug() << "Starting a new task using a thread from the QThreadPool";
    QThreadPool::globalInstance()->start(task);
}

void Client::result(int result)
{
    QByteArray Buffer;
    Buffer.append("\r\nTask result = %d", result);

    socket->write(Buffer);
}
