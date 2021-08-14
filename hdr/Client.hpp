#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>
#include "Calculator.hpp"

class Client : public QTcpSocket
{
    Q_OBJECT
public:
    explicit Client(int descriptor, QObject *parent = 0);
    ~Client();

signals:

public slots:
    void readyReadNewData();

    void response(int64_t result);

private:
    Calculator *calculator;
};

#endif // CLIENT_HPP
