#ifndef UTILITY_HPP
#define UTILITY_HPP

#ifdef QT_DEBUG
#define DEBUG_MSG(str)   \
    {                    \
        qDebug() << str; \
    }
#else
#define DEBUG_MSG(str) \
    {                  \
    }
#endif

#include <time.h>
#include <QDebug>

class ElapsedTime
{
public:
    ElapsedTime(std::string message): msg(message),
        startTime(clock())
    {
    }
    ~ElapsedTime()
    {
        qDebug() << msg.c_str() << ":" << clock() - startTime;
    }

private:
    std::string msg;
    clock_t startTime;
};

#endif //UTILITY_HPP
