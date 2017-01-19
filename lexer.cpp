#include <string>
#include <vector>
#include <iostream>

#include "token.hpp"
#include "bistro.hpp"

std::vector<Token> Bistro::lexer(std::string av)
{
	std::vector<Token> tokens;
	std::string current_value;
	std::string::iterator it = av.begin();
	for (; it != av.end(); ++it) {
		if ('0' <= *it && *it <= '9') {
			current_value += *it;
		}
		else {
			if (!current_value.empty()) {
				Token temp(current_value, Token::Type::NUM);
				tokens.push_back(temp);
				current_value.erase(current_value.begin(), current_value.end());
			}
			if (*it == '+') {
				std::string value_op;
				value_op += *it;
				Token temp(value_op, Token::Type::ADD);
				tokens.push_back(temp);
			}
			else if (*it == '-') {
				std::string value_op;
				value_op += *it;
				Token temp(value_op, Token::Type::SUB);
				tokens.push_back(temp);
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