#include <vector>
#include <string>
#include "number.hpp"
#include "utility.hpp"

Number Utility::stringToNumber(std::string str)
{
	std::vector<int> num;
	for (int i = 0; i < (int)str.size(); ++i)
	{
		num.push_back(str[i] - '0');
	}
	Number number(num, '+');
	return number;
}