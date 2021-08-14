#include <string>
#include "../hdr/Calculator.hpp"
#include "../hdr/Utility.hpp"

using namespace std;

Calculator::Calculator()
{
}

Calculator::~Calculator()
{
    qDebug() << "Calculator is destroy!";
}

void Calculator::run()
{
    //TO-DO: test
    {
        static int result = 0;
        emit notifyResult(++result);
    }
}
