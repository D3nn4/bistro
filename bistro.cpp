#include <iostream>
#include <string>
#include <stack>
#include <stdbool.h>

#include "bistro.hpp"
#include "token.hpp"
#include "number.hpp"
#include "utility.hpp"
#include "operation.hpp"

Bistro::Bistro(char *argv)
{
	std::string arg(argv);
	_tokens = lexer(arg);
}

bool Bistro::isVIP(Token token)
{
	if (token.value.compare("*") || token.value.compare("/"))
		return true;
	return false;
}

void Bistro::printStacks()
{
	while (!_numbers.empty()) {
		std::cout << _numbers.top();
		_numbers.pop(); 
	}
	while (!_actions.empty()) {
		std::cout << _actions.top() << "\n";
		_actions.pop();
	}
}
void Bistro::stacking()
{
	std::vector<Token>::iterator it = _tokens.begin();
	for (; it < _tokens.end(); ++it) {
		if ((*it).type == Token::Type::NUM) {
			Number temp = Utility::stringToNumber((*it).value);
			_numbers.push(temp);
		}
		else {
			_actions.push((*it).value);
		}
	}
		//printStacks();

}

void Bistro::calcul()
{
	if (_actions.empty() || _numbers.empty()) {
		std::cout << "error calcul \n";
		exit(0);
	}
	while ((int)_actions.size() > 0) {
		if (_actions.top().compare("+") == 0) {
			std::cout << "add ";
			Number num2 = _numbers.top();
			std::cout << num2 << " and ";
			_numbers.pop();
			Number num1 = _numbers.top();
			std::cout << num1 << " = ";
			_numbers.pop();
			Number result = Operation::add(num1.getNumber(), num2.getNumber());
			_numbers.push(result);
			std::cout << result << "\n";
			_actions.pop();
		}
		else if (_actions.top().compare("-") == 0) {
			std::cout << "sub ";
			Number num2 = _numbers.top();
			std::cout << num2 << " and ";
			_numbers.pop();
			Number num1 = _numbers.top();
			std::cout << num1 << " = ";
			_numbers.pop();
			Number result = Operation::sub(num1.getNumber(), num2.getNumber());
			_numbers.push(result);
			std::cout << result << "\n";
			_actions.pop();
		}
		else if (_actions.top().compare("*") == 0) {
			std::cout << "mult ";
			Number num2 = _numbers.top();
			std::cout << num2 << " and ";
			_numbers.pop();
			Number num1 = _numbers.top();
			std::cout << num1 << " = ";
			_numbers.pop();
			Number result = Operation::mult(num1.getNumber(), num2.getNumber());
			_numbers.push(result);
			std::cout << result << "\n";
			_actions.pop();
		}/*
		else if (_actions.top().compare("/") == 0) {
			Number num2 = _numbers.top();
			_numbers.pop();
			Number num1 = _numbers.top();
			_numbers.pop();
			Number result = Operation::div(num1.getNumber(), num2.getNumber());
			_numbers.push(result);
			_actions.pop();
		}*/
		else {
			std::cout << "other";
		}
		
	}
	std::cout << _numbers.top();
}