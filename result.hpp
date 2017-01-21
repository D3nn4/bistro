#ifndef __RESULT_H__
#define __RESULT_H__
#include <stdbool.h>

#include "number.hpp"

struct Result
{
		enum class Success {
			SYNTAXERROR,
			SUCCESS,
			ZERODIVIDED
		};
		Result(){};
		Result(Number num, Result::Success s);
		void successMsg();
		Number number;
		Success success;
};

#endif // __RESULT_H__