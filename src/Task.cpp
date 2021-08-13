#include "../hdr/Task.h"

#include <QDebug>

Task::Task()
{
    qDebug() << "MyTask()";
}

void Task::run()
{
    qDebug() << "Task start";

    int iNumber = 0;
    for(int i = 0; i < 100; i++)
    {
        iNumber += 1;
    }

    qDebug() << "Task done";
    emit result(iNumber);
}
