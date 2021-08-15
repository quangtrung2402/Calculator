#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <QObject>
#include <QRunnable>
#include "CustomStack.hpp"
#include "Result.hpp"

typedef CustomStack<int64_t> Stack_Int;
typedef CustomStack<char> Stack_Char;

class Calculator : public QObject, public QRunnable
{
    Q_OBJECT
public:
    Calculator(QObject *parent);
    ~Calculator();
    void addExpression(const char* expression);

signals:
    void notifyResult(Result result);

protected:
    void run();

private:
    int64_t evaluate();
    void resetCalculator();
    bool isDigit(const char &);
    bool isOperator(const char &);
    bool isParentheses(const char &);
    int64_t getCurrentNumber(size_t &pos, char &spot);
    int64_t getPrecedence(const char &);
    int64_t operate(const int64_t &, const int64_t &, const char &);
    int64_t operate();

private:
    std::string *expressionStr;
    Stack_Int *values;
    Stack_Char *operators;
    bool isDone;
    bool runningStatus;
};
#endif //CALCULATOR_HPP
