#pragma once
#include <string>
#include <iostream>

namespace VuKevin
{
	class UnbalancedParentheses : public std::logic_error
	{
	public:
		UnbalancedParentheses(const std::string &msg = "");
	};
}
