#include <string>
#include <iostream>
#include "Calculator.h"


int main(int argc,      // Number of strings in array argv
		char *argv[],   // Array of command-line argument strings
		char *envp[]) {

	if (argv == 0)
	{
		std::cout << "Wtf, man?!" << std::endl;
	}
	
	if (argv[1] == "test") {
		//launch tests
		std::cout << "Launching tests" << std::endl;
	}
	else {
		int start = 0;
		//std::string test = "23.5 - 8 * (4 + 7)";
		//std::string test = "2 + 5*(3 - (6 + 5) - 3 * 2) -7";
		//std::string test = "-2 + sin(30)";
		//std::string test = "2 + 5*(3 - (6 + sin(30)/0) - 3 * 2) -7";
		std::string expression;
		for (int i = 1; i < argc; ++i)
		{
			expression.append(argv[i]);
		}
		std::cout << expression << std::endl;
		std::string errorMessage;

		float value = Calculator::Evaluate(expression, errorMessage);

		if (errorMessage.empty())
			std::cout << value;
		else
			std::cout << errorMessage;
	}
	return 0;
}