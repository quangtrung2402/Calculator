//calcmain.cpp
#include <iostream>
#include "Calculator.hpp"

using namespace std;

int main()
{
    string expression = "3 + 4 + 5";
    Calculator calculator(expression);
    cout << calculator.evaluate() << endl; // 12

    expression = "3 * 4 + 5";
    calculator.sendExpression(expression);
    cout << calculator.evaluate() << endl; // 17

    expression = "3 + 4 * 5";
    calculator.sendExpression(expression);
    cout << calculator.evaluate() << endl; // 23

    expression = "(3 + 4) * 5";
    calculator.sendExpression(expression);
    cout << calculator.evaluate() << endl; // 15
    return 0;
}