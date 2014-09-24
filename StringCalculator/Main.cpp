#include <string>
#include <iostream>
#include "Calculator.h"


int main(std::string* args){

	std::cout << "Wtf, man?!" << std::endl;
    int start = 0;
    //std::string test = "23.5 - 8 * (4 + 7)";
    std::string test = "2 + 5*(3 - (6 + 5) - 3 * 2) -7";
    
    std::cout << Calculator::Evaluate(test, start);    
	std::cin.get();
	return 0;
}