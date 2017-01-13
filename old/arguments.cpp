#include <deque>
#include <iostream>

#include "arguments.hpp"

Arguments::Arguments(int ac, char **av)
{
	std::deque< std::deque<int> > numbers;
	for (int i = 1; i < ac; ++i) {
		std::deque<int> num;
		for (int j = 0; av[i][j] != '\0'; ++j) {
			num.push_back(av[i][j] - '0');
		}
		numbers.push_back(num);
	}
	_num1 = numbers[0];
	_num2 = numbers[1];
}
Arguments::~Arguments(){}

std::deque<int> Arguments::getnum1() const
{
	return _num1;
}

std::deque<int> Arguments::getnum2() const
{
	return _num2;
}