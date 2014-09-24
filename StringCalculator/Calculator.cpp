#include "Calculator.h"
#include <iostream>
#include <algorithm>
#include <vector>

Calculator::Calculator() {}

Calculator::~Calculator() {}

/*static*/
float
Calculator::Evaluate(const std::string& expression) {
    std::string _expression = expression; //we do not want to change input data
    _expression.erase(std::remove_if(_expression.begin(), _expression.end(), isspace), _expression.end());

    std::vector<float> numbers;
    std::vector<OPERATION_TYPE> operations;

    std::string number_str;
    for (int i = 0; i < _expression.length(); ++i) {
        char ch = _expression[i];
        if (isdigit(ch) || ch == '.')
            number_str.push_back(ch);
        else {
            float number = number_str.length() > 0 ? atof(number_str.c_str()) : 0.0f;
            auto operation = Calculator::_ParseBinaryOperation(ch);
        }
    }


    return _EvaluateBraceslessExpression(_expression);
}

/*static*/
float
Calculator::_EvaluateBraceslessExpression(const std::string& expression) {
    std::string leftOperand;
    int operationIndex = -1;
    for (int i = 0; i < expression.length(); ++i) {
        char ch = expression[i];
        if (isdigit(ch) || ch == '.') {
            leftOperand.push_back(ch);
        }
        else {
            operationIndex = i;
            break;
        }
    }

    float result = leftOperand.length() > 0 ? atof(leftOperand.c_str()) : 0.0f;
    if (operationIndex != -1) {
        Calculator::OPERATION_TYPE operation = Calculator::_ParseBinaryOperation(expression[operationIndex]);
        float right = _EvaluateBraceslessExpression(expression.substr(operationIndex+1));
        result = Calculator::_PerformOperation(result, right, operation);
    }
        
    return result;
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