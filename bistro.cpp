#include <iostream>
#include <string>
#include <stack>
#include <stdbool.h>

#include "bistro.hpp"
#include "token.hpp"
#include "number.hpp"
#include "utility.hpp"

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
	
	while (!_numbers.empty()) {
		std::cout << _numbers.top();
		_numbers.pop(); 
	}
	
	while (!_actions.empty()) {
		std::cout << _actions.top() << "\n";
		_actions.pop();
	}
}