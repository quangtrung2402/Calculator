#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <QObject>
#include <QRunnable>
#include "CustomStack.hpp"

class Calculator : public QObject, public QRunnable
{
     Q_OBJECT
public:
    Calculator();
    ~Calculator();
    int64_t evaluate();

signals:
    void notifyResult(int64_t result);

protected:
    void run();
};
#endif //CALCULATOR_HPP
