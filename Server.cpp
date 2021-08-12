#include <iostream>
#include "Server.hpp"

using namespace std;

Server::Server(int port)
{
    cout << "Created an server at port: " << port << endl;
}

Server::~Server()
{
}

void Server::run()
{
    cout << "Server started!" << endl;
    while (true)
    {
    }
}
