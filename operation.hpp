#ifndef __OPERATION_H__
#define __OPERATION_H__
#include <vector>
#include <iostream>
#include <stdbool.h>
#include "result.hpp"


class Operation
{
		
	public:
		static bool isLessThan(std::vector<int> left, std::vector<int> right);
		static Result add(std::vector<int> num1, std::vector<int> num2);
		static Result sub(std::vector<int> num1, std::vector<int> num2);		
		static Result mult(std::vector<int> num1, std::vector<int> num2);	
		static Result div(std::vector<int> num1, std::vector<int> num2);	
};

#endif // __OPERATION_H__