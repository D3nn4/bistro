#include <deque>

#include "number.hpp"

Number sub(std::deque<int> num1, std::deque<int> num2)
{
	char sign = '+';
	std::deque<int> final_result;
	int rest = 0;
	int total = 0;
	if ((num1.size() < num2.size())
		|| (num1.size() == num2.size() && num1.front() < num2.front())) {
		std::deque<int> temp;
		temp = num2;
		num2 = num1;
		num1 = temp;
		sign = '-';
	}
	std::deque<int>::reverse_iterator curr_num1 = num1.rbegin();
	std::deque<int>::reverse_iterator curr_num2 = num2.rbegin();
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