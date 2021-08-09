#include <iostream>
#include <string>
#include "Calculator.hpp"
#include "ArrayStack.hpp"

using namespace std;

Calculator::Calculator(std::string &expression)
{
    this->expressionStr = new std::string(expression);
}

Calculator::~Calculator()
{
    delete expressionStr;
    expressionStr = nullptr;
}

void Calculator::sendExpression(std::string &exp)
{
    if (this->expressionStr != nullptr)
    {
        delete expressionStr;
    }
    expressionStr = new std::string(exp);
}

//check if char is a digit.
bool Calculator::isDigit(char &c)
{
    switch (c)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return true;
    default:
        return false;
    }
}

//check if char is an operator.
bool Calculator::isOperator(char &c)
{
    switch (c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
        return true;
    default:
        return false;
    }
}

//determine the precedence of an operator
int Calculator::getPrecedence(char &c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '(':
    case ')':
        return 3;
    default:
        return -1;
    }
}

//evaluate an arithmetic expression
int Calculator::operate(int &val1, int &val2, char &op)
{
    switch (op)
    {
    case '+':
        return val1 + val2;
    case '-':
        return val1 - val2;
    case '*':
        return val1 * val2;
    case '/':
        return val1 / val2;
    default:
        throw std::runtime_error("Not an operator!");
    }
}

//evaluate a string.
int Calculator::evaluate()
{
    CustomStack<int> vals;
    CustomStack<char> ops;

    int val = 0;
    try
    {
        for (int pos = 0; pos < expressionStr->length(); ++pos)
        {
            char spot = expressionStr->at(pos);
            if (isDigit(spot))
            {
                val = (val * 10) + (int)(spot - '0');
            }
            else if (isOperator(spot))
            {
                if (spot == '(')
                {
                    cout << "open parens, val = " << val << endl;
                    ops.push(spot);
                    val = 0;
                }
                else if (vals.empty())
                {
                    cout << "empty stack, val = " << val << endl;
                    vals.push(val);
                    ops.push(spot);
                    val = 0;
                }
                else if (spot == ')')
                {
                    cout << "close parens, val = " << val << endl;
                    vals.push(val);
                    while (ops.top() != '(')
                    {
                        spot = ops.pop();
                        val = vals.pop();
                        int prev = vals.pop();
                        val = operate(prev, val, spot);
                        vals.push(val);
                    }
                    ops.pop();
                    vals.pop();
                    cout << "finished close parens, val = " << val << endl;
                }
                else
                {
                    char prev = ops.top();
                    if (getPrecedence(spot) > getPrecedence(prev))
                    {
                        cout << "high precedence, val = " << val << endl;
                        vals.push(val);
                        ops.push(spot);
                        val = 0;
                    }
                    else
                    {
                        cout << "low precedence, val = " << val << endl;
                        int prevval = vals.pop();
                        char prevop = ops.pop();
                        prevval = operate(prevval, val, prevop);
                        vals.push(prevval);
                        ops.push(spot);
                        val = 0;
                    }
                }
            }
        }

        while (!ops.empty())
        {
            cout << "ops not empty, val = " << val << endl;
            int prev = vals.pop();
            char spot = ops.pop();
            val = operate(prev, val, spot);
        }
    }
    catch (exception e)
    {
        cout << "Exception: " << e.what() << endl;
    }
    return val;
}