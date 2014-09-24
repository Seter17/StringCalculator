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
    std::string operation_str;
    for (index; index < _expression.length(); ++index) {
        if (isdigit(_expression[index]) || _expression[index] == '.')
            number_str.push_back(_expression[index]);
        else {
            if (_expression[index] == '(') {
                _AddNumber(Evaluate(_expression, ++index), numbers, operations, isPriorityOperationPending);
                ++index;
            }
            else
                _AddNumber(number_str, numbers, operations, isPriorityOperationPending);
            
            if (_expression[index] == ')')
                break;

            OPERATION_TYPE operation = Calculator::_ParseSymbolOperation(_expression[index]);
            if (operation == UKNOWN) {
                //parse until next digit
                while (index != _expression.length() && _expression[index] != '(' && _expression[index] != '.' && !isdigit(_expression[index])) {
                    operation_str.push_back(_expression[index]);
                    ++index;
                }
                --index;
                operation = Calculator::_ParseWordOperation(operation_str);
                if (operation == UKNOWN) {
                    //exception for sure;
                }
                operation_str.clear();
            }

            operations.push_back(operation);
            //negative number case
            if (operation == SUBSTRACTION && numbers.size() == 0)
                numbers.push_back(0.0f);

            if (_IsHighPriorityOperation(operation)) {
                isPriorityOperationPending = true;
            }
        }
    }

    Calculator::_AddNumber(number_str, numbers, operations, isPriorityOperationPending);

    //vectors contains only numbers and simple binary operations
    return _Unwind(numbers, operations);

}

/*static*/
Calculator::OPERATION_TYPE
Calculator::_ParseSymbolOperation(char ch) {
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
Calculator::OPERATION_TYPE
Calculator::_ParseWordOperation(const std::string& word) {
    if (word == "sin") {
        return SIN;
    }
    if (word == "cos") {
        return COS;
    }
    return UKNOWN;
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
        return sin(value*PI / 180);
    }
    if (operation == COS) {
        return cos(value*PI / 180);
    }

    throw 3;
}

/*static*/
bool
Calculator::_IsHighPriorityOperation(OPERATION_TYPE operation) {
    return operation == MULTIPLICATION || operation == DIVISION || operation == SIN || operation == COS;
}

/*static*/
bool
Calculator::_IsUnaryOperation(OPERATION_TYPE operation) {
    return operation == SIN || operation == COS;
}

/*static*/
void
Calculator::_AddNumber(std::string &number_str, std::vector<float> &numbers, std::vector<OPERATION_TYPE> &operations, bool& isPriorityOperationPending) {
    if (number_str.length() == 0)
        return;
    float number =  atof(number_str.c_str());
    number_str.clear();
    _AddNumber(number, numbers, operations, isPriorityOperationPending);
}

/*static*/
void
Calculator::_AddNumber(float number, std::vector<float> &numbers, std::vector<OPERATION_TYPE> &operations, bool &isPriorityOperationPending) {
    if (isPriorityOperationPending) {
        auto operation = operations.back();
        operations.pop_back();

        if (!Calculator::_IsUnaryOperation(operation)) {
            float left = numbers.back();
            numbers.pop_back();
            number = _PerformOperation(left, number, operation);
        }
        else {
            number = _PerformOperation(number, operation);
        }

        isPriorityOperationPending = false;
    }
    numbers.push_back(number);
}

float Calculator::_Unwind(std::vector<float> &numbers, std::vector<OPERATION_TYPE> &operations) {
    float left = numbers[0];
    numbers.erase(numbers.begin());
    while (numbers.size() > 0) {

        float right = numbers[0];
        auto operation = operations[0];

        operations.erase(operations.begin());
        numbers.erase(numbers.begin());

        left = Calculator::_PerformOperation(left, right, operation);
    }

    return left;
}
