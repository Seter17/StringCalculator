#include <string>
#include <iostream>
#include "Calculator.h"


int main(std::string* args){

	std::cout << "Wtf, man?!" << std::endl;
    std::cout << Calculator::Evaluate ("23.5 - 8 * 4 + 7");
	std::cin.get();
	return 0;
}