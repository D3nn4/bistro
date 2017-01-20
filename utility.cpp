#include <vector>
#include <string>
#include "number.hpp"
#include "utility.hpp"

Number Utility::stringToNumber(std::string str)
{
	std::vector<int> num;
	int i = 0;
	Number::Sign sign = Number::Sign::POSITIF;
	if (str[0] == '-') {
			++i;
			sign = Number::Sign::NEGATIF;
	}
	for (; i < (int)str.size(); ++i)
	{
		num.push_back(str[i] - '0');
	}
	Number number(num, sign);
	return number;
}

std::vector<int> Utility::reverseVector(std::vector<int> number)
{
	std::vector<int> toReturn;
	std::vector<int>::reverse_iterator it = number.rbegin();
	for (; it != number.rend(); ++it) {
		toReturn.push_back(*it);
	}
	return toReturn;
}