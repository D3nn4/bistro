#include <string>
#include <cstdlib>
#include <iostream>

#include "bistro.hpp"

int main(/*int argc, char **argv*/)
{
	/*
	if (argc == 2){
		Bistro bistro(argv[1]);
	}
	*/
	std::string entry;
	while (true) {
		std::getline(std::cin, entry);
		if (entry.compare("exit\n") == 0
			|| entry.compare("quit") == 0
			|| entry.compare("q") == 0) {
			exit(EXIT_SUCCESS);
		}
		Bistro bistro(entry);
	}
	return 0;
}