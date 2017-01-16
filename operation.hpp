#ifndef __OPERATION_H__
#define __OPERATION_H__
#include <vector>
#include <iostream>


class Operation
{
	public:
		static Number add(std::vector<int> num1, std::vector<int> num2);
		static Number sub(std::vector<int> num1, std::vector<int> num2);		
		static Number mult(std::vector<int> num1, std::vector<int> num2);	
		static Number div(std::vector<int> num1, std::vector<int> num2);	
};

#endif // __OPERATION_H__