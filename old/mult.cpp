#include <deque>
#include <string>
#include <stdbool.h>

#include "mult.hpp"
#include "add.hpp"

std::string mult(std::deque<int> num1, std::deque<int> num2) {
	int shift = 0;
	char sign = '+';
	std::deque<int> leftToAdd;
	std::deque<int> rightToAdd;
	std::deque<int> final_result;
	std::deque<int>::reverse_iterator curr_num1 = num1.rbegin();
	for (curr_num1; curr_num1 != num1.rend(); ++curr_num1) {
		std::deque<int>::reverse_iterator curr_num2 = num2.rbegin();
		if (!leftToAdd.empty() && !rightToAdd.empty()) {

		}
		for (curr_num2; curr_num2 != curr_num2.rend(); ++curr_num2) {

		}
	}

}