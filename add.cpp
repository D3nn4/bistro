#include <vector>
#include <string>

#include "add.hpp"

std::string add(std::vector<char> num1, std::vector<char> num2)
{
	int rest = 0;
	int total = 0;
	std::string total_result;
	std::vector<char>::reverse_iterator curr_num1 = num1.rbegin();
	std::vector<char>::reverse_iterator curr_num2 = num2.rbegin();
	while (curr_num1 != num1.rend() || curr_num2 != num2.rend()) {
		int left = 0;
		int right = 0;
		if (curr_num1 != num1.rend()) {
			left = *curr_num1 - '0';
			++curr_num1;
		}
		if (curr_num2 != num2.rend()) {
			right = *curr_num2 - '0';
			++curr_num2;
		}
		total = left + right + rest;
		std::string result = std::to_string(total);
		total_result.insert(total_result.begin(), result.back());
		if (result.size() > 1) {
		rest = result.front() - '0';
		}
		else
			rest = 0;
	}
	if (rest > 0) {
		total_result.insert(total_result.begin(), rest);
	}

	return total_result;

}