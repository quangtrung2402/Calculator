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
    ElapsedTime()
    {
        startTime = clock();
    }
    ~ElapsedTime()
    {
        qDebug() << "Elapsed time:" << clock() - startTime;
    }

private:
    clock_t startTime;
};

#endif //UTILITY_HPP
