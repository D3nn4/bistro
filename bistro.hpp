#ifndef __BISTRO_H__
#define __BISTRO_H__
#include <string>
#include <vector>
#include <stack>
#include "number.hpp"
#include "token.hpp"

class Bistro
{
	private:

	protected:
		std::vector<Token> _tokens;
		std::stack<std::string> _actions;
		std::stack<Number> _numbers;

	public:
		Bistro(char *argv);
		std::vector<Token> lexer(std::string av);
		bool isVIP(Token token);
		void stacking();
};

std::ostream &operator<<(std::ostream &o, Bistro const &bistro);

#endif // __BISTRO_H__