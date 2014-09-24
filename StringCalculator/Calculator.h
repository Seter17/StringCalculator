#pragma once

#include <string>
#include <vector>

class Calculator {
public:
    Calculator();
    ~Calculator();

    static float Evaluate(const std::string& expression);
private:

    enum OPERATION_TYPE {
        UKNOWN,
        ADDITION,
        SUBSTRACTION,
        MULTIPLICATION,
        DIVISION,
        SIN,
        COS
    };
    static OPERATION_TYPE   _ParseBinaryOperation(char ch);

    static bool             _IsHighPriorityOperator(OPERATION_TYPE operation);

    static float            _PerformOperation(float value, OPERATION_TYPE operation);

    static float            _PerformOperation(float left, float right, OPERATION_TYPE operation);

    static void             _AddNumber(std::string &number_str, std::vector<float> &numbers, std::vector<OPERATION_TYPE> &operations, bool& isPriorityOperationPending);
};

