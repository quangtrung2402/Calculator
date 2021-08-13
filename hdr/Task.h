#ifndef TASK_H
#define TASK_H

#include <QRunnable>
#include <QObject>
#include <QRunnable>

class Task : public QObject, public QRunnable
{
    Q_OBJECT
public:
    Task();

signals:
    void result(int result);

protected:
    void run();
};

#endif // TASK_H
