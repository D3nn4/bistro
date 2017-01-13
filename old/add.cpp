#include <deque>
#include <string>

#include "number.hpp"

Number add(std::deque<int> num1, std::deque<int> num2)
{
	int rest = 0;
	int total = 0;
	std::deque<int> final_result;
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
		total = left + right + rest;
		
		final_result.push_front(total % 10);
		rest = (total % 100 - total % 10) / 10;
	}
	if (rest > 0) 
		final_result.push_front(rest);
	Number result(final_result, '+');
	return result;
}