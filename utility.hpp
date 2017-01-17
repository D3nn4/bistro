#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <vector>
#include <deque>
#include <string>
#include "number.hpp"

class Utility
{	

	public:
		static Number stringToNumber(std::string str);
		static std::vector<int> reverseVector(std::vector<int> number); 
};

#endif // __UTILITY_H__