#ifndef __BISTRO_H__
#define __BISTRO_H__
#include <string>
#include <vector>
#include <stack>
#include <stdbool.h>
#include "number.hpp"
#include "token.hpp"
#include "result.hpp"

class Bistro
{
	private:

	protected:
		std::vector<Token> _tokens;
		std::stack<Token> _actions;
		std::stack<Number> _numbers;
		bool isPar(Token token);
		bool isOp(Token token);
		

	public:
		
		Bistro(std::string str);
		bool lexer(std::string av);
		void stacking();
		void printStacks();
		void unstacking();
		Result calcul();
};

std::ostream &operator<<(std::ostream &o, Bistro const &bistro);

#endif // __BISTRO_H__