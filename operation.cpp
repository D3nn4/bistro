#include <vector>
#include <deque>
#include <string>
#include <iostream>

#include "number.hpp"
#include "utility.hpp"
#include "operation.hpp"

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
		
		final_result.push_back(total % 10);
		rest = (total % 100 - total % 10) / 10;
	}
	if (rest > 0) 
		final_result.push_back(rest);
	Number result(Utility::reverseVector(final_result), '+');
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
		
		final_result.push_back(total);
	}
	Number result(Utility::reverseVector(final_result), sign);
	return result;
}

Number Operation::mult(std::vector<int> num1, std::vector<int> num2)
{
	int shift = 0;
	int rest = 0;
	char sign = '+';
	std::vector<int> leftToAdd;
	std::vector<int> rightToAdd;
	std::vector<int>::reverse_iterator curr_num2 = num2.rbegin();
	for (; curr_num2 != num2.rend(); ++curr_num2) {
		std::vector<int>::reverse_iterator curr_num1 = num1.rbegin();
		std::vector<int> temp;
		for (int i = 0; i < shift ;++i) {
			temp.push_back(0);
		}
		for (; curr_num1 != num1.rend(); ++curr_num1) {
			int total = ((*curr_num1) * (*curr_num2)) + rest;
			temp.push_back(total % 10);
			
			if (total > 9)
				rest = (total - (total % 10)) / 10;
			else
				rest = 0;
		}
		if (rest > 0)
			leftToAdd.push_back(rest);
		if (!leftToAdd.empty() && !rightToAdd.empty()) {
			Number toAdd = add(leftToAdd, rightToAdd);
			leftToAdd.clear();
			rightToAdd.clear();
			leftToAdd = toAdd.getNumber();
		}
		else if (leftToAdd.empty()) {
			leftToAdd = Utility::reverseVector(temp);
		}
		else {
			rightToAdd = Utility::reverseVector(temp);
		}
		++shift;
	}
	if (!leftToAdd.empty() && !rightToAdd.empty()) {
			Number toAdd = add(leftToAdd, rightToAdd);
			leftToAdd.clear();
			rightToAdd.clear();
			leftToAdd = toAdd.getNumber();
	}

	Number result(Utility::reverseVector(leftToAdd), sign);
	return result;
}
/*
void Operation::div(std::vector<int> num1, std::vector<int> num2)
{
	std::cout << "div\n";
}*/