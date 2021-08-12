#include <iostream>
#include "Server.hpp"

int main()
{
    using namespace std;
restart:
    try
    {
        Server(7000).run();
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
        // Restart;
        goto restart;
    }
    return 0;
}