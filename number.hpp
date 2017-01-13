#ifndef __NUMBER_H__
#define __NUMBER_H__
#include <vector>
#include <iostream>


class Number
{
	protected:

		std::vector<int>  _number;
		char _sign;
		Number();
		

	public:
		Number(std::vector<int> number, char sign);
		~Number();
		void setNumber(std::vector<int> number);
		void setSign(char sign);
		std::vector<int> getNumber() const;
		char getSign() const;
		Number(Number const &src); 
		Number &operator=(Number const &src);
};

std::ostream &operator<<(std::ostream &o, Number const &number);

#endif // __NUMBER_H__