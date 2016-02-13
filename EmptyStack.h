#pragma once
#include <iostream>
#include <string>

namespace VuKevin
{
	class EmptyStack : public std::logic_error
	{
	public:
		EmptyStack(const std::string& msg = "");
	};
}
