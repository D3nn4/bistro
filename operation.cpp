#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <stdbool.h>

#include "number.hpp"
#include "utility.hpp"
#include "operation.hpp"
#include "result.hpp"

bool Operation::isLessThan(std::vector<int> left, std::vector<int> right)
{
	if ((left.size() < right.size())
		|| (left.size() == right.size() && left.front() < right.front())) {
		return true;
	}
	return false;
}

Result Operation::add(std::vector<int> num1, std::vector<int> num2)
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
	Number result(Utility::reverseVector(final_result), Number::Sign::POSITIF);
	Utility::cleanZero(result.number);
	Result toReturn(result, Result::Success::SUCCESS);
	return toReturn;
}

Result Operation::sub(std::vector<int> num1, std::vector<int> num2)
{
	Number::Sign sign = Number::Sign::POSITIF;
	std::vector<int> final_result;
	int rest = 0;
	int total = 0;
	if (isLessThan(num1, num2)) {
		std::vector<int> temp;
		temp = num2;
		num2 = num1;
		num1 = temp;
		sign = Number::Sign::NEGATIF;
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
	Utility::cleanZero(result.number);
	Result toReturn(result, Result::Success::SUCCESS);
	return toReturn;
}

Result Operation::mult(std::vector<int> num1, std::vector<int> num2)
{
	int shift = 0;
	int rest = 0;
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
			temp.push_back(rest);
		if (!leftToAdd.empty() && !rightToAdd.empty()) {
			Number toAdd = add(leftToAdd, rightToAdd).number;
			leftToAdd.clear();
			rightToAdd.clear();
			leftToAdd = toAdd.number;
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
			Number toAdd = add(leftToAdd, rightToAdd).number;
			leftToAdd.clear();
			rightToAdd.clear();
			leftToAdd = toAdd.number;
	}

	Number result(leftToAdd, Number::Sign::POSITIF);
	Utility::cleanZero(result.number);
	Result toReturn(result, Result::Success::SUCCESS);
	return toReturn;
}

Result Operation::div(std::vector<int> num1, std::vector<int> num2)
{
	if ((int)num2.size() == 1 && num2[0] == 0) {
		Number num;
		Result toReturn(num, Result::Success::ZERODIVIDED);
		return toReturn;
	}
	if ((int)num2.size() == 1 && num2[0] == 1) {
		Number num(num1, Number::Sign::POSITIF);
		Result toReturn(num, Result::Success::SUCCESS);
		return toReturn;
	}
	if (isLessThan(num1, num2)) {
		std::vector<int> temp;
		temp.push_back(0);
		Number result(temp, Number::Sign::POSITIF);
		Result toReturn(result, Result::Success::SUCCESS);
		return toReturn;
	}
	int multiple = 1;
	std::vector<int> result;
	std::vector<int>::iterator curseur = num1.begin();
	std::vector<int> current;
	current.push_back(*curseur);
	++curseur;
	for (; isLessThan(current, num1); ++curseur) {
		current.push_back(*curseur);
	}
	--curseur;
	while (curseur != num1.end()) {
		bool cont = true;
		while (cont) {
			Number temp = Operation::sub(current, num2).number;
			if (isLessThan(temp.number, num2)) {
				cont = false;
			}
			else {
				++multiple;
				current.clear();
				current = temp.number;
			}
		}
		result.push_back(multiple);
		multiple = 0;
		current.push_back(*curseur);
		++curseur;
	}
	Number final_result(result, Number::Sign::POSITIF);
	Utility::cleanZero(final_result.number);
	Result toReturn(final_result, Result::Success::SUCCESS);
	return toReturn;
}