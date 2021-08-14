#include "../hdr/Client.h"

Client::Client(QObject *parent) :
    QObject(parent)
{
    int processorCores = QThread::idealThreadCount();
    QThreadPool::globalInstance()->setMaxThreadCount(processorCores);
}

void Client::setSocket(int descriptor)
{
    // Create a new socket for incomming data
    socket = new CustomSocket(this);

    connect(socket, &QTcpSocket::disconnected, socket, &CustomSocket::deleteLater);
    connect(socket, &QTcpSocket::readyRead, this, &Client::readyRead);

    socket->setSocketDescriptor(descriptor);

    qDebug() << "A new socket created at" << descriptor;
}

void Client::readyRead()
{
    qDebug() << socket->readAll();

    Task *task = new Task();
    task->setAutoDelete(true);
    connect(task, &Task::result, this, &Client::result, Qt::QueuedConnection);

    qDebug() << "Starting a new task using a thread from the QThreadPool, socket id: " << socket->socketDescriptor();
    QThreadPool::globalInstance()->start(task);
}

void Client::result(int result)
{
    QByteArray Buffer;
    Buffer.append("\r\nTask result = %d", result);

    socket->write(Buffer);
}
