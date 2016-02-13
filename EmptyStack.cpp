#include "EmptyStack.h"

namespace VuKevin
{
	EmptyStack::EmptyStack(const std::string& msg)
		: std::logic_error(msg.c_str())
	{}
}
