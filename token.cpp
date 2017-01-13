#include <vector>
#include <iostream>
#include <string>

#include "token.hpp"

Token::Token(std::string value, std::string type)
	:_value(value),
	_type(type){}

Token::~Token(){}

std::string Token::getValue() const
{
	return _value;
}

std::string Token::getType() const
{
	return _type;
}

std::ostream &operator<<(std::ostream &o, Token const &token)
{
	o << token.getValue() << "\n";
	return o;
}