#ifndef SERVER_HPP
#define SERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "Client.hpp"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void start(int);

protected:
    void incomingConnection(long long handle);

signals:

public slots:

};

#endif // SERVER_HPP
