#include <vector>
#include <string>
#include <iostream>

#include "number.hpp"

Number::Number(std::vector<int> num, Number::Sign s)
	:number(num),
	sign(s){}

std::ostream &operator<<(std::ostream &o, Number const &number)
{
	std::vector<int> res = number.number;
	if (number.sign == Number::Sign::NEGATIF)
		o << '-';
	for (int i = 0; i < (int)res.size(); ++i) {
		o <<  res[i];
	}
	return o;
}