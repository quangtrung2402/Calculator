#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>
#include "Task.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void setSocket(int descriptor);

signals:

public slots:
    void readyRead();

    void result(int result);

private:
    QTcpSocket *socket;
};

class CustomSocket : public QTcpSocket{
public:
    CustomSocket(QObject *parent):QTcpSocket(parent){}
    ~CustomSocket(){
        qDebug() << "One socket has been destroy";
    }
};

#endif // CLIENT_H
