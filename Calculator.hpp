#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>

class Calculator
{
public:
    Calculator(std::string &);
    ~Calculator();
    int evaluate();
    void sendExpression(std::string &);

private:
    bool isDigit(char &);
    bool isOperator(char &);
    int getPrecedence(char &);
    int operate(int &, int &, char &);

private:
    std::string *expressionStr;
};
#endif //CALCULATOR_HPP