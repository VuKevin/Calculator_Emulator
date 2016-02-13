#pragma once
#include <string>
#include <iostream>

namespace VuKevin
{
	class DivideByZero : public std::logic_error
	{
	public:
		DivideByZero(const std::string &msg = "");
		const char* what() const;
	};
}
