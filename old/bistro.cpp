#include <deque>
#include <iostream>

#include "arguments.hpp"
#include "number.hpp"
#include "add.hpp"
#include "sub.hpp"

void bistro(int argc, char **argv)
{
	Arguments args(argc, argv);
	Number num1(args.getnum1(), '+');
	Number num2(args.getnum2(), '+');
	std::cout << num1;
	std::cout << num2;
	

	Number addresult = add(num1.getNumber(), num2.getNumber());
	Number subresult = sub(num1.getNumber(), num2.getNumber());

	std::cout << addresult;
	std::cout << subresult;
}


int main(int argc, char **argv)
{
	if (argc > 1){
		bistro(argc, argv);
	}
	return 0;
}