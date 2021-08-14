#ifndef RESULT_H
#define RESULT_H

#include <stdint.h>
#include <string>

enum class ResultCode{
    OK = 0,
    ERROR
};

class Result{
public:
    Result(ResultCode code, int64_t result, std::string msg = ""):
        code(code),
        calculatedResult(result),
        message(msg)
    {}

    Result(ResultCode code, std::string msg):
        code(code),
        calculatedResult(0),
        message(msg)
    {}

    ResultCode code;
    int64_t calculatedResult;
    std::string message;
};

#endif // RESULT_H
