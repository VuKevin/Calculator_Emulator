#pragma once
#include <string>
#include <iostream>

namespace VuKevin
{
	class InvalidCharacter : public std::logic_error
	{
	public:
		InvalidCharacter(const std::string &msg = "");
	};
}
