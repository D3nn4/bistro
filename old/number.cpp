#include <deque>
#include <string>
#include <iostream>

#include "number.hpp"

Number::Number(std::deque<int> number, char sign)
	:_number(number),
	_sign(sign){}

Number::~Number(){}

void Number::setNumber(std::deque<int> number)
{
	_number = number;
}

void Number::setSign(char sign)
{
	_sign = sign;
}

std::deque<int> Number::getNumber() const
{
	return _number;
}

char Number::getSign() const
{
	return _sign;
}

Number::Number(Number const &src)
{
	if(this != &src)
		*this = src;
}
	
Number &Number::operator=(Number const &src)
{
	this->_sign = src.getSign();
	this->_number = src.getNumber();
	return *this;
}

std::ostream &operator<<(std::ostream &o, Number const &number)
{
	std::deque<int> res = number.getNumber();
	if (number.getSign() == '-')
		o << '-';
	for (int i = 0; i < (int)res.size(); ++i) {
		o <<  res[i];
	}
	o << std::endl;
	return o;
}