#pragma once
#include <string>
#include <exception>


class CalculatorException : std::exception {
public:
	CalculatorException(int index) {
		this->index = index;
	};

	virtual  ~CalculatorException() {};

	virtual const char* what() const throw() {
		FormatMessage();
		return message.c_str();
	}

protected:
	virtual std::string GetMessage() const { return "Calculator failed"; }

private:
	int index;
	mutable std::string message;
	const void FormatMessage() const {
		message = GetMessage();
		if (index != -1) {
			char buff[100];
			sprintf_s(buff, " at %d", index);
			message.append(buff);
		}
	}
};

class DivisionByZeroException : public CalculatorException {
public:
	DivisionByZeroException() : CalculatorException(-1) {}
	virtual ~DivisionByZeroException() {}
protected:
	virtual std::string GetMessage() const { return "Division by zero"; }
};

class ParseException: public CalculatorException {
public:
	ParseException(int index) : CalculatorException(index) {};
	virtual ~ParseException() {};

protected:
	virtual std::string GetMessage() const { return "Wrong expression format"; }
};

class BracesException : public CalculatorException {
public:
	BracesException() : CalculatorException(-1) {}
	virtual ~BracesException() {}
protected:
	virtual std::string GetMessage() const { return "Braces do not match"; }
};