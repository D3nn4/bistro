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

Bistro::Bistro(std::string str)
{
	if (lexer(str)) {
		stacking();
	}
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

bool Bistro::lexer(std::string av)
{
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
				_tokens.push_back(temp);
				current_value.erase(current_value.begin(), current_value.end());
			}
			if (nextNumNeg) {
				Utility::syntaxErrorMsg();
				return false;
			}
			if (*it == '+') {
				std::string value_op;
				value_op += *it;
				Token temp(value_op, Token::Type::ADD);
				_tokens.push_back(temp);
			}
			else if (*it == '-') {
				if (_tokens.empty()
					|| isOp(_tokens.back())
					|| _tokens.back().type == Token::Type::OPENPAR) {
					nextNumNeg = true;
				}
				else {
					std::string value_op;
					value_op += *it;
					Token temp(value_op, Token::Type::SUB);
					_tokens.push_back(temp);
				}
			}
			else if (*it == '*') {
				std::string value_op;
				value_op += *it;
				Token temp(value_op, Token::Type::MULT);
				_tokens.push_back(temp);
			}
			else if (*it == '/') {
				std::string value_op;
				value_op += *it;
				Token temp(value_op, Token::Type::DIV);
				_tokens.push_back(temp);
			}
			else if (*it == '(') {
				std::string value_par;
				value_par += *it;
				Token temp(value_par, Token::Type::OPENPAR);
				_tokens.push_back(temp);
			}
			else if (*it == ')') {
				std::string value_par;
				value_par += *it;
				Token temp(value_par, Token::Type::CLOSEPAR);
				_tokens.push_back(temp);
			}
			else if (*it != ' ' && *it != '\0' && *it != '\n') {
				Utility::syntaxErrorMsg();
				return false;
			}
		}
	}
	if (!current_value.empty()) {
		Token temp(current_value, Token::Type::NUM);
		_tokens.push_back(temp);
		current_value.erase(current_value.begin(), current_value.end());
	}
	return true;
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
				Result result = calcul();
				if (result.success == Result::Success::SUCCESS) {
					_numbers.push(result.number);	
				}
				else {
					result.successMsg();
					return;
				}
			}
			_actions.pop();
		}
		else if ((*it).type == Token::Type::ADD || (*it).type == Token::Type::SUB) {
			if((!_actions.empty()) && ((_actions.top().type == Token::Type::MULT) 
				|| (_actions.top().type == Token::Type::DIV))) {
				Result result = calcul();
				if (result.success == Result::Success::SUCCESS) {
					_numbers.push(result.number);	
				}
				else {
					result.successMsg();
					return;
				}
			}
			_actions.push(*it);
		}
		else if ((*it).type == Token::Type::MULT || (*it).type == Token::Type::DIV) {
			if((!_actions.empty()) && ((_actions.top().type == Token::Type::MULT) 
				|| (_actions.top().type == Token::Type::DIV))) {
				Result result = calcul();
				if (result.success == Result::Success::SUCCESS) {
					_numbers.push(result.number);	
				}
				else {
					result.successMsg();
					return;
				}
			}
			_actions.push(*it);
		}
	}
	unstacking();
}

void Bistro::unstacking()
{
	while (!_actions.empty()) {
		Result result = calcul();
		if (result.success == Result::Success::SUCCESS) {
			_numbers.push(result.number);	
		}
		else {
			result.successMsg();
			return;
		}
	}
	if ((int)_numbers.size() > 1)
	{
		Utility::syntaxErrorMsg();
		return;
	}
	printStacks();
}

Result Bistro::calcul()
{	
	if (_actions.empty() || ((int)_numbers.size() < 2)) {
		Number num;
		Result toReturn(num, Result::Success::SYNTAXERROR);
		return toReturn;
	}
	Number rightNum = _numbers.top();
	_numbers.pop();
	Number leftNum = _numbers.top();
	_numbers.pop();
	Result toReturn;
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
			toReturn.number.sign = Number::Sign::NEGATIF;
		}
		else {
			toReturn = Operation::add(leftNum.number, rightNum.number);
		}	
	}
	else if (_actions.top().type == Token::Type::SUB) { // SI SUB
		if (leftNum.sign == Number::Sign::NEGATIF 
			&& rightNum.sign == Number::Sign::POSITIF) {
			toReturn = Operation::add(leftNum.number, rightNum.number);
			toReturn.number.sign = Number::Sign::NEGATIF;
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
			toReturn.number.sign = Number::Sign::NEGATIF;
		}
		else {
			toReturn = Operation::mult(leftNum.number, rightNum.number);
		}
		
	}
	else if (_actions.top().type == Token::Type::DIV) { //SI DIV
		if (leftNum.sign != rightNum.sign) {
			toReturn = Operation::div(leftNum.number, rightNum.number);
			toReturn.number.sign = Number::Sign::NEGATIF;
		}
		else {
			toReturn = Operation::div(leftNum.number, rightNum.number);
		}
		
	}
	else {
		Number num;
		Result error(num, Result::Success::SYNTAXERROR);
		return error;
	}
	_actions.pop();
	return toReturn;
}