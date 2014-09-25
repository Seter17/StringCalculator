#include <string>
#include <iostream>
#include <map>
#include "Calculator.h"


int main(int argc,      // Number of strings in array argv
	char *argv[],   // Array of command-line argument strings
	char *envp[]) {

	if (argv == 0) {
		std::cout << "Wtf, man?!" << std::endl;
	}

	int start = 0;
	std::string expression;
	for (int i = 1; i < argc; ++i) {
		expression.append(argv[i]);
	}

	if (expression == "test") {
		//launch tests
		std::cout << "Launching tests" << std::endl;
		std::map<std::string, std::string> cases;
		cases["23.5 - 8 * (4 + 7)"] =  "-64.5";
		cases["2 + 5*(3 - (6 + 5) - 3 * 2) -7"] =  "-75";
		cases["2 + 5*(3 - (6 + sin(30)/0) - 3 * 2) -7"] =  "error";
		cases["-2 + sin(30)"] = "-1.5";
		cases["sin(30) - 2"] = "-1.5";

		std::string errorMessage;
		for (auto testCase: cases)
		{
			std::cout << "Test expression: " << testCase.first << std::endl;
			std::cout << "Expected result: " << testCase.second << std::endl;

			float value = Calculator::Evaluate(testCase.first, errorMessage);
			std::string result; 
			if (errorMessage.empty()) {
				char buf[64];
				sprintf(buf, "%.20g", value);
				result = buf;
			}
			else {
				result = "error";
			}


			std::cout << "Obtained result: " << result << std::endl;
			std::cout << "Passed:" << ((result == testCase.second) ? "true" : "false") << std::endl;
			errorMessage.clear();
		}
	}
	else {

		std::cout << "Input expression: " << expression << std::endl;
		std::string errorMessage;

		float value = Calculator::Evaluate(expression, errorMessage);

		if (errorMessage.empty())
			std::cout << "Result: " << value << std::endl;
		else
			std::cout << errorMessage << std::endl;
	}
	return 0;
}