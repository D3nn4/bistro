#include <iostream>
#include <string>
#include <stack>

#include "lexer.hpp"
#include "token.hpp"


void bistro(char **argv)
{
	std::string arg(argv[1]);
	std::vector<Token> tokens = lexer(arg);

	//std::stack<std::string> actions;
	//std::stack<std::string> numbers;





	std::vector<Token>::iterator it = tokens.begin();
	while (it != tokens.end()) {
		std::cout << *it;
		++it;
	}
	
}


int main(int argc, char **argv)
{
	if (argc > 1){
		bistro(argv);
	}
	return 0;
}