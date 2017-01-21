#include <stdbool.h>

#include "number.hpp"
#include "result.hpp"
#include "utility.hpp"


Result::Result(Number num, Result::Success s)
	:number(num),
	success(s){}

void Result::successMsg()
{
	if (success == Result::Success::SYNTAXERROR) {
		Utility::syntaxErrorMsg();
	}
	else if (success == Result::Success::ZERODIVIDED) {
		Utility::zeroDividedMsg();
	}
}