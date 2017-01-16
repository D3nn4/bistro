#ifndef __TOKEN_H__
#define __TOKEN_H__
#include <vector>
#include <iostream>
#include <string>

struct Token
{	

	enum Type {
		NUM, 
		OP,
		PARENTHESE
	};

	Token(std::string value, Type type);
	std::string  value;
	Type type;
};

std::ostream &operator<<(std::ostream &o, Token const &Token);

#endif // __TOKEN_H__