#ifndef UTILITY_HPP
#define UTILITY_HPP

// #define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(str)                 \
    {                                  \
        std::cout << str << std::endl; \
    }
#else
#define DEBUG_MSG(str) \
    {                  \
    }
#endif

#include <time.h>
#include <iostream>

class ElapsedTime
{
public:
    ElapsedTime()
    {
        startTime = clock();
    }
    ~ElapsedTime()
    {
        std::cout << "Elapsed time: " << clock() - startTime << std::endl;
    }

private:
    clock_t startTime;
};

#endif //UTILITY_HPP