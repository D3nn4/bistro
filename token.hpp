#ifndef __TOKEN_H__
#define __TOKEN_H__
#include <vector>
#include <iostream>
#include <string>

class Token
{
	private:

	protected:

		std::string  _value;
		std::string _type;
		Token();
		//Token(Token const &src); 
		//Token &operator=(Token const &src);

	public:
		Token(std::string value, std::string type);
		~Token();
		std::string getValue() const;
		std::string getType() const;
		
};

std::ostream &operator<<(std::ostream &o, Token const &Token);

#endif // __TOKEN_H__