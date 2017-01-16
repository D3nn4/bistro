#include <vector>
#include <iostream>
#include <string>

#include "token.hpp"

Token::Token(std::string value, Type type)
	:value(value),
	type(type){}

std::ostream &operator<<(std::ostream &o, Token const &token)
{
	o << token.value << "\n";
	return o;
}