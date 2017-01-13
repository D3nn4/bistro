#ifndef __NUMBER_H__
#define __NUMBER_H__
#include <deque>
#include <iostream>


class Number
{
	private:

	protected:

		std::deque<int>  _number;
		char _sign;
		Number();
		

	public:
		Number(std::deque<int> number, char sign);
		~Number();
		void setNumber(std::deque<int> number);
		void setSign(char sign);
		std::deque<int> getNumber() const;
		char getSign() const;
		Number(Number const &src); 
		Number &operator=(Number const &src);
};

std::ostream &operator<<(std::ostream &o, Number const &number);

#endif // __NUMBER_H__