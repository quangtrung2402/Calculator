#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include "CustomStack.hpp"

typedef CustomStack<int64_t> Stack_Int;
typedef CustomStack<char> Stack_Char;

class Calculator
{
public:
    Calculator(std::string &);
    ~Calculator();
    int64_t evaluate();

private:
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
};
#endif //CALCULATOR_HPP