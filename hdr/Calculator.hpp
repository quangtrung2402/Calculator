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
    int64_t evaluate();
    void addExpression(const char* expression);

signals:
    void notifyResult(Result result);

protected:
    void run();

private:
    void resetCalculator();
    bool isDigit(char &);
    bool isOperator(char &);
    bool isParentheses(char &);
    int64_t getPrecedence(char &);
    int64_t operate(int64_t &, int64_t &, char &);
    int64_t operate();

private:
    std::string *expressionStr;
    Stack_Int *values;
    Stack_Char *operators;
    bool isDone;
    bool runningStatus;
};
#endif //CALCULATOR_HPP
