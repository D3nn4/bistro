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

void Utility::cleanZero(std::vector<int> &number)
{
	if ((int)number.size() == 1 && number.front() == 0) {
		return;
	}
	while (!number.empty() && number.front() == 0) {
		number.erase(number.begin());
	}
	if (number.empty()) {
		number.push_back(0);
	}
}

void Utility::syntaxErrorMsg()
{
	std::cout << "Syntax error\n";
}

void Utility::zeroDividedMsg()
{
	std::cout << "Error : divide by zero\n";
}