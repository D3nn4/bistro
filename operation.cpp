#include <vector>
#include <string>

#include "number.hpp"

Number Operation::add(std::vector<int> num1, std::vector<int> num2)
{
	int rest = 0;
	int total = 0;
	std::vector<int> final_result;
	std::vector<int>::reverse_iterator curr_num1 = num1.rbegin();
	std::vector<int>::reverse_iterator curr_num2 = num2.rbegin();
	while (curr_num1 != num1.rend() || curr_num2 != num2.rend()) {
		int left = 0;
		int right = 0;
		if (curr_num1 != num1.rend()) {
			left = *curr_num1;
			++curr_num1;
		}
		if (curr_num2 != num2.rend()) {
			right = *curr_num2;
			++curr_num2;
		}
		total = left + right + rest;
		
		final_result.push_front(total % 10);
		rest = (total % 100 - total % 10) / 10;
	}
	if (rest > 0) 
		final_result.push_front(rest);
	Number result(final_result, '+');
	return result;
}

Number Operation::sub(std::vector<int> num1, std::vector<int> num2)
{
	char sign = '+';
	std::vector<int> final_result;
	int rest = 0;
	int total = 0;
	if ((num1.size() < num2.size())
		|| (num1.size() == num2.size() && num1.front() < num2.front())) {
		std::vector<int> temp;
		temp = num2;
		num2 = num1;
		num1 = temp;
		sign = '-';
	}
	std::vector<int>::reverse_iterator curr_num1 = num1.rbegin();
	std::vector<int>::reverse_iterator curr_num2 = num2.rbegin();
	while (curr_num1 != num1.rend() || curr_num2 != num2.rend()) {
		int left = 0;
		int right = 0;
		if (curr_num1 != num1.rend()) {
			left = *curr_num1;
			++curr_num1;
		}
		if (curr_num2 != num2.rend()) {
			right = *curr_num2;
			++curr_num2;
		}
		if (left < right + rest) {
			left += 10;
			total = left - (right + rest);
			rest = 1;
		}
		else {
			total = left - (right + rest);
			rest = 0;
		}
		
		final_result.push_front(total);
	}
	Number result(final_result, sign);
	return result;
}

Number Operation::mult(std::vector<int> num1, std::vector<int> num2)
{
	std::cout << "mult\n";
}

Number Operation::div(std::vector<int> num1, std::vector<int> num2)
{
	std::cout << "div\n";
}