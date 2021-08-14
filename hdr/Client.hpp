#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>
#include "Calculator.hpp"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client(){
        qDebug() << "Client is disconnected!";
    }
    void setSocket(int descriptor);

signals:

public slots:
    void readyRead();

    void response(int64_t result);

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

#endif // CLIENT_HPP
