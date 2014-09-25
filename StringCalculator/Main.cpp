#include <string>
#include <iostream>
#include "Calculator.h"


int main(std::string* args){

	std::cout << "Wtf, man?!" << std::endl;
    int start = 0;
    //std::string test = "23.5 - 8 * (4 + 7)";
    //std::string test = "2 + 5*(3 - (6 + 5) - 3 * 2) -7";
    //std::string test = "-2 + sin(30)";
    std::string test = "2 + 5*(3 - (6 + sin(30)/0) - 3 * 2) -7";
    
	std::string errorMessage;
	float value =  Calculator::Evaluate(test, errorMessage);

	if (errorMessage.empty())
		std::cout << value;
	else
		std::cout <<errorMessage;
	std::cin.get();
	return 0;
}