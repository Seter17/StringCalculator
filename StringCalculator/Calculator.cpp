#include "Calculator.h"
#include <iostream>
#include <algorithm>
#include <vector>

Calculator::Calculator() {}

Calculator::~Calculator() {}

/*static*/
float
Calculator::Evaluate(const std::string& expression, int& index) {
    std::string _expression = expression; //we do not want to change input data
    _expression.erase(std::remove_if(_expression.begin(), _expression.end(), isspace), _expression.end());

    std::vector<float> numbers;
    std::vector<OPERATION_TYPE> operations;

    bool isPriorityOperationPending = false;
    std::string number_str;
    for (index; index < _expression.length(); ++index) {
        char ch = _expression[index];
        if (isdigit(ch) || ch == '.')
            number_str.push_back(ch);
        else {
            if (ch == ')') 
                break;
            if (ch == '(') {
                _AddNumber(Evaluate(_expression, ++index), numbers, operations, isPriorityOperationPending);
                ++index;
            }
            else
                _AddNumber(number_str, numbers, operations, isPriorityOperationPending);

            OPERATION_TYPE operation = Calculator::_ParseBinaryOperation(_expression[index]);
            operations.push_back(operation);
            if (_IsHighPriorityOperator(operation)) {
                isPriorityOperationPending = true;
            }
        }
    }

    Calculator::_AddNumber(number_str, numbers, operations, isPriorityOperationPending);

    //vectors contains only numbers and simple binary operations
    float left = numbers[0];
    numbers.erase(numbers.begin());
    while (numbers.size() > 0)
    {
      
        float right = numbers[0];
        auto operation = operations[0];

        operations.erase(operations.begin());
        numbers.erase(numbers.begin());

        left = Calculator::_PerformOperation(left, right, operation);
    }

    return left;
}

/*static*/
Calculator::OPERATION_TYPE
Calculator::_ParseBinaryOperation(char ch) {
    switch (ch) {
        case '+':
            return ADDITION;
            break;
        case '-':
            return SUBSTRACTION;
            break;
        case '*':
            return MULTIPLICATION;
            break;
        case '/':
            return DIVISION;
            break;
        default:
            return UKNOWN;
            break;
    }
}


/*static*/
float
Calculator::_PerformOperation(float left, float right, OPERATION_TYPE operation) {
    if (operation == ADDITION) {
        return left + right;
    }
    if (operation == SUBSTRACTION) {
        return left - right;
    }
    if (operation == MULTIPLICATION) {
        return left * right;
    }
    if (operation == DIVISION) {
        if (right == 0) throw 0;
        return left / right;
    }
    throw 2;
}

/*static*/
float
Calculator::_PerformOperation(float value, OPERATION_TYPE operation) {
    if (operation == SIN) {
        return sin(value);
    }
    if (operation == COS) {
        return cos(value);
    }

    throw 3;
}

/*static*/
bool
Calculator::_IsHighPriorityOperator(OPERATION_TYPE operation) {
    return operation == MULTIPLICATION || operation == DIVISION;
}

/*static*/
void 
Calculator::_AddNumber(std::string &number_str, std::vector<float> &numbers, std::vector<OPERATION_TYPE> &operations, bool& isPriorityOperationPending) {
    float number = number_str.length() > 0 ? atof(number_str.c_str()) : 0.0f;
    number_str.clear();
    _AddNumber(number, numbers, operations, isPriorityOperationPending);
}

/*static*/
void 
Calculator::_AddNumber(float number, std::vector<float> &numbers, std::vector<OPERATION_TYPE> &operations, bool &isPriorityOperationPending) {
    if (isPriorityOperationPending) {
        float left = numbers.back();
        numbers.pop_back();
        number = _PerformOperation(left, number, operations.back());
        operations.pop_back();
        isPriorityOperationPending = false;
    }
    numbers.push_back(number);
}
