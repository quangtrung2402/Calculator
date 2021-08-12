#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

class Server
{
public:
    Server(int port);
    virtual ~Server();
    void run();
};

#endif //SERVER_HPP