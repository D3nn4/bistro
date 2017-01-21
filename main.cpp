#include <string>
#include <cstdlib>
#include <iostream>

#include "bistro.hpp"

int main(int argc, char **argv)
{
	
	if (argc == 2){
		Bistro bistro(argv[1]);
	}
	else {
		std::string entry;
		while (!std::cin.eof()) {
			std::getline(std::cin, entry);
			if (entry.compare("exit") == 0
				|| entry.compare("quit") == 0
				|| entry.compare("q") == 0) {
				break;
			}
			Bistro bistro(entry);
		}
	}
	return EXIT_SUCCESS;
}