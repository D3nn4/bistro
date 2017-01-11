#include <vector>
#include <string>
#include <iostream>

#include "add.hpp"

void bistro(int argc, char **argv)
{
	std::vector< std::vector<char> > numbers;
	for (int i = 1; i < argc; ++i) {
		std::vector<char> num;
		for (int j = 0; argv[i][j] != '\0'; ++j) {
			num.push_back(argv[i][j]);
		}
		numbers.push_back(num);
	}
	for (int i = 0; i < (int)numbers[0].size(); ++i){
		std::cout << numbers[0][i];
	}
	std::cout << std::endl;
	for (int i = 0; i < (int)numbers[1].size(); ++i){
		std::cout << numbers[1][i];
	}
	std::cout << std::endl;

	std::cout << add(numbers[0], numbers[1]) << std::endl;
}


int main(int argc, char **argv)
{
	if (argc > 1){
		bistro(argc, argv);
	}
	return 0;
}