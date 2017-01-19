#include <iostream>
#include <string>
#include <stack>
#include <stdbool.h>
#include <cstdlib>

#include "bistro.hpp"
#include "token.hpp"
#include "number.hpp"
#include "utility.hpp"
#include "operation.hpp"

Bistro::Bistro(char *argv)
{
	std::string arg(argv);
	_tokens = lexer(arg);
	stacking();
}

void Bistro::printStacks()
{
	while (!_numbers.empty()) {
		std::cout << _numbers.top() << "\n";
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
			_numbers.push(Utility::stringToNumber((*it).value));
		}
		else if ((*it).type == Token::Type::OPENPAR) {
			_actions.push(*it);
		}
		else if ((*it).type == Token::Type::CLOSEPAR) {
			while (_actions.top().type != Token::Type::OPENPAR) {
				_numbers.push(calcul());
			}
			_actions.pop();
		}
		else if ((*it).type == Token::Type::ADD || (*it).type == Token::Type::SUB) {
			if((!_actions.empty()) && ((_actions.top().type == Token::Type::MULT) 
				|| (_actions.top().type == Token::Type::DIV))) {
				_numbers.push(calcul());
			}
			_actions.push(*it);
		}
		else if ((*it).type == Token::Type::MULT || (*it).type == Token::Type::DIV) {
			if((!_actions.empty()) && ((_actions.top().type == Token::Type::MULT) 
				|| (_actions.top().type == Token::Type::DIV))) {
				_numbers.push(calcul());
			}
			_actions.push(*it);
		}
	}
	unstacking();
}

void Bistro::unstacking()
{
	while (!_actions.empty()) {
		_numbers.push(calcul());
	}
	if ((int)_numbers.size() > 1)
	{
		std::cout << "Syntax error \n";
		exit(EXIT_FAILURE);
	}
	printStacks();
}

Number Bistro::calcul()
{	
	if (_actions.empty()) {
		std::cout << "Error : action empty\n";
		exit(EXIT_FAILURE);
	}
	std::vector<int> rightNum = _numbers.top().number;
	_numbers.pop();
	std::vector<int> leftNum = _numbers.top().number;
	_numbers.pop();
	Number toReturn;
	if (_actions.top().type == Token::Type::ADD) {
		//if (leftNum.sign == Number::Sign::NEGATIF && rightNum)
		toReturn = Operation::add(leftNum, rightNum);
	}
	else if (_actions.top().type == Token::Type::SUB) {
		toReturn = Operation::sub(leftNum, rightNum);
	}
	else if (_actions.top().type == Token::Type::MULT) {
		toReturn = Operation::mult(leftNum, rightNum);
	}/*
	else if (_actions.top().type == Token::Type::DIV) {
		toReturn = Operation::div(leftNum, rightNum);
		
	}*/
	else {
		std::cout << "Error operator " << _actions.top() << ".\n";
		exit(EXIT_FAILURE);
	}
	_actions.pop();
	return toReturn;
}