#ifndef __NUMBER_H__
#define __NUMBER_H__
#include <vector>
#include <iostream>


struct Number
{
	
		enum class Sign {
			POSITIF,
			NEGATIF
		};

		Number(std::vector<int> number, Number::Sign sign);
		Number(){};
		std::vector<int>  number;
		Sign sign;
		
};

std::ostream &operator<<(std::ostream &o, Number const &number);

#endif // __NUMBER_H__