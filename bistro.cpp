#include <iostream>
#include <string>
#include <stack>
#include <vector>
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

bool Bistro::isPar(Token token)
{
	if (token.type == Token::Type::OPENPAR
		|| token.type == Token::Type::CLOSEPAR) {
		return true;
	}
	return false;
}

bool Bistro::isOp(Token token)
{
	if (token.type == Token::Type::SUB
		|| token.type == Token::Type::ADD
		|| token.type == Token::Type::MULT
		|| token.type == Token::Type::DIV) {
		return true;
	}
	return false;
}

std::vector<Token> Bistro::lexer(std::string av)
{
	std::vector<Token> tokens;
	std::string current_value;
	bool nextNumNeg = false;
	std::string::iterator it = av.begin();
	for (; it != av.end(); ++it) {
		if ('0' <= *it && *it <= '9') {
			if (nextNumNeg) {
				current_value += '-';
				nextNumNeg = false;
			}
			current_value += *it;
		}
		else {
			if (!current_value.empty()) {
				Token temp(current_value, Token::Type::NUM);
				tokens.push_back(temp);
				current_value.erase(current_value.begin(), current_value.end());
			}
			if (nextNumNeg) {
				std::cout << "Syntax error.\n";
				exit(EXIT_FAILURE);
			}
			if (*it == '+') {
				std::string value_op;
				value_op += *it;
				Token temp(value_op, Token::Type::ADD);
				tokens.push_back(temp);
			}
			else if (*it == '-') {
				if (tokens.empty()
					|| isOp(tokens.back())
					|| tokens.back().type == Token::Type::OPENPAR) {
					nextNumNeg = true;
				}
				else {
					std::string value_op;
					value_op += *it;
					Token temp(value_op, Token::Type::SUB);
					tokens.push_back(temp);
				}
			}
			else if (*it == '*') {
				std::string value_op;
				value_op += *it;
				Token temp(value_op, Token::Type::MULT);
				tokens.push_back(temp);
			}
			else if (*it == '/') {
				std::string value_op;
				value_op += *it;
				Token temp(value_op, Token::Type::DIV);
				tokens.push_back(temp);
			}
			else if (*it == '(') {
				std::string value_par;
				value_par += *it;
				Token temp(value_par, Token::Type::OPENPAR);
				tokens.push_back(temp);
			}
			else if (*it == ')') {
				std::string value_par;
				value_par += *it;
				Token temp(value_par, Token::Type::CLOSEPAR);
				tokens.push_back(temp);
			}
			else if (*it != ' ' && *it != '\0' && *it != '\n') {
				std::cout << "Syntax error \n";
				exit(0);
			}
		}
	}
	if (!current_value.empty()) {
		Token temp(current_value, Token::Type::NUM);
		tokens.push_back(temp);
		current_value.erase(current_value.begin(), current_value.end());
	}
	return tokens;
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
		std::cout << "Syntax error \n";
		exit(EXIT_FAILURE);
	}
	if ((int)_numbers.size() < 2) {
		std::cout << "Syntax error \n";
		exit(EXIT_FAILURE);
	}
	Number rightNum = _numbers.top();
	_numbers.pop();
	Number leftNum = _numbers.top();
	_numbers.pop();
	Number toReturn;
	if (_actions.top().type == Token::Type::ADD) { // si ADD
		if (leftNum.sign == Number::Sign::NEGATIF 
			&& rightNum.sign == Number::Sign::POSITIF) {
			toReturn = Operation::sub(rightNum.number, leftNum.number);
		}
		else if (leftNum.sign == Number::Sign::POSITIF 
			&& rightNum.sign == Number::Sign::NEGATIF) {
			toReturn = Operation::sub(leftNum.number, rightNum.number);
		}
		else if (leftNum.sign == Number::Sign::NEGATIF 
			&& rightNum.sign == Number::Sign::NEGATIF) {
			toReturn = Operation::add(rightNum.number, leftNum.number);
			toReturn.sign = Number::Sign::NEGATIF;
		}
		else {
			toReturn = Operation::add(leftNum.number, rightNum.number);
		}	
	}
	else if (_actions.top().type == Token::Type::SUB) { // SI SUB
		if (leftNum.sign == Number::Sign::NEGATIF 
			&& rightNum.sign == Number::Sign::POSITIF) {
			toReturn = Operation::add(leftNum.number, rightNum.number);
			toReturn.sign = Number::Sign::NEGATIF;
		}
		else if (leftNum.sign == Number::Sign::POSITIF 
			&& rightNum.sign == Number::Sign::NEGATIF) {
			toReturn = Operation::add(leftNum.number, rightNum.number);
		}
		else if (leftNum.sign == Number::Sign::NEGATIF 
			&& rightNum.sign == Number::Sign::NEGATIF) {
			toReturn = Operation::sub(rightNum.number, leftNum.number);
		}
		else {
			toReturn = Operation::sub(leftNum.number, rightNum.number);
		}
	}
	else if (_actions.top().type == Token::Type::MULT) {//SI MULT
		if (leftNum.sign != rightNum.sign) {
			toReturn = Operation::mult(leftNum.number, rightNum.number);
			toReturn.sign = Number::Sign::NEGATIF;
		}
		else {
			toReturn = Operation::mult(leftNum.number, rightNum.number);
		}
		
	}/*
	else if (_actions.top().type == Token::Type::DIV) { //SI DIV
		toReturn = Operation::div(leftNum, rightNum);
		
	}*/
	else {
		std::cout << "Syntax error \n";
		exit(EXIT_FAILURE);
	}
	_actions.pop();
	return toReturn;
}