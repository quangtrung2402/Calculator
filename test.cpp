//calcmain.cpp
#include <iostream>
#include "Calculator.hpp"

using namespace std;

int main()
{
    string expression = "3 + 4 + 5";
    cout << Calculator(expression).evaluate() << endl; // 12

    expression = "3 * 4 + 5";
    cout << Calculator(expression).evaluate() << endl; // 17

    expression = "3 + 4 * 5";
    cout << Calculator(expression).evaluate() << endl; // 23

    expression = "(3 + 4) * 5";
    cout << Calculator(expression).evaluate() << endl; // 15

    expression = "23+12) +12345 -(56)* (3+34) - 46";
    cout << Calculator(expression).evaluate() << endl;
    return 0;
}