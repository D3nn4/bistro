#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__
#include <deque>

class Arguments
{
	private:

	protected:

		std::deque<int> _num1;
		std::deque<int> _num2;
		Arguments(); //deleted
		Arguments(Arguments const &src); //not done
		Arguments &operator=(Arguments const &src);	//not done

	public:
		Arguments(int ac, char **av);
		~Arguments();
		std::deque<int> getnum1() const;
		std::deque<int> getnum2() const;
		
};

//std::ostream &operator<<(std::ostream &o, Arguments const &arg);

#endif // __ARGUMENTS_H__