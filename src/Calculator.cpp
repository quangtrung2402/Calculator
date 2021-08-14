#include <string>
#include "../hdr/Calculator.hpp"
#include "../hdr/Utility.hpp"

using namespace std;

Calculator::Calculator(QObject *parent):QObject(parent),
    expressionStr(new std::string()),
    values(new Stack_Int()),
    operators(new Stack_Char()),
    isDone(false)
{
}

Calculator::~Calculator()
{
    qDebug() << "Calculator is destroy!";
    delete expressionStr;
    expressionStr = nullptr;

    delete values;
    values = nullptr;

    delete operators;
    operators = nullptr;
}

bool Calculator::isDigit(char &c)
{
    //TO-DO: can use isdegit()
    DEBUG_MSG("Calculator::isDigit(" << c << ")");
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

bool Calculator::isOperator(char &c)
{
    DEBUG_MSG("Calculator::isOperator(" << c << ")");
    switch (c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        return true;
    default:
        return false;
    }
}

bool Calculator::isParentheses(char &c)
{
    DEBUG_MSG("Calculator::isParentheses(" << c << ")");
    switch (c)
    {
    case '(':
    case ')':
        return true;
    default:
        return false;
    }
}

int64_t Calculator::getPrecedence(char &c)
{
    DEBUG_MSG("Calculator::getPrecedence(" << c << ")");
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

int64_t Calculator::operate(int64_t &val1, int64_t &val2, char &op)
{
    DEBUG_MSG("Calculator::operate(" << val1 << op << val2 << ")");
    switch (op)
    {
    case '+':
        return val1 + val2;
    case '-':
        return val1 - val2;
    case '*':
        return val1 * val2;
    case '/':
        if(0 == val2){
            throw std::runtime_error("Something went wrong! Zero devided");
        }
        return val1 / val2;
    default:
        DEBUG_MSG("Not an operator!");
        throw std::runtime_error("Something went wrong! Not an operator!");
    }
}

int64_t Calculator::operate()
{
    DEBUG_MSG("Calculator::operate()");
    int64_t result = (nullptr == values || values->empty())
            ? 0
            : values->pop();

    while (nullptr != operators &&
           !operators->empty() &&
           operators->top() != '(')
    {
        DEBUG_MSG("\toperators->size() = " << operators->size()
                  << ", values->size() = " << (nullptr == values ?: values->size()));
        char op = operators->pop();

        int64_t prevVal = (nullptr == values || values->empty())
                ? 0
                : values->pop();

        result = operate(prevVal, result, op);
    }

    return result;
}

int64_t Calculator::evaluate()
{
    ElapsedTime t;
    DEBUG_MSG("Calculator::evaluate()");
    int64_t result = 0;
    try
    {
        if (nullptr == expressionStr)
        {
            throw runtime_error("Something went wrong! Don't have expression!");
        }

        for (size_t pos = 0; pos < expressionStr->length(); ++pos)
        {
            char spot = expressionStr->at(pos);
            DEBUG_MSG("\tCharacter handling: " << spot);

            if (isDigit(spot)) // If is a digit, gets all digits in the current number
            {
                int num = spot - '0';
                while (pos + 1 < expressionStr->length() &&
                       isDigit(expressionStr->at(pos + 1)))
                {
                    num = num * 10 + (expressionStr->at(++pos) - '0');
                }

                if (nullptr != values)
                {
                    values->push(num);
                }
            }
            else if (std::isspace(spot)) // If is an space, ignore
            {
            }
            else if (isOperator(spot)) //If is an operator, calculates
            {
                if (operators != nullptr)
                {
                    if (operators->empty()) //If is first operator, just save it
                    {
                        operators->push(spot);
                    }
                    else
                    {
                        char prevOp = operators->top();
                        if ('(' == prevOp) //If is first operator in the parentheses, just save it
                        {
                            DEBUG_MSG("\tStart operand in parentheses");
                            operators->push(spot);
                        }
                        else //Else, considers to calculate
                        {
                            if (getPrecedence(spot) > getPrecedence(prevOp))
                            {
                                DEBUG_MSG("\tHandling the higher precedence");
                                operators->push(spot);
                            }
                            else
                            {
                                DEBUG_MSG("\tHandling the lower precedence, calculate!");
                                if (nullptr != values)
                                {
                                    values->push(operate());
                                }
                                operators->push(spot);
                            }
                        }
                    }
                }
            }
            else if (isParentheses(spot)) //If is an parentheses, considers to calculate
            {
                if ('(' == spot) //If is open parenthese, just save it
                {
                    DEBUG_MSG("\tOpen parentheses");
                    if (operators != nullptr)
                    {
                        operators->push(spot);
                    }
                }
                else //Else, it is close parenthese, calculates
                {
                    DEBUG_MSG("\tClose parentheses, operators.top() = " << char(nullptr == operators || operators->empty() ?: operators->top()));

                    if (nullptr != values)
                    {
                        values->push(operate());
                    }

                    if (operators != nullptr &&
                            !operators->empty() &&
                            '(' == operators->top())
                    {
                        operators->pop();
                    }

                    DEBUG_MSG("\tFinished close parentheses, values.top() = " << (nullptr == values || values->empty() ?: values->top()));
                }
            }
            else
            {
                DEBUG_MSG("Not a number or an operator!");
                throw runtime_error("Something went wrong! Not a number or an operator!");
            }
        }

        if (operators != nullptr &&
                !operators->empty())
        {
            DEBUG_MSG("\toperators stack is not empty, finish calculates");
            result = operate();
        }
    }
    catch (const exception &e)
    {
        DEBUG_MSG("Exception: " << e.what());
    }

    DEBUG_MSG("Result = " + values->size());
    values->push(result);
    expressionStr->clear();
    return result;
}

void Calculator::addExpression(const char* expression)
{
    if(expressionStr != nullptr){
        DEBUG_MSG(expressionStr->size());
        expressionStr->append(expression);
        DEBUG_MSG(expressionStr->size());
    }
}

void Calculator::run()
{
    //TO-DO: test
//    {
//        static int result = 0;
//        emit notifyResult(++result);
//    }
    evaluate();
    isDone = true;
    DEBUG_MSG(values->size());
int64_t result = values->pop();

    emit notifyResult(result);

while(values->size() > 0){
    DEBUG_MSG(values->pop());
}

    if (isDone &&
            1 == values->size())
    {
        emit notifyResult(values->pop());
    }
}
