#pragma once

#include <string>
#include <vector>

#define PI 3.14159265

class Calculator {
public:
    Calculator();
    ~Calculator();

	static float Evaluate(const std::string& expression, std::string& errorMessage);


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

	static float _Evaluate(const std::string& expression, int& index, int& braceCount);

    static OPERATION_TYPE   _ParseSymbolOperation(char ch);

    static OPERATION_TYPE   _ParseWordOperation(const std::string& ch);

    static bool             _IsHighPriorityOperation(OPERATION_TYPE operation);

    static bool             _IsUnaryOperation(OPERATION_TYPE operation);

    static float            _PerformOperation(float value, OPERATION_TYPE operation);

    static float            _PerformOperation(float left, float right, OPERATION_TYPE operation);

    static void             _AddNumber(std::string &number_str, std::vector<float> &numbers, std::vector<OPERATION_TYPE> &operations, bool& isPriorityOperationPending);

    static void             _AddNumber(float number, std::vector<float> &numbers, std::vector<OPERATION_TYPE> &operations, bool &isPriorityOperationPending);

    static float            _Unwind(std::vector<float> &numbers, std::vector<OPERATION_TYPE> &operations);

};

