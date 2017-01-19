#ifndef __TOKEN_H__
#define __TOKEN_H__
#include <vector>
#include <iostream>
#include <string>

struct Token
{	

	enum class Type {
		NUM, 
		ADD,
		SUB,
		MULT,
		DIV,
		OPENPAR,
		CLOSEPAR
	};

	Token(std::string value, Type type);
	std::string  value;
	Type type;
};

std::ostream &operator<<(std::ostream &o, Token const &Token);

#endif // __TOKEN_H__