#pragma once

#include <string>

class Calculator {
public:
    Calculator();
    ~Calculator();

    static
        float Evaluate(const std::string& expression);
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

    static
        float _EvaluateBraceslessExpression(const std::string& expression);

    static
        OPERATION_TYPE _ParseBinaryOperation(char ch);

    static
        float _PerformOperation(float value, OPERATION_TYPE operation);

    static
        float _PerformOperation(float left, float right, OPERATION_TYPE operation);
};

